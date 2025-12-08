#ifndef DIALOGUEMEMORY_H
#define DIALOGUEMEMORY_H

#include "constants.h"
#include <QString>
#include <QList>
//registra de manera temporal la conversacion mas reciente
struct DialogueMessage {
    QString sender;   // "user" o "bot"
    QString text;
};

class DialogueMemory
{
public:
    DialogueMemory() = default;

    // API existente
    QList<DialogueMessage> getLast(int n) const;
    QList<DialogueMessage> getFullSession() const;
    void clear();

    // NUEVO: helpers específicos
    void addUserMessage(const QString& text);
    void addBotMessage(const QString& text);

private:
    void addMessage(const QString& sender, const QString& text);
    QList<DialogueMessage> buffer;
    static inline const QString &C_User = Constants::User;
    static inline const QString &C_Bot = Constants::Bot;
};

#endif // DIALOGUEMEMORY_H
