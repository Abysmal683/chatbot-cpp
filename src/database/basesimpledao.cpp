#include "basesimpledao.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

BaseSimpleDAO::BaseSimpleDAO(const QString& tableName)
    : table(tableName)
{}

QList<QPair<int, QString>> BaseSimpleDAO::getAll() const {
    QList<QPair<int, QString>> list;
    QSqlQuery q(DataBaseManager::instance().getDatabase());
    QString sql = "SELECT id, name FROM " + table + " ORDER BY name ASC";
    if(!q.exec(sql)) {
        qCritical() << "Error getAll() en tabla" << table << ":" << q.lastError().text();
        return list;
    }

    while (q.next()) {
        list.append({ q.value(0).toInt(), q.value(1).toString() });
    }
    return list;
}

int BaseSimpleDAO::insert(const QString& name) const {
    QSqlQuery q(DataBaseManager::instance().getDatabase());
    q.prepare("INSERT INTO " + table + " (name) VALUES (:name)");
    q.bindValue(":name", name);
    DataBaseManager::instance().beginTransaction();
    if (!q.exec()) {
        qCritical() << "Error insert() en tabla" << table << ":" << q.lastError().text();
        DataBaseManager::instance().rollback();
        return -1;
    }
    DataBaseManager::instance().commit();
    return q.lastInsertId().toInt();
}

bool BaseSimpleDAO::remove(int id) const {
    QSqlQuery q(DataBaseManager::instance().getDatabase());
    q.prepare("DELETE FROM " + table + " WHERE id = :id");
    q.bindValue(":id", id);
    DataBaseManager::instance().beginTransaction();
    if (!q.exec()) {
        qCritical() << "Error remove() en tabla" << table << ":" << q.lastError().text();
        DataBaseManager::instance().rollback();
        return false;
    }
    DataBaseManager::instance().commit();
    return true;
}

bool BaseSimpleDAO::update(int id, const QString& name) const {
    QSqlQuery q(DataBaseManager::instance().getDatabase());
    q.prepare("UPDATE " + table + " SET name = :name WHERE id = :id");
    q.bindValue(":name", name);
    q.bindValue(":id", id);
    DataBaseManager::instance().beginTransaction();
    if (!q.exec()) {
        qCritical() << "Error update() en tabla" << table << ":" << q.lastError().text();
        DataBaseManager::instance().rollback();
        return false;
    }
    DataBaseManager::instance().commit();
    return true;
}

bool BaseSimpleDAO::exists(const QString& name) const {
    QSqlQuery q(DataBaseManager::instance().getDatabase());
    q.prepare("SELECT COUNT(*) FROM " + table + " WHERE name = :name");
    q.bindValue(":name", name);

    if (!q.exec()) return false;
    if (q.next()) return q.value(0).toInt() > 0;
    return false;
}

QString BaseSimpleDAO::getNameById(int id) const {
    QSqlQuery q(DataBaseManager::instance().getDatabase());
    q.prepare("SELECT name FROM " + table + " WHERE id = :id");
    q.bindValue(":id", id);

    if (!q.exec()) return {};

    if (q.next()) return q.value(0).toString();
    return {};
}

int BaseSimpleDAO::getIdByName(const QString& name) const {
    QSqlQuery q(DataBaseManager::instance().getDatabase());
    q.prepare("SELECT id FROM " + table + " WHERE name = :name");
    q.bindValue(":name", name);

    if (!q.exec()) return -1;

    if (q.next()) return q.value(0).toInt();
    return -1;
}

int BaseSimpleDAO::count() const {
    QSqlQuery q("SELECT COUNT(*) FROM " + table, DataBaseManager::instance().getDatabase());
    if (!q.exec()) return 0;
    if (q.next()) return q.value(0).toInt();
    return 0;
}
