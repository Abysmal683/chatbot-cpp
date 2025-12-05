#ifndef CONVERSATIONHISTORY_H
#define CONVERSATIONHISTORY_H

#include <QString>
#include <QVector>

struct TurnoConversacion {
    QString emisor;      // "usuario", "sistema", "IA", etc.
    QString mensaje;     // contenido
    qint64 timestamp;    // unix ms
};

class ConversationHistory
{
public:
    ConversationHistory();

    void registrarTurno(const QString &emisor,
        const QString &mensaje,
        qint64 timestamp);

    QVector<TurnoConversacion> obtenerHistorialFiltrado(const QString &emisorFiltro = QString(),
        qint64 desde = 0,
        qint64 hasta = 0) const;

    void limpiarConversacion();

private:
    QVector<TurnoConversacion> historial;
};

#endif // CONVERSATIONHISTORY_H
