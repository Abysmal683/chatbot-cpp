#ifndef MEMORYLONGTERMDAO_H
#define MEMORYLONGTERMDAO_H

#include "baseentitydao.h"
#include "memorylongterm.h"

class MemoryLongTermDAO : public BaseEntityDAO<MemoryLongTerm>
{
public:
    explicit MemoryLongTermDAO(QSqlDatabase& db);

    // Implementaciones requeridas por BaseEntityDAO
    MemoryLongTerm fromQuery(const QSqlQuery& q) const override;
    void bindInsert(QSqlQuery& q, const MemoryLongTerm& m) const override;
    void bindUpdate(QSqlQuery& q, const MemoryLongTerm& m) const override;

    // Extras útiles para esta tabla
    QList<MemoryLongTerm> findByKey(const QString& key) const;
    QList<MemoryLongTerm> findImportant(int minImportance) const;
    QList<QString> listKeys() const;
};

#endif // MEMORYLONGTERMDAO_H
