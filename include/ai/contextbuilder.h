#ifndef CONTEXTBUILDER_H
#define CONTEXTBUILDER_H

#include <QString>
#include <QStringList>

class DialogueMemory;
class ConversationHistoryDAO;
class LongTermStore;
class IntentClassifier;
class KeywordDetector;

class ContextBuilder
{
public:
    ContextBuilder(DialogueMemory* sessionMemory,
        ConversationHistoryDAO* historyDao,
        LongTermStore* longTermStore,
        IntentClassifier* intentClassifier,
        KeywordDetector* keywordDetector);

    // Construye el contexto final para la IA
    QString buildContext(const QString& userMessage,
        const QString& intentId,
        const QStringList& detectedKeywords) const;

private:
    DialogueMemory* sessionMemory;
    ConversationHistoryDAO* historyDao;
    LongTermStore* longTermStore;
    IntentClassifier* intentClassifier;
    KeywordDetector* keywordDetector;

    QString buildHistorySection() const;
    QString buildMemorySection() const;
};

#endif // CONTEXTBUILDER_H
