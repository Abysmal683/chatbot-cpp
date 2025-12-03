#include "logdao.h"

LogEntry LogDAO::fromQuery(const QSqlQuery& q) const {
    LogEntry e;
    e.id         = q.value("id").toInt();
    e.level      = q.value("level").toString();
    e.message    = q.value("message").toString();
    e.created_at = q.value("created_at").toString();
    return e;
}

void LogDAO::bindInsert(QSqlQuery& q, const LogEntry& e) const {
    q.prepare("INSERT INTO logs (id, level, message, created_at) "
              "VALUES (NULL, :level, :message, :created_at)");

    q.bindValue(":level",      e.level);
    q.bindValue(":message",    e.message);

    // si viene vacío, dejamos que SQLite ponga datetime('now')
    if (e.created_at.isEmpty())
        q.bindValue(":created_at", QVariant());
    else
        q.bindValue(":created_at", e.created_at);
}

void LogDAO::bindUpdate(QSqlQuery& q, const LogEntry& e) const {
    q.prepare("UPDATE logs SET "
              "level = :level, "
              "message = :message, "
              "created_at = :created_at "
              "WHERE id = :id");

    q.bindValue(":level",      e.level);
    q.bindValue(":message",    e.message);
    q.bindValue(":created_at", e.created_at);
    q.bindValue(":id",         e.id);
}
