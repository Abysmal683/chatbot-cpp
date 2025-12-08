#ifndef RULESDAO_H
#define RULESDAO_H

#include "baseentitydao.h"
#include "rule.h"
#include "constants.h"
#include <QList>

class RulesDAO : public BaseEntityDAO<Rule>
{
public:
    explicit RulesDAO(QSqlDatabase& db);

    /* FUNCIONES ÚTILES */
    QList<Rule> getByTrigger(const QString& trigger) const;
    QList<Rule> getByPriority(int minPriority) const;
    Rule getBestMatch(const QString& trigger) const;

    // Nueva función: reglas activas
    QList<Rule> getActiveRules() const;

private:
    Rule fromQuery(const QSqlQuery& q) const override;
    void bindInsert(QSqlQuery& q, const Rule& r) const override;
    void bindUpdate(QSqlQuery& q, const Rule& r) const override;

    /* ALIAS USADOS POR EL ESTÁNDAR */
    const QString T  = Constants::Tables::Rules;
    const QString C_Id       = Constants::Columns::Rules::Id;
    const QString C_Trigger  = Constants::Columns::Rules::Trigger;
    const QString C_Response = Constants::Columns::Rules::Response;
    const QString C_Priority = Constants::Columns::Rules::Priority;
    const QString C_Category = Constants::Columns::Rules::Category;
    const QString C_Source   = Constants::Columns::Rules::Source;
    const QString C_IsActive = Constants::Columns::Rules::IsActive;
    const QString C_CreatedAt = Constants::Columns::Rules::CreatedAt;
    const QString C_UpdatedAt = Constants::Columns::Rules::UpdatedAt;
};

#endif // RULESDAO_H
