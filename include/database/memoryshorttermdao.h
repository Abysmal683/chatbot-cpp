#ifndef MEMORYSHORTTERMDAO_H
#define MEMORYSHORTTERMDAO_H

#include "baseentitydao.h"
#include "memoryshortterm.h"
#include "constants.h"

class MemoryShortTermDAO : public BaseEntityDAO<MemoryShortTerm>
{
public:
    explicit MemoryShortTermDAO(QSqlDatabase& db);

    // --- FUNCIONES ÚTILES ---
    bool removeExpired() const;                       // elimina memorias vencidas
    QList<MemoryShortTerm> getValid() const;          // solo memorias vigentes
    QList<MemoryShortTerm> findByIntent(const QString& intent) const;
    void extendLifetime(int id, int minutes) const;   // extiende expiración

private:

    // Implementaciones BaseEntityDAO
    MemoryShortTerm fromQuery(const QSqlQuery& q) const override;
    void bindInsert(QSqlQuery& q, const MemoryShortTerm& m) const override;
    void bindUpdate(QSqlQuery& q, const MemoryShortTerm& m) const override;

    // inlines (alias de tabla / columnas)
    static inline const QString& T  = Constants::Tables::MemoryShortTerm;

    static inline const QString& C_Id     = Constants::Columns::MemoryShortTerm::Id;
    static inline const QString& C_Val    = Constants::Columns::MemoryShortTerm::Value;
    static inline const QString& C_Exp    = Constants::Columns::MemoryShortTerm::ExpiresAt;
    static inline const QString& C_Int    = Constants::Columns::MemoryShortTerm::RelatedIntent;
    static inline const QString& C_Crt    = Constants::Columns::MemoryShortTerm::CreatedAt;
};

#endif // MEMORYSHORTTERMDAO_H
