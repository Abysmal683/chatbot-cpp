#ifndef BASEENTITYDAO_H
#define BASEENTITYDAO_H

#include <QList>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
template <typename T>
class BaseEntityDAO
{
public:
    explicit BaseEntityDAO(const QString& tableName,QSqlDatabase& db)
        : table(tableName),db(db) {}

    virtual ~BaseEntityDAO() = default;

    // Métodos que cada DAO concreto debe implementar
    virtual T fromQuery(const QSqlQuery& q) const = 0;
    virtual void bindInsert(QSqlQuery& q, const T& entity) const = 0;
    virtual void bindUpdate(QSqlQuery& q, const T& entity) const = 0;

    // CRUD genérico
    T getById(int id) const;
    QList<T> getAll() const;
    int insert(const T& entity) const;
    bool update(const T& entity) const;
    bool remove(int id) const;

protected:
    QString table;
    QSqlDatabase& db;
};

template <typename T>
T BaseEntityDAO<T>::getById(int id) const {
    QSqlQuery q(db);
    q.prepare("SELECT * FROM " + table + " WHERE id = :id");
    q.bindValue(":id", id);

    if (!q.exec() || !q.next()) return T();
    return fromQuery(q);
}

template <typename T>
QList<T> BaseEntityDAO<T>::getAll() const {
    QList<T> list;
    QSqlQuery q("SELECT * FROM " + table + " ORDER BY id ASC",
                db);

    if (!q.exec()) return list;

    while (q.next()) list.append(fromQuery(q));
    return list;
}

template <typename T>
int BaseEntityDAO<T>::insert(const T& entity) const {
    QSqlQuery q(db);

    bindInsert(q, entity);

    if (!q.exec()) {
        qCritical() << "Error insert() en tabla" << table << ":" << q.lastError().text();
        return -1;
    }
    return q.lastInsertId().toInt();
}

template <typename T>
bool BaseEntityDAO<T>::update(const T& entity) const {
    QSqlQuery q(db);

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
    QSqlQuery q(db);
    q.prepare("DELETE FROM " + table + " WHERE id = :id");
    q.bindValue(":id", id);

    if (!q.exec()) return false;
    return true;
}

#endif // BASEENTITYDAO_H
