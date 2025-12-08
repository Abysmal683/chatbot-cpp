#include "chatsessionhistory.h"

ChatSessionHistory::ChatSessionHistory()
{
    historial.reserve(100);
}

void ChatSessionHistory::registrarTurno(const QString &emisor,
                                        const QString &mensaje,
                                        qint64 timestamp)
{
    historial.append(TurnoConversacion{emisor, mensaje, timestamp});
}

void ChatSessionHistory::addUserTurn(const QString &mensaje, qint64 timestamp)
{
    registrarTurno(C_User, mensaje, timestamp);
}

void ChatSessionHistory::addBotTurn(const QString &mensaje, qint64 timestamp)
{
    registrarTurno(C_Bot, mensaje, timestamp);
}

// ---------------------------
// Filtrado
// ---------------------------
QVector<TurnoConversacion> ChatSessionHistory::obtenerHistorialFiltrado(
    const QString &emisorFiltro, qint64 desde, qint64 hasta) const
{
    QVector<TurnoConversacion> filtrado;
    filtrado.reserve(historial.size());

    for (const auto &t : historial)
    {
        if (!emisorFiltro.isEmpty() && t.emisor != emisorFiltro)
            continue;
        if (desde > 0 && t.timestamp < desde)
            continue;
        if (hasta > 0 && t.timestamp > hasta)
            continue;

        filtrado.append(t);
    }

    return filtrado;
}

void ChatSessionHistory::limpiarConversacion()
{
    historial.clear();
}
