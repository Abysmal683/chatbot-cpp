#ifndef KEYWORDDAO_H
#define KEYWORDDAO_H

#include "baseentitydao.h"
#include "keyword.h"
#include <QSqlDatabase>

class KeywordDAO : public BaseEntityDAO<Keyword>
{
public:
    explicit KeywordDAO(QSqlDatabase& db);

    // Implementaciones obligatorias del BaseEntityDAO
    Keyword fromQuery(const QSqlQuery& q) const override;
    void bindInsert(QSqlQuery& q, const Keyword& k) const override;
    void bindUpdate(QSqlQuery& q, const Keyword& k) const override;

    // Métodos extra (opcionales)
    QList<Keyword> findByCategory(const QString& cat) const;
};

#endif // KEYWORDDAO_H
