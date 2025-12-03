#ifndef LOGDAO_H
#define LOGDAO_H

#include "baseentitydao.h"
#include "logentry.h"

class LogDAO : public BaseEntityDAO<LogEntry>
{
public:
    explicit LogDAO(QSqlDatabase& db)
        : BaseEntityDAO("logs", db) {}

protected:
    LogEntry fromQuery(const QSqlQuery& q) const override;
    void bindInsert(QSqlQuery& q, const LogEntry& e) const override;
    void bindUpdate(QSqlQuery& q, const LogEntry& e) const override;
};
#endif // LOGDAO_H
