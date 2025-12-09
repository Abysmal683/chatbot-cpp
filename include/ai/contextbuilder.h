#ifndef CONTEXTBUILDER_H
#define CONTEXTBUILDER_H

#include <QString>
#include <QStringList>
//desarrolla el texto con todo el contexto para la AI,conlleva todo el proceso
class DialogueMemory;
class ConversationHistoryDAO;
class LongTermStore;

class ContextBuilder
{
public:
    ContextBuilder(DialogueMemory* sessionMemory,
                   ConversationHistoryDAO* historyDao,
                   LongTermStore* longTermStore);

    // Construye el contexto final para la IA
    QString buildContext(const QString& userMessage,
                         const QString& intstr,
                         const QStringList &kws,
                         bool includeMemory = true,
                         bool includeHistory = true,
                         int historyMessages = 5) const;

private:
    DialogueMemory* sessionMemory;
    ConversationHistoryDAO* historyDao;
    LongTermStore* longTermStore;

    QString buildMemorySection() const;
    QString buildHistorySection(int nMessages) const;
};

#endif // CONTEXTBUILDER_H
