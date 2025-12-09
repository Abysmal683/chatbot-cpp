#include "contextbuilder.h"
#include "dialoguememory.h"
#include "conversationhistorydao.h"
#include "longtermstore.h"
#include "intentclassifier.h"
#include "keyworddetector.h"
#include "memorylongterm.h"
#include <algorithm>

ContextBuilder::ContextBuilder(DialogueMemory* sessionMemory,
                               ConversationHistoryDAO* historyDao,
                               LongTermStore* longTermStore,
                               IntentClassifier* intentClassifier,
                               KeywordDetector* keywordDetector)
    : sessionMemory(sessionMemory),
    historyDao(historyDao),
    longTermStore(longTermStore),
    intentClassifier(intentClassifier),
    keywordDetector(keywordDetector)
{
}

QString ContextBuilder::buildContext(const QString& userMessage,
                                     const QString& intentId,
                                     const QStringList& detectedKeywords,
                                     bool includeMemory,
                                     bool includeHistory,
                                     int historyMessages) const
{
    QStringList ctxSections;

    // ===== CONTEXT =====
    ctxSections << "=== CONTEXT ===";
    ctxSections << "User message: " + userMessage;

    // Si existe el intentClassifier se usa para detectar intención
    QString intentStr = intentId.isEmpty() && intentClassifier
                            ? intentClassifier->classify(userMessage).intent
                            : intentId;
    ctxSections << "Detected intent: " + intentStr;

    // Detectar keywords dinámicamente si hay detector
    QStringList kws = detectedKeywords;
    if (kws.isEmpty() && keywordDetector)
        kws = keywordDetector->detectar(userMessage);
    ctxSections << "Keywords: " + kws.join(", ");

    // ===== MEMORY =====
    if (includeMemory) {
        ctxSections << "\n=== MEMORY ===";
        ctxSections << buildMemorySection();
    }

    // ===== HISTORY =====
    if (includeHistory) {
        ctxSections << "\n=== HISTORY ===";
        ctxSections << buildHistorySection(historyMessages);
    }

    ctxSections << "=== END CONTEXT ===";

    return ctxSections.join("\n");
}

// --------------------------------------------
// Memoria de largo plazo, ordenada y eficiente
// --------------------------------------------
QString ContextBuilder::buildMemorySection() const
{
    if (!longTermStore)
        return "No long-term memory available.";

    const auto keys = longTermStore->listKeys();
    if (keys.isEmpty())
        return "No saved long-term memory.";

    QStringList output;
    for (const QString& key : keys) {
        const auto memories = longTermStore->getAllMemories(key);
        if (memories.isEmpty())
            continue;

        // Ordenar por importancia descendente
        QList<MemoryLongTerm> sorted = memories;
        std::sort(sorted.begin(), sorted.end(),
                  [](const MemoryLongTerm& a, const MemoryLongTerm& b) {
                      return a.importance > b.importance;
                  });

        QStringList values;
        for (const MemoryLongTerm& m : sorted)
            values << m.value;

        output << key + ": " + values.join(" | ");
    }

    return output.isEmpty() ? "Memory empty." : output.join("\n");
}

// --------------------------------------------
// Historial reciente de conversación
// --------------------------------------------
QString ContextBuilder::buildHistorySection(int nMessages) const
{
    // No hay memoria ni historial
    if (!sessionMemory && !historyDao)
        return "No session or history memory available.";

    QStringList out;
    int remaining = nMessages;

    // 1️ Tomar primero de sessionMemory si existe
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

    // 2️ Completar con historyDao si aún faltan
    if (remaining > 0 && historyDao) {
        const auto lastHistory = historyDao->getLastMessages(remaining);
        for (const auto& h : lastHistory) {
            out << QString("U [%1]: %2").arg(h.timestamp, h.user_message);
            out << QString("B [%1]: %2").arg(h.timestamp, h.bot_message);
        }
    }

    return out.isEmpty() ? "No previous messages." : out.join("\n");
}
