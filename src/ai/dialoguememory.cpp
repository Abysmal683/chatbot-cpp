#include "dialoguememory.h"

void DialogueMemory::addMessage(const QString& sender, const QString& text)
{
    buffer.append(DialogueMessage{sender, text});
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

void DialogueMemory::clear()
{
    buffer.clear();
}
