#ifndef USERPREFERENCEDAO_H
#define USERPREFERENCEDAO_H

#include "baseentitydao.h"
#include "userpreference.h"
#include "constants.h"

class UserPreferenceDAO : public BaseEntityDAO<UserPreference>
{
public:
    explicit UserPreferenceDAO(QSqlDatabase& db);

    // Implementaciones obligatorias
    UserPreference fromQuery(const QSqlQuery& q) const override;
    void bindInsert(QSqlQuery& q, const UserPreference& m) const override;
    void bindUpdate(QSqlQuery& q, const UserPreference& m) const override;

    // Funciones útiles
    UserPreference getByKey(const QString& key) const;
    bool exists(const QString& key) const;

private:
    // Alias inline como GameDAO
    static inline const QString& T       = Constants::Tables::UserPreferences;
    static inline const QString& C_Id    = Constants::Columns::UserPreferences::Id;
    static inline const QString& C_Key   = Constants::Columns::UserPreferences::Key;
    static inline const QString& C_Value = Constants::Columns::UserPreferences::Value;
    static inline const QString& C_UpdatedAt = Constants::Columns::UserPreferences::UpdatedAt;
};

#endif // USERPREFERENCEDAO_H
