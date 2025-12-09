#include "dialoguememory.h"

DialogueMemory::DialogueMemory(int maxSize)
    : maxSize(maxSize)
{
}

void DialogueMemory::addMessage(const QString& sender, const QString& text)
{
    DialogueMessage msg;
    msg.sender = sender;
    msg.text = text;
    msg.timestamp = QDateTime::currentDateTime().toString(Qt::ISODate);

    buffer.append(msg);

    // Mantener tamaño máximo
    if (buffer.size() > maxSize)
        buffer.remove(0, buffer.size() - maxSize);
}

void DialogueMemory::addUserMessage(const QString& text)
{
    addMessage(C_User, text);
}

void DialogueMemory::addBotMessage(const QString& text)
{
    addMessage(C_Bot, text);
}

QList<DialogueMessage> DialogueMemory::getLast(int n) const
{
    if (n >= buffer.size())
        return buffer;
    return buffer.mid(buffer.size() - n, n);
}

QList<DialogueMessage> DialogueMemory::getFullSession() const
{
    return buffer;
}

QList<ConversationHistory> DialogueMemory::getAsHistory() const
{
    QList<ConversationHistory> list;
    for (const auto& msg : buffer) {
        if (msg.sender == C_User) {
            ConversationHistory ch;
            ch.user_message = msg.text;
            ch.timestamp = msg.timestamp;
            list.append(ch);
        } else if (msg.sender == C_Bot) {
            // Asignar bot_message al último user_message si existe
            if (!list.isEmpty() && list.last().bot_message.isEmpty()) {
                list.last().bot_message = msg.text;
            }
        }
    }
    return list;
}

void DialogueMemory::clear()
{
    buffer.clear();
}

int DialogueMemory::size() const
{
    return buffer.size();
}
