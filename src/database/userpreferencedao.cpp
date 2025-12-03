#include "userpreferencedao.h"

UserPreferenceDAO::UserPreferenceDAO(QSqlDatabase& db)
    : BaseEntityDAO<UserPreference>("user_preferences", db)
{}

// ---------------------------------------------------------
//  MAPEO → struct UserPreference
// ---------------------------------------------------------
UserPreference UserPreferenceDAO::fromQuery(const QSqlQuery& q) const
{
    UserPreference u;
    u.id         = q.value("id").toInt();
    u.key        = q.value("key").toString();
    u.value      = q.value("value").toString();
    u.updated_at = q.value("updated_at").toString();
    return u;
}

// ---------------------------------------------------------
//  INSERT
// ---------------------------------------------------------
void UserPreferenceDAO::bindInsert(QSqlQuery& q, const UserPreference& m) const
{
    q.prepare("INSERT INTO user_preferences (key, value, updated_at) "
              "VALUES (:key, :value, datetime('now'))");

    q.bindValue(":key", m.key);
    q.bindValue(":value", m.value);
}

// ---------------------------------------------------------
//  UPDATE
// ---------------------------------------------------------
void UserPreferenceDAO::bindUpdate(QSqlQuery& q, const UserPreference& m) const
{
    q.prepare("UPDATE user_preferences "
              "SET key = :key, value = :value, updated_at = datetime('now') "
              "WHERE id = :id");

    q.bindValue(":key", m.key);
    q.bindValue(":value", m.value);
    q.bindValue(":id", m.id);
}

// ---------------------------------------------------------
//  EXTRA
// ---------------------------------------------------------
UserPreference UserPreferenceDAO::getByKey(const QString& key) const
{
    QSqlQuery q(db);
    q.prepare("SELECT * FROM user_preferences WHERE key = :k");
    q.bindValue(":k", key);

    if (!q.exec() || !q.next())
        return {};

    return fromQuery(q);
}

bool UserPreferenceDAO::exists(const QString& key) const
{
    QSqlQuery q(db);
    q.prepare("SELECT COUNT(*) FROM user_preferences WHERE key = :k");
    q.bindValue(":k", key);

    if (!q.exec())
        return false;

    return q.next() && q.value(0).toInt() > 0;
}
