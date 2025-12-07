#include "baserelationdao.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

BaseRelationDAO::BaseRelationDAO(const QString& tableName,
                                 const QString& leftColumn,
                                 const QString& rightColumn,
                                 QSqlDatabase& db)
    : tableName(tableName),
    leftCol(leftColumn),
    rightCol(rightColumn),
    db(db)
{}

bool BaseRelationDAO::add(int L, int R) const {
    QSqlQuery q(db);
    q.prepare(QString("INSERT INTO %1 (%2, %3) VALUES (:l, :r)")
                  .arg(tableName, leftCol, rightCol));
    q.bindValue(":l", L);
    q.bindValue(":r", R);

    if (!q.exec()) {
        qCritical() << "Error add() en tabla" << tableName << ":" << q.lastError().text();
        return false;
    }
    return true;
}

bool BaseRelationDAO::remove(int L, int R) const {
    QSqlQuery q(db);
    q.prepare(QString("DELETE FROM %1 WHERE %2 = :l AND %3 = :r")
                  .arg(tableName, leftCol, rightCol));
    q.bindValue(":l", L);
    q.bindValue(":r", R);
    return q.exec();
}

bool BaseRelationDAO::clearLeft(int L) const {
    QSqlQuery q(db);
    q.prepare(QString("DELETE FROM %1 WHERE %2 = :l")
                  .arg(tableName, leftCol));
    q.bindValue(":l", L);
    return q.exec();
}

QList<int> BaseRelationDAO::getRights(int L) const {
    QList<int> list;
    QSqlQuery q(db);

    q.prepare(QString("SELECT %1 FROM %2 WHERE %3 = :l")
                  .arg(rightCol, tableName, leftCol));
    q.bindValue(":l", L);

    if (!q.exec()) return list;
    while (q.next()) list.append(q.value(0).toInt());

    return list;
}

QList<int> BaseRelationDAO::getLefts(int R) const {
    QList<int> list;
    QSqlQuery q(db);

    q.prepare(QString("SELECT %1 FROM %2 WHERE %3 = :r")
                  .arg(leftCol, tableName, rightCol));
    q.bindValue(":r", R);

    if (!q.exec()) return list;
    while (q.next()) list.append(q.value(0).toInt());

    return list;
}

bool BaseRelationDAO::exists(int L, int R) const {
    QSqlQuery q(db);
    q.prepare(QString("SELECT COUNT(*) FROM %1 WHERE %2 = :l AND %3 = :r")
                  .arg(tableName, leftCol, rightCol));
    q.bindValue(":l", L);
    q.bindValue(":r", R);

    if (!q.exec()) return false;
    return q.next() && q.value(0).toInt() > 0;
}
