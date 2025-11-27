#include "baserelationdao.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

BaseRelationDAO::BaseRelationDAO(const QString& tableName,
                                 const QString& leftColumn,
                                 const QString& rightColumn)
    : table(tableName),
    leftCol(leftColumn),
    rightCol(rightColumn)
{}

bool BaseRelationDAO::add(int L, int R) const {
    QSqlQuery q(DataBaseManager::instance().getDatabase());
    q.prepare("INSERT INTO " + table +
              " (" + leftCol + ", " + rightCol + ") VALUES (:l, :r)");
    q.bindValue(":l", L);
    q.bindValue(":r", R);

    if (!q.exec()) {
        qCritical() << "Error add() en tabla" << table << ":" << q.lastError().text();
        return false;
    }
    return true;
}

bool BaseRelationDAO::remove(int L, int R) const {
    QSqlQuery q(DataBaseManager::instance().getDatabase());
    q.prepare("DELETE FROM " + table +
              " WHERE " + leftCol + " = :l AND " + rightCol + " = :r");
    q.bindValue(":l", L);
    q.bindValue(":r", R);
    return q.exec();
}

bool BaseRelationDAO::clearLeft(int L) const {
    QSqlQuery q(DataBaseManager::instance().getDatabase());
    q.prepare("DELETE FROM " + table +
              " WHERE " + leftCol + " = :l");
    q.bindValue(":l", L);
    return q.exec();
}

QList<int> BaseRelationDAO::getRights(int L) const {
    QList<int> list;
    QSqlQuery q(DataBaseManager::instance().getDatabase());
    q.prepare("SELECT " + rightCol + " FROM " + table +
              " WHERE " + leftCol + " = :l");
    q.bindValue(":l", L);

    if (!q.exec()) return list;

    while (q.next()) list.append(q.value(0).toInt());
    return list;
}

QList<int> BaseRelationDAO::getLefts(int R) const {
    QList<int> list;
    QSqlQuery q(DataBaseManager::instance().getDatabase());
    q.prepare("SELECT " + leftCol + " FROM " + table +
              " WHERE " + rightCol + " = :r");
    q.bindValue(":r", R);

    if (!q.exec()) return list;

    while (q.next()) list.append(q.value(0).toInt());
    return list;
}

bool BaseRelationDAO::exists(int L, int R) const {
    QSqlQuery q(DataBaseManager::instance().getDatabase());
    q.prepare("SELECT COUNT(*) FROM " + table +
              " WHERE " + leftCol + " = :l AND " + rightCol + " = :r");
    q.bindValue(":l", L);
    q.bindValue(":r", R);

    if (!q.exec()) return false;

    if (q.next()) return q.value(0).toInt() > 0;
    return false;
}
