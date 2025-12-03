#ifndef RULESDAO_H
#define RULESDAO_H

#include "baseentitydao.h"
#include "rule.h"

class RulesDAO : public BaseEntityDAO<Rule>
{
public:
    explicit RulesDAO(QSqlDatabase& db);

protected:
    Rule fromQuery(const QSqlQuery& q) const override;
    void bindInsert(QSqlQuery& q, const Rule& r) const override;
    void bindUpdate(QSqlQuery& q, const Rule& r) const override;
};
#endif // RULESDAO_H
