#include "ai/conversationhistory.h"

ConversationHistory::ConversationHistory()
{
    historial.reserve(100);   // opcional: evita realocaciones iniciales
}

void ConversationHistory::registrarTurno(const QString &emisor,
    const QString &mensaje,
    qint64 timestamp)
{
    TurnoConversacion turno;
    turno.emisor = emisor;
    turno.mensaje = mensaje;
    turno.timestamp = timestamp;

    historial.append(turno);
}

QVector<TurnoConversacion> ConversationHistory::obtenerHistorialFiltrado(const QString &emisorFiltro,
    qint64 desde,
    qint64 hasta) const
{
    QVector<TurnoConversacion> filtrado;
    filtrado.reserve(historial.size());

    for (const auto &t : historial) {

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

void ConversationHistory::limpiarConversacion()
{
    historial.clear();
}
