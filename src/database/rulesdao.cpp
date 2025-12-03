#include "rulesdao.h"

RulesDAO::RulesDAO(QSqlDatabase& db)
    : BaseEntityDAO("rules", db)
{}

// ---------------------------
// Convertir fila → Rule
// ---------------------------
Rule RulesDAO::fromQuery(const QSqlQuery& q) const {
    Rule r;
    r.id       = q.value("id").toInt();
    r.trigger  = q.value("trigger").toString();
    r.response = q.value("response").toString();
    r.priority = q.value("priority").toInt();
    return r;
}

// ---------------------------
// INSERT
// ---------------------------
void RulesDAO::bindInsert(QSqlQuery& q, const Rule& r) const {
    q.prepare(
        "INSERT INTO rules (trigger, response, priority) "
        "VALUES (:trigger, :response, :priority)"
        );
    q.bindValue(":trigger",  r.trigger);
    q.bindValue(":response", r.response);
    q.bindValue(":priority", r.priority);
}

// ---------------------------
// UPDATE
// ---------------------------
void RulesDAO::bindUpdate(QSqlQuery& q, const Rule& r) const {
    q.prepare(
        "UPDATE rules SET "
        "trigger = :trigger, "
        "response = :response, "
        "priority = :priority "
        "WHERE id = :id"
        );
    q.bindValue(":trigger",  r.trigger);
    q.bindValue(":response", r.response);
    q.bindValue(":priority", r.priority);
    q.bindValue(":id",       r.id);
}
