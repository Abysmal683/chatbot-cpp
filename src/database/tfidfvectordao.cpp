#include "tfidfvectordao.h"
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
    q.prepare(QString("INSERT INTO %1 (%2, %3,%4) VALUES (:%2, :%3,:%4)")
                  .arg(T, C_RuleId, C_Token, C_TFIDF));

    q.bindValue(":" + C_RuleId, v.ruleId);
    q.bindValue(":" + C_Token,  v.token);
    // TF-IDF puede calcularse en código, si se quiere persistir:
    q.bindValue(":" + C_TFIDF, v.tfidf);
}

/* ----------------------------------------------------------
 * UPDATE
 * ----------------------------------------------------------*/
void TFIDFVectorDAO::bindUpdate(QSqlQuery& q, const TFIDFVector& v) const {
    q.prepare(QString("UPDATE %1 SET %2 = :%2 WHERE %3 = :%3")
                  .arg(T, C_TFIDF, C_RuleId));

    q.bindValue(":" + C_TFIDF, v.tfidf);
    q.bindValue(":" + C_RuleId, v.ruleId);
}
/* ==========================================================
 * FUNCIONES ESPECÍFICAS
 * ==========================================================*/
QList<TFIDFVector> TFIDFVectorDAO::getByRuleId(int ruleId) const {
    QList<TFIDFVector> results;
    QSqlQuery q(db);
    q.prepare(QString("SELECT * FROM %1 WHERE %2 = :rid").arg(T, C_RuleId));
    q.bindValue(":rid", ruleId);

    if (!q.exec()) {
        qWarning() << "Error getByRuleId:" << q.lastError().text();
        return results;
    }

    while (q.next())
        results.append(fromQuery(q));

    return results;
}

bool TFIDFVectorDAO::removeByRuleId(int ruleId) const {
    QSqlQuery q(db);
    q.prepare(QString("DELETE FROM %1 WHERE %2 = :rid").arg(T, C_RuleId));
    q.bindValue(":rid", ruleId);

    if (!q.exec()) {
        qWarning() << "Error removeByRuleId:" << q.lastError().text();
        return false;
    }

    return true;
}
