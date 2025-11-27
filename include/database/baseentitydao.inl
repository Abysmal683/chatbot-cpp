
#pragma ONCE
#include "baseentitydao.h"
#include <QList>
template <typename T>
T BaseEntityDAO<T>::getById(int id) const {
    QSqlQuery q(DataBaseManager::instance().getDatabase());
    q.prepare("SELECT * FROM " + table + " WHERE id = :id");
    q.bindValue(":id", id);

    if (!q.exec() || !q.next()) return T();
    return fromQuery(q);
}

template <typename T>
QList<T> BaseEntityDAO<T>::getAll() const {
    QList<T> list;
    QSqlQuery q("SELECT * FROM " + table + " ORDER BY id ASC",
                DataBaseManager::instance().getDatabase());

    if (!q.exec()) return list;

    while (q.next()) list.append(fromQuery(q));
    return list;
}

template <typename T>
int BaseEntityDAO<T>::insert(const T& entity) const {
    QString sql = "INSERT INTO " + table + " VALUES (NULL"; // id AUTOINCREMENT
    QSqlQuery q(DataBaseManager::instance().getDatabase());

    // Prepara: INSERT INTO table VALUES (NULL, ?, ?, ?, ...)
    q.prepare(sql + ")");

    bindInsert(q, entity);

    if (!q.exec()) {
        qCritical() << "Error insert() en tabla" << table << ":" << q.lastError().text();
        return -1;
    }
    return q.lastInsertId().toInt();
}

template <typename T>
bool BaseEntityDAO<T>::update(const T& entity) const {
    QSqlQuery q(DataBaseManager::instance().getDatabase());

    // El DAO concreto arma el query con bindUpdate()
    bindUpdate(q, entity);

    if (!q.exec()) {
        qCritical() << "Error update() en tabla" << table << ":" << q.lastError().text();
        return false;
    }
    return true;
}

template <typename T>
bool BaseEntityDAO<T>::remove(int id) const {
    QSqlQuery q(DataBaseManager::instance().getDatabase());
    q.prepare("DELETE FROM " + table + " WHERE id = :id");
    q.bindValue(":id", id);

    if (!q.exec()) return false;
    return true;
}
