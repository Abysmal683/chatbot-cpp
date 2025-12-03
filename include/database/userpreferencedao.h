#ifndef USERPREFERENCEDAO_H
#define USERPREFERENCEDAO_H

#include "baseentitydao.h"
#include "userpreference.h"

class UserPreferenceDAO : public BaseEntityDAO<UserPreference>
{
public:
    explicit UserPreferenceDAO(QSqlDatabase& db);

    // Implementaciones obligatorias
    UserPreference fromQuery(const QSqlQuery& q) const override;
    void bindInsert(QSqlQuery& q, const UserPreference& m) const override;
    void bindUpdate(QSqlQuery& q, const UserPreference& m) const override;

    // Extra útil para tu IA
    UserPreference getByKey(const QString& key) const;
    bool exists(const QString& key) const;
};

#endif // USERPREFERENCEDAO_H
