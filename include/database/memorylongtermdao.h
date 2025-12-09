#ifndef MEMORYLONGTERMDAO_H
#define MEMORYLONGTERMDAO_H

#include "baseentitydao.h"
#include "memorylongterm.h"
#include "constants.h"

class MemoryLongTermDAO : public BaseEntityDAO<MemoryLongTerm>
{
public:
    explicit MemoryLongTermDAO(QSqlDatabase& db);

    // Funciones adicionales
    QList<MemoryLongTerm> findByKey(const QString& key) const;
    QList<MemoryLongTerm> findImportant(int minImportance) const;
    QList<QString> listKeys() const;

private:
    // Implementación obligatoria
    MemoryLongTerm fromQuery(const QSqlQuery& q) const override;
    void bindInsert(QSqlQuery& q, const MemoryLongTerm& m) const override;
    void bindUpdate(QSqlQuery& q, const MemoryLongTerm& m) const override;

    // alias inline
    static inline const QString& T        = Constants::Tables::MemoryLongTerm;
    static inline const QString& C_Id     = Constants::Columns::MemoryLongTerm::Id;
    static inline const QString& C_Key    = Constants::Columns::MemoryLongTerm::Key;
    static inline const QString& C_Val    = Constants::Columns::MemoryLongTerm::Value;
    static inline const QString& C_Imp    = Constants::Columns::MemoryLongTerm::Importance;
    static inline const QString& C_Created= Constants::Columns::MemoryLongTerm::CreatedAt;
};

#endif // MEMORYLONGTERMDAO_H
