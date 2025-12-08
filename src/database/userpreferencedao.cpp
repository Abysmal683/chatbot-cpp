#include "userpreferencedao.h"

/* ============================================================
 *  CONSTRUCTOR
 * ============================================================ */
UserPreferenceDAO::UserPreferenceDAO(QSqlDatabase& db)
    : BaseEntityDAO<UserPreference>(T, db)
{}

/* ============================================================
 *  MAPEO → UserPreference
 * ============================================================ */
UserPreference UserPreferenceDAO::fromQuery(const QSqlQuery& q) const
{
    UserPreference u;
    u.id         = q.value(C_Id).toInt();
    u.key        = q.value(C_Key).toString();
    u.value      = q.value(C_Value).toString();
    u.updated_at = q.value(C_UpdatedAt).toString();
    return u;
}

/* ============================================================
 *  INSERT
 * ============================================================ */
void UserPreferenceDAO::bindInsert(QSqlQuery& q, const UserPreference& m) const
{
    q.prepare(QString("INSERT INTO %1 (%2, %3, %4) "
                      "VALUES (:%2, :%3, datetime('now'))")
                  .arg(T, C_Key, C_Value, C_UpdatedAt));

    q.bindValue(QString(":%1").arg(C_Key),   m.key);
    q.bindValue(QString(":%1").arg(C_Value), m.value);
}

/* ============================================================
 *  UPDATE
 * ============================================================ */
void UserPreferenceDAO::bindUpdate(QSqlQuery& q, const UserPreference& m) const
{
    q.prepare(QString("UPDATE %1 SET %2 = :%2, %3 = :%3, %4 = datetime('now') "
                      "WHERE %5 = :%5")
                  .arg(T, C_Key, C_Value, C_UpdatedAt, C_Id));

    q.bindValue(QString(":%1").arg(C_Key),   m.key);
    q.bindValue(QString(":%1").arg(C_Value), m.value);
    q.bindValue(QString(":%1").arg(C_Id),    m.id);
}

/* ============================================================
 *  EXTRA: BUSCAR POR CLAVE
 * ============================================================ */
UserPreference UserPreferenceDAO::getByKey(const QString& key) const
{
    QSqlQuery q(db);

    q.prepare(QString("SELECT * FROM %1 WHERE %2 = :key")
                  .arg(T, C_Key));
    q.bindValue(":key", key);

    if (!q.exec() || !q.next())
        return {};

    return fromQuery(q);
}

/* ============================================================
 *  EXTRA: EXISTS()
 * ============================================================ */
bool UserPreferenceDAO::exists(const QString& key) const
{
    QSqlQuery q(db);

    q.prepare(QString("SELECT COUNT(*) FROM %1 WHERE %2 = :key")
                  .arg(T, C_Key));
    q.bindValue(":key", key);

    if (!q.exec()) return false;

    return q.next() && q.value(0).toInt() > 0;
}
