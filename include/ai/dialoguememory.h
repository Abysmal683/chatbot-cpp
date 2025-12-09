#ifndef DIALOGUEMEMORY_H
#define DIALOGUEMEMORY_H

#include "constants.h"
#include "conversationhistory.h"
#include <QString>
#include <QList>
#include <QDateTime>

// Mensaje de diálogo con timestamp
struct DialogueMessage {
    QString sender;   // "user" o "bot"
    QString text;
    QString timestamp; // ISO8601
};

class DialogueMemory
{
public:
    DialogueMemory(int maxSize = 50);  // buffer limitado

    // Añadir mensajes
    void addUserMessage(const QString& text);
    void addBotMessage(const QString& text);

    // Obtener mensajes
    QList<DialogueMessage> getLast(int n) const;       // últimos n mensajes
    QList<DialogueMessage> getFullSession() const;     // toda la sesión
    QList<ConversationHistory> getAsHistory() const;  // útil para DAO

    void clear();
    int size() const;

private:
    void addMessage(const QString& sender, const QString& text);

    QList<DialogueMessage> buffer;
    int maxSize;

    static inline const QString &C_User = Constants::User;
    static inline const QString &C_Bot = Constants::Bot;
};

#endif // DIALOGUEMEMORY_H
