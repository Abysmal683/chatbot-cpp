#include "contextbuilder.h"
#include "dialoguememory.h"
#include "conversationhistorydao.h"
#include "longtermstore.h"
#include "intentclassifier.h"
#include "keyworddetector.h"

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
    const QStringList& detectedKeywords) const
{
    QString ctx;

    ctx += "=== CONTEXT ===\n";
    ctx += "User message: " + userMessage + "\n";
    ctx += "Detected intent: " + intentId + "\n";
    ctx += "Keywords: " + detectedKeywords.join(", ") + "\n\n";

    ctx += "=== MEMORY ===\n";
    ctx += buildMemorySection() + "\n\n";

    ctx += "=== HISTORY ===\n";
    ctx += buildHistorySection() + "\n";

    ctx += "=== END CONTEXT ===\n";

    return ctx;
}

// --------------------------------------------
// Memoria del usuario: gustos, preferencias, datos persistentes
// --------------------------------------------
QString ContextBuilder::buildMemorySection() const
{
    if (!longTermStore)
        return "No long-term memory available.\n";

    const QList<QString> keys = longTermStore->listKeys();
    if (keys.isEmpty())
        return "No saved long-term memory.\n";

    QString out;

    for (const QString& key : keys) {

        const QList<MemoryLongTerm> list = longTermStore->getAllMemories(key);

        if (list.isEmpty())
            continue;

        out += key + ": ";

        QStringList values;
        for (const MemoryLongTerm& m : list)
            values.append(m.value);

        out += values.join(" | ");
        out += "\n";
    }

    if (out.isEmpty())
        return "Memory empty.\n";

    return out;
}

// --------------------------------------------
// Historial reciente de conversación
// --------------------------------------------
QString ContextBuilder::buildHistorySection() const
{
    if (!historyDao)
        return "No conversation history.\n";

    const auto last = historyDao->getLastMessages(5);
    if (last.isEmpty())
        return "No previous messages.\n";

    QString out;
    for (const auto& h : last) {
        out += "U: " + h.user_message + "\n";
        out += "B: " + h.bot_message + "\n";
    }

    return out;
}
