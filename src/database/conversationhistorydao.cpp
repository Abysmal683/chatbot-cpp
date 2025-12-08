#include "conversationhistorydao.h"
#include <QDateTime>
ConversationHistoryDAO::ConversationHistoryDAO(QSqlDatabase& db)
    : BaseEntityDAO<ConversationHistory>(T, db)
{}

// ----------------------------------------------
//   MAPEO DE FILA → ConversationHistory
// ----------------------------------------------
ConversationHistory ConversationHistoryDAO::fromQuery(const QSqlQuery& q) const {
    ConversationHistory m;
    m.id           = q.value(C_Id).toInt();
    m.user_message = q.value(C_UserMsg).toString();
    m.bot_message  = q.value(C_BotMsg).toString();
    m.timestamp    = q.value(C_Time).toString();
    return m;
}

// ----------------------------------------------
//   INSERT
// ----------------------------------------------


void ConversationHistoryDAO::bindInsert(QSqlQuery& q, const ConversationHistory& m) const
{
    QString timestamp = QDateTime::currentDateTime().toString(Qt::ISODate);

    q.prepare(QStringLiteral(
                  "INSERT INTO %1 (%2, %3, %4) VALUES (:u, :b, :t)"
                  ).arg(T, C_UserMsg, C_BotMsg, C_Time));

    q.bindValue(":u", m.user_message);
    q.bindValue(":b", m.bot_message);
    q.bindValue(":t", timestamp);
}

// ----------------------------------------------
//   UPDATE
// ----------------------------------------------
void ConversationHistoryDAO::bindUpdate(QSqlQuery& q, const ConversationHistory& m) const
{
    q.prepare(QStringLiteral(
                  "UPDATE %1 SET %2 = :u, %3 = :b WHERE %4 = :id"
                  ).arg(T, C_UserMsg, C_BotMsg, C_Id));

    q.bindValue(":u",  m.user_message);
    q.bindValue(":b",  m.bot_message);
    q.bindValue(":id", m.id);
}

// ----------------------------------------------
//   OBTENER ÚLTIMOS MENSAJES
// ----------------------------------------------
QList<ConversationHistory> ConversationHistoryDAO::getLastMessages(int limit) const
{
    QList<ConversationHistory> list;

    QSqlQuery q(db);
    q.prepare(QStringLiteral(
                  "SELECT %1, %2, %3, %4 "
                  "FROM %5 "
                  "ORDER BY %1 DESC "
                  "LIMIT :lim"
                  ).arg(C_Id, C_UserMsg, C_BotMsg, C_Time, T));

    q.bindValue(":lim", limit);

    if (!q.exec()) return list;

    while (q.next())
        list.append(fromQuery(q));

    return list;
}
