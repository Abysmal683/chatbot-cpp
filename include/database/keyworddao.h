#ifndef KEYWORDDAO_H
#define KEYWORDDAO_H

#include "baseentitydao.h"
#include "keyword.h"
#include "constants.h"

class KeywordDAO : public BaseEntityDAO<Keyword>
{
public:
    explicit KeywordDAO(QSqlDatabase& db);

    // Implementaciones obligatorias
    Keyword fromQuery(const QSqlQuery& q) const override;
    void bindInsert(QSqlQuery& q, const Keyword& k) const override;
    void bindUpdate(QSqlQuery& q, const Keyword& k) const override;

    // Métodos adicionales
    QList<Keyword> findByCategory(const QString& category) const;
    QList<Keyword> search(const QString& text) const;

private:
    // Alias inline (igual estructura que GameDAO)
    static inline const QString& T       = Constants::Tables::Keywords;

    static inline const QString& C_Id     = Constants::Columns::Keywords::Id;
    static inline const QString& C_Key    = Constants::Columns::Keywords::Keyword;
    static inline const QString& C_Cat    = Constants::Columns::Keywords::Category;
};

#endif // KEYWORDDAO_H
