#include "tfidfvectorsdao.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>



/* ----------------------------------------------------------
 * MAPEAR QUERY → TFIDFVector
 * ----------------------------------------------------------*/
TFIDFVector TFIDFVectorDAO::fromQuery(const QSqlQuery& q) const {
    TFIDFVector v;
    v.ruleId = q.value(C_RuleId).toInt();
    v.token  = q.value(C_Token).toString();
    v.tfidf  = q.value(C_TFIDF).toDouble();
    return v;
}

/* ----------------------------------------------------------
 * INSERT
 * ----------------------------------------------------------*/
void TFIDFVectorDAO::bindInsert(QSqlQuery& q, const TFIDFVector& v) const {
    q.prepare(QString("INSERT INTO %1 (%2, %3, %4) "
                      "VALUES (:%2, :%3, :%4)")
                  .arg(T, C_RuleId, C_Token, C_TFIDF));
    q.bindValue(":" + C_RuleId, v.ruleId);
    q.bindValue(":" + C_Token,  v.token);
    q.bindValue(":" + C_TFIDF,  v.tfidf);
}

/* ----------------------------------------------------------
 * UPDATE
 * ----------------------------------------------------------*/
void TFIDFVectorDAO::bindUpdate(QSqlQuery& q, const TFIDFVector& v) const {
    q.prepare(QString("UPDATE %1 SET %3 = :%3 WHERE %2 = :%2 AND %4 = :%4")
                  .arg(T, C_RuleId, C_TFIDF, C_Token));
    q.bindValue(":" + C_TFIDF,  v.tfidf);
    q.bindValue(":" + C_RuleId, v.ruleId);
    q.bindValue(":" + C_Token,  v.token);
}

/* ----------------------------------------------------------
 * FUNCIONES ÚTILES
 * ----------------------------------------------------------*/
QList<TFIDFVector> TFIDFVectorDAO::getByRuleId(int ruleId) const {
    QList<TFIDFVector> results;
    QSqlQuery q(db);
    q.prepare(QString("SELECT * FROM %1 WHERE %2 = :id").arg(T, C_RuleId));
    q.bindValue(":id", ruleId);
    if (!q.exec()) {
        qWarning() << "Error getByRuleId:" << q.lastError().text();
        return results;
    }
    while (q.next()) results.append(fromQuery(q));
    return results;
}

bool TFIDFVectorDAO::removeByRuleId(int ruleId) const {
    QSqlQuery q(db);
    q.prepare(QString("DELETE FROM %1 WHERE %2 = :id").arg(T, C_RuleId));
    q.bindValue(":id", ruleId);
    if (!q.exec()) {
        qWarning() << "Error removeByRuleId:" << q.lastError().text();
        return false;
    }
    return true;
}
