#ifndef DIALOGUEMEMORY_H
#define DIALOGUEMEMORY_H

#include <QString>
#include <QList>

struct DialogueMessage {
    QString sender;   // "user" o "bot"
    QString text;
};

class DialogueMemory
{
public:
    DialogueMemory() = default;

    // API existente
    void addMessage(const QString& sender, const QString& text);
    QList<DialogueMessage> getLast(int n) const;
    QList<DialogueMessage> getFullSession() const;
    void clear();

    // NUEVO: helpers específicos
    void addUserMessage(const QString& text);
    void addBotMessage(const QString& text);

private:
    QList<DialogueMessage> buffer;
};

#endif // DIALOGUEMEMORY_H
