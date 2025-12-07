#include "logdao.h"

LogDAO::LogDAO(QSqlDatabase& db)
    : BaseEntityDAO<LogEntry>(T, db)
{}

/* ----------------------------------------------------------
 * MAPEAR DB → LogEntry
 * ----------------------------------------------------------*/
LogEntry LogDAO::fromQuery(const QSqlQuery& q) const {
    LogEntry e;
    e.id         = q.value(C_Id).toInt();
    e.level      = q.value(C_Level).toString();
    e.message    = q.value(C_Msg).toString();
    e.created_at = q.value(C_Time).toString();
    return e;
}

/* ----------------------------------------------------------
 * INSERT
 * ----------------------------------------------------------*/
void LogDAO::bindInsert(QSqlQuery& q, const LogEntry& e) const {
    q.prepare(QString(
                  "INSERT INTO %1 (%2, %3, %4) "
                  "VALUES (:level, :message, :created_at)"
                  ).arg(T, C_Level, C_Msg, C_Time));

    q.bindValue(":level",   e.level);
    q.bindValue(":message", e.message);

    // Si no se envía created_at, SQLite insertará datetime('now')
    if (e.created_at.isEmpty())
        q.bindValue(":created_at", QVariant());
    else
        q.bindValue(":created_at", e.created_at);
}

/* ----------------------------------------------------------
 * UPDATE
 * ----------------------------------------------------------*/
void LogDAO::bindUpdate(QSqlQuery& q, const LogEntry& e) const {
    q.prepare(QString(
                  "UPDATE %1 SET %2 = :level, %3 = :message, %4 = :created_at WHERE %5 = :id"
                  ).arg(T, C_Level, C_Msg, C_Time, C_Id));

    q.bindValue(":level",      e.level);
    q.bindValue(":message",    e.message);
    q.bindValue(":created_at", e.created_at);
    q.bindValue(":id",         e.id);
}

/* ----------------------------------------------------------
 * GET LAST N LOGS
 * ----------------------------------------------------------*/
QList<LogEntry> LogDAO::getLast(int limit) const {
    QList<LogEntry> list;

    QSqlQuery q(db);
    q.prepare(QString(
                  "SELECT * FROM %1 ORDER BY %2 DESC LIMIT :limit"
                  ).arg(T, C_Time));

    q.bindValue(":limit", limit);

    if (q.exec())
        while (q.next())
            list.append(fromQuery(q));

    return list;
}
