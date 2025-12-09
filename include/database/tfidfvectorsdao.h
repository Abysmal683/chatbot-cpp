#ifndef TFIDFVECTORDAO_H
#define TFIDFVECTORDAO_H

#include "baseentitydao.h"
#include "tfidfvector.h" // aquí va el struct TFIDFVector
#include "constants.h"
#include <QList>

class TFIDFVectorDAO : public BaseEntityDAO<TFIDFVector>
{
public:
    explicit TFIDFVectorDAO(QSqlDatabase& db)
        : BaseEntityDAO<TFIDFVector>(T, db)
    {}

    /* FUNCIONES ÚTILES */
    QList<TFIDFVector> getByRuleId(int ruleId) const;
    bool removeByRuleId(int ruleId) const;

private:
    TFIDFVector fromQuery(const QSqlQuery& q) const override;
    void bindInsert(QSqlQuery& q, const TFIDFVector& v) const override;
    void bindUpdate(QSqlQuery& q, const TFIDFVector& v) const override;

    /* ALIAS USADOS POR EL ESTÁNDAR */
    const QString T      = Constants::Tables::TFIDFVectors;
    const QString C_RuleId = Constants::Columns::TFIDFVectors::RuleId;
    const QString C_Token  = Constants::Columns::TFIDFVectors::Token;
    const QString C_TFIDF  = Constants::Columns::TFIDFVectors::TFIDF;
};

#endif // TFIDFVECTORDAO_H
