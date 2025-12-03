#ifndef MEMORYSHORTTERMDAO_H
#define MEMORYSHORTTERMDAO_H
#include "baseentitydao.h"
#include "memoryshortterm.h"

class MemoryShortTermDAO : public BaseEntityDAO<MemoryShortTerm>
{
public:
    explicit MemoryShortTermDAO(QSqlDatabase& db);

    // Implementaciones obligatorias
    MemoryShortTerm fromQuery(const QSqlQuery& q) const override;
    void bindInsert(QSqlQuery& q, const MemoryShortTerm& m) const override;
    void bindUpdate(QSqlQuery& q, const MemoryShortTerm& m) const override;
};

#endif // MEMORYSHORTTERMDAO_H
