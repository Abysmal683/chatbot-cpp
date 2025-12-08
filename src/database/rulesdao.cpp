#include "rulesdao.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

RulesDAO::RulesDAO(QSqlDatabase& db)
    : BaseEntityDAO<Rule>(T, db)
{}

/* ----------------------------------------------------------

* MAPEAR QUERY → Rule
* ----------------------------------------------------------*/
Rule RulesDAO::fromQuery(const QSqlQuery& q) const {
    Rule r;
    r.id       = q.value(C_Id).toInt();
    r.trigger  = q.value(C_Trigger).toString();
    r.response = q.value(C_Response).toString();
    r.priority = q.value(C_Priority).toInt();
    return r;
}

/* ----------------------------------------------------------

* INSERT

* ----------------------------------------------------------*/
void RulesDAO::bindInsert(QSqlQuery& q, const Rule& r) const {
    q.prepare(QString("INSERT INTO %1 (%2, %3, %4) "
                      "VALUES (:%2, :%3, :%4)")
                  .arg(T, C_Trigger, C_Response, C_Priority));

    q.bindValue(":" + C_Trigger,  r.trigger);
    q.bindValue(":" + C_Response, r.response);
    q.bindValue(":" + C_Priority, r.priority);
}

/* ----------------------------------------------------------

* UPDATE

* ----------------------------------------------------------*/
void RulesDAO::bindUpdate(QSqlQuery& q, const Rule& r) const {
    q.prepare(QString("UPDATE %1 SET "
                      "%2 = :%2, %3 = :%3, %4 = :%4 "
                      "WHERE %5 = :%5")
                  .arg(T, C_Trigger, C_Response, C_Priority, C_Id));

    q.bindValue(":" + C_Trigger,  r.trigger);
    q.bindValue(":" + C_Response, r.response);
    q.bindValue(":" + C_Priority, r.priority);
    q.bindValue(":" + C_Id,       r.id);
}

/* ==========================================================

* FUNCIONES ÚTILES
* ==========================================================*/
QList<Rule> RulesDAO::getByTrigger(const QString& trigger) const {
    QList<Rule> results;
    QSqlQuery q(db);
    q.prepare(QString("SELECT * FROM %1 WHERE %2 = :trigger").arg(T, C_Trigger));
    q.bindValue(":trigger", trigger);
    if (!q.exec()) {
        qWarning() << "Error getByTrigger:" << q.lastError().text();
        return results;
    }
    while (q.next()) results.append(fromQuery(q));
    return results;
}

QList<Rule> RulesDAO::getByPriority(int minPriority) const {
    QList<Rule> results;
    QSqlQuery q(db);
    q.prepare(QString("SELECT * FROM %1 WHERE %2 >= :p ORDER BY %2 DESC").arg(T, C_Priority));
    q.bindValue(":p", minPriority);
    if (!q.exec()) {
        qWarning() << "Error getByPriority:" << q.lastError().text();
        return results;
    }
    while (q.next()) results.append(fromQuery(q));
    return results;
}

Rule RulesDAO::getBestMatch(const QString& trigger) const {
    QSqlQuery q(db);
    q.prepare(QString("SELECT * FROM %1 WHERE %2 = :t ORDER BY %3 DESC LIMIT 1")
                  .arg(T, C_Trigger, C_Priority));
    q.bindValue(":t", trigger);
    if (!q.exec() || !q.next()) {
        qWarning() << "Error getBestMatch:" << q.lastError().text();
        return {};
    }
    return fromQuery(q);
}
