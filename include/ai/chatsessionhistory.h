#ifndef CHATSESSIONHISTORY_H
#define CHATSESSIONHISTORY_H

#include <QString>
#include <QVector>
#include "constants.h"
//debe guardar un historial de la seccion actual mas detallada
struct TurnoConversacion {
    QString emisor;      // user / bot
    QString mensaje;
    qint64 timestamp;    // unix ms
};

class ChatSessionHistory
{
public:
    ChatSessionHistory();

    // Helpers solicitados
    void addUserTurn(const QString &mensaje, qint64 timestamp);
    void addBotTurn(const QString &mensaje, qint64 timestamp);

    QVector<TurnoConversacion> obtenerHistorialFiltrado(
        const QString &emisorFiltro = QString(),
        qint64 desde = 0,
        qint64 hasta = 0) const;

    void limpiarConversacion();

private:
    void registrarTurno(const QString &emisor,
                        const QString &mensaje,
                        qint64 timestamp);

    QVector<TurnoConversacion> historial;

    // Aliases a tus constantes
    static inline const QString &C_User = Constants::User;
    static inline const QString &C_Bot  = Constants::Bot;
};

#endif // CHATSESSIONHISTORY_H
