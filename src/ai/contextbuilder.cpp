#include "contextbuilder.h"
#include "dialoguememory.h"
#include "conversationhistorydao.h"
#include "longtermstore.h"
#include "memorylongterm.h"
#include <algorithm>
#include <QSet>

ContextBuilder::ContextBuilder(DialogueMemory* sessionMemory,
                               ConversationHistoryDAO* historyDao,
                               LongTermStore* longTermStore)
    : sessionMemory(sessionMemory),
    historyDao(historyDao),
    longTermStore(longTermStore)
{
}

QString ContextBuilder::buildContext(const QString& userMessage,
                                     const QString& intstr,
                                     const QStringList& kws,
                                     bool includeMemory,
                                     bool includeHistory,
                                     int historyMessages) const
{
    QStringList ctxSections;

    // ===== CONTEXT =====
    ctxSections << "=== CONTEXT ===";
    ctxSections << "User message: " + userMessage;
    ctxSections << "Detected intent: " + intstr;

    // Keywords únicos y normalizados
    QSet<QString> uniqueKws(kws.begin(), kws.end());
    ctxSections << "Keywords: " + QStringList(uniqueKws.begin(), uniqueKws.end()).join(", ");

    // ===== MEMORY =====
    if (includeMemory) {
        ctxSections << "=== MEMORY ===";
        ctxSections << buildMemorySection();
    }

    // ===== HISTORY =====
    if (includeHistory) {
        ctxSections << "=== HISTORY ===";
        ctxSections << buildHistorySection(historyMessages);
    }

    ctxSections << "=== END CONTEXT ===";

    return ctxSections.join("\n");
}

// --------------------------------------------
// Memoria de largo plazo, ordenada y limitada
// --------------------------------------------
QString ContextBuilder::buildMemorySection() const
{
    if (!longTermStore)
        return "No long-term memory available.";

    const auto keys = longTermStore->listKeys();
    if (keys.isEmpty())
        return "No saved long-term memory.";

    QStringList output;
    const int maxMemoriesPerKey = 5; // limitar recuerdos por key

    for (const QString& key : keys) {
        const auto memories = longTermStore->getAllMemories(key);
        if (memories.isEmpty())
            continue;

        QList<MemoryLongTerm> sorted = memories;
        std::sort(sorted.begin(), sorted.end(),
                  [](const MemoryLongTerm& a, const MemoryLongTerm& b) {
                      return a.importance > b.importance;
                  });

        QStringList values;
        for (int i = 0; i < qMin(sorted.size(), maxMemoriesPerKey); ++i)
            values << sorted[i].value;

        output << key + ": " + values.join(" | ");
    }

    return output.isEmpty() ? "Memory empty." : output.join("\n");
}

// --------------------------------------------
// Historial reciente de conversación limitado
// --------------------------------------------
QString ContextBuilder::buildHistorySection(int nMessages) const
{
    if (!sessionMemory && !historyDao)
        return "No session or history memory available.";

    QStringList out;
    int remaining = nMessages;

    // 1️ SessionMemory primero
    if (sessionMemory) {
        const auto lastSession = sessionMemory->getLast(remaining);
        for (const auto& msg : lastSession) {
            if (msg.sender == Constants::User)
                out << QString("U [%1]: %2").arg(msg.timestamp, msg.text);
            else if (msg.sender == Constants::Bot)
                out << QString("B [%1]: %2").arg(msg.timestamp, msg.text);
        }
        remaining -= lastSession.size();
    }

    // 2️ Completar con historyDao si falta
    if (remaining > 0 && historyDao) {
        const auto lastHistory = historyDao->getLastMessages(remaining);
        for (const auto& h : lastHistory) {
            out << QString("U [%1]: %2").arg(h.timestamp, h.user_message);
            out << QString("B [%1]: %2").arg(h.timestamp, h.bot_message);
        }
    }

    // Limitar total de mensajes a nMessages
    if (out.size() > nMessages)
        out = out.mid(out.size() - nMessages);

    return out.isEmpty() ? "No previous messages." : out.join("\n");
}
