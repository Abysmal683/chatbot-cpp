#ifndef BASEENTITYDAO_H
#define BASEENTITYDAO_H

#include <QList>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

template <typename T>
class BaseEntityDAO {
public:
    explicit BaseEntityDAO(const QString& tableName, QSqlDatabase& db)
        : tableName(tableName), db(db) {}

    virtual ~BaseEntityDAO() = default;

    // Métodos obligatorios
    virtual T fromQuery(const QSqlQuery& q) const = 0;
    virtual void bindInsert(QSqlQuery& q, const T& entity) const = 0;
    virtual void bindUpdate(QSqlQuery& q, const T& entity) const = 0;

    // CRUD
    T getById(int id) const;
    QList<T> getAll() const;
    int insert(const T& entity) const;
    bool update(const T& entity) const;
    bool remove(int id) const;

protected:
    QString tableName;
    QSqlDatabase& db;
};

/* ------------------------------ */
/*          IMPLEMENTACIÓN        */
/* ------------------------------ */

template <typename T>
T BaseEntityDAO<T>::getById(int id) const {
    QSqlQuery q(db);
    q.prepare(QString("SELECT * FROM %1 WHERE id = :id").arg(tableName));
    q.bindValue(":id", id);

    return (q.exec() && q.next()) ? fromQuery(q) : T();
}

template <typename T>
QList<T> BaseEntityDAO<T>::getAll() const {
    QList<T> list;
    QSqlQuery q(QString("SELECT * FROM %1 ORDER BY id ASC").arg(tableName), db);

    if (q.exec())
        while (q.next()) list.append(fromQuery(q));

    return list;
}

template <typename T>
int BaseEntityDAO<T>::insert(const T& entity) const {
    QSqlQuery q(db);
    bindInsert(q, entity);

    if (!q.exec()) {
        qCritical() << "[ERROR insert]" << tableName << ":" << q.lastError().text();
        return -1;
    }
    return q.lastInsertId().toInt();
}

template <typename T>
bool BaseEntityDAO<T>::update(const T& entity) const {
    QSqlQuery q(db);
    bindUpdate(q, entity);

    if (!q.exec()) {
        qCritical() << "[ERROR update]" << tableName << ":" << q.lastError().text();
        return false;
    }
    return true;
}

template <typename T>
bool BaseEntityDAO<T>::remove(int id) const {
    QSqlQuery q(db);
    q.prepare(QString("DELETE FROM %1 WHERE id = :id").arg(tableName));
    q.bindValue(":id", id);
    return q.exec();
}

#endif // BASEENTITYDAO_H
