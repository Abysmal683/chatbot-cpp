#ifndef LOGDAO_H
#define LOGDAO_H

#include "baseentitydao.h"
#include "logentry.h"
#include "constants.h"

class LogDAO : public BaseEntityDAO<LogEntry>
{
public:
    explicit LogDAO(QSqlDatabase& db);
    // Extra útil: obtener últimos N logs
    QList<LogEntry> getLast(int limit) const;

private:
    // Alias inline (igual estilo estandarizado)
    static inline const QString& T       = Constants::Tables::Logs;

    LogEntry fromQuery(const QSqlQuery& q) const override;
    void bindInsert(QSqlQuery& q, const LogEntry& e) const override;
    void bindUpdate(QSqlQuery& q, const LogEntry& e) const override;

    static inline const QString& C_Id    = Constants::Columns::Logs::Id;
    static inline const QString& C_Level = Constants::Columns::Logs::Level;
    static inline const QString& C_Msg   = Constants::Columns::Logs::Message;
    static inline const QString& C_Time  = Constants::Columns::Logs::CreatedAt;
};

#endif // LOGDAO_H
