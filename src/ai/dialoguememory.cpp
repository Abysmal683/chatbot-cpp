#include "dialoguememory.h"

void DialogueMemory::addMessage(const QString& sender, const QString& text)
{
    buffer.append({ sender, text });
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
