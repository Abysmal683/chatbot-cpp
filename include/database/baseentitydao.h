#ifndef BASEENTITYDAO_H
#define BASEENTITYDAO_H

#include <QList>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "databasemanager.h"
template <typename T>
class BaseEntityDAO
{
public:
    explicit BaseEntityDAO(const QString& tableName)
        : table(tableName) {}

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
};

#include "baseentitydao.inl"

#endif // BASEENTITYDAO_H
