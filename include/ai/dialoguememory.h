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

    // Añadir mensajes al historial
    void addMessage(const QString& sender, const QString& text);

    // Últimos N mensajes
    QList<DialogueMessage> getLast(int n) const;

    // Sesión completa (se borra al reiniciar)
    QList<DialogueMessage> getFullSession() const;

    // Limpia la sesión
    void clear();

private:
    QList<DialogueMessage> buffer;
};

#endif // DIALOGUEMEMORY_H
