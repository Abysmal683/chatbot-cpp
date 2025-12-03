#include "conversationhistorydao.h"

ConversationHistoryDAO::ConversationHistoryDAO(QSqlDatabase& db)
    : BaseEntityDAO("conversation_history", db)
{}

// ----------------------------
//   MAPEO DE FILAS → ENTITY
// ----------------------------
ConversationHistory ConversationHistoryDAO::fromQuery(const QSqlQuery& q) const {
    ConversationHistory m;
    m.id = q.value("id").toInt();
    m.user_message = q.value("user_message").toString();
    m.bot_message = q.value("bot_message").toString();
    m.timestamp = q.value("current_timestamp").toString();
    return m;
}

// ----------------------------
//   INSERT
// ----------------------------
void ConversationHistoryDAO::bindInsert(QSqlQuery& q, const ConversationHistory& m) const
{
    q.prepare(
        "INSERT INTO conversation_history "
        "(id, user_message, bot_message) "
        "VALUES (NULL, :u, :b)"
        // current_timestamp lo llena SQLite
        );

    q.bindValue(":u", m.user_message);
    q.bindValue(":b", m.bot_message);
}

// ----------------------------
//   UPDATE
// ----------------------------
void ConversationHistoryDAO::bindUpdate(QSqlQuery& q, const ConversationHistory& m) const
{
    q.prepare(
        "UPDATE conversation_history SET "
        "user_message = :u, "
        "bot_message = :b "
        "WHERE id = :id"
        );

    q.bindValue(":u", m.user_message);
    q.bindValue(":b", m.bot_message);
    q.bindValue(":id", m.id);
}
