#include "basesimpledao.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "constants.h"

BaseSimpleDAO::BaseSimpleDAO(const QString& tableName, QSqlDatabase& db)
    : tableName(tableName), db(db)
{}

/* ============================================================
 * Obtener todos los registros (id, name)
 * ============================================================ */
QList<QPair<int, QString>> BaseSimpleDAO::getAll() const {
    QList<QPair<int, QString>> list;

    QSqlQuery q(db);
    QString sql = QString("SELECT %1, %2 FROM %3 ORDER BY %2 ASC").arg(
        Constants::Columns::GenericSimple::Id,
        Constants::Columns::GenericSimple::Name,
        tableName);

    if (!q.exec(sql)) {
        qCritical() << QString("Error getAll() en tabla %1: %2")
        .arg(tableName, q.lastError().text());
        return list;
    }

    while (q.next()) {
        list.append({
            q.value(0).toInt(),
            q.value(1).toString()
        });
    }

    return list;
}

/* ============================================================
 * Insertar
 * ============================================================ */
int BaseSimpleDAO::insert(const QString& name) const {
    QSqlQuery q(db);
    q.prepare(QString("INSERT INTO %1 (%2) VALUES (:name)").arg(
        tableName,
        Constants::Columns::GenericSimple::Name));

    q.bindValue(":name", name);

    if (!q.exec()) {
        qCritical() << QString("Error insert() en tabla %1: %2")
        .arg(tableName, q.lastError().text());
        return -1;
    }

    return q.lastInsertId().toInt();
}

/* ============================================================
 * Eliminar
 * ============================================================ */
bool BaseSimpleDAO::remove(int id) const {
    QSqlQuery q(db);
    q.prepare(QString("DELETE FROM %1 WHERE %2 = :id").arg(
        tableName,
        Constants::Columns::GenericSimple::Id));

    q.bindValue(":id", id);

    if (!q.exec()) {
        qCritical() << QString("Error remove() en tabla %1: %2")
        .arg(tableName, q.lastError().text());
        return false;
    }

    return true;
}

/* ============================================================
 * Modificar
 * ============================================================ */
bool BaseSimpleDAO::update(int id, const QString& name) const {
    QSqlQuery q(db);
    q.prepare(QString("UPDATE %1 SET %2 = :name WHERE %3 = :id").arg(
        tableName,
        Constants::Columns::GenericSimple::Name,
        Constants::Columns::GenericSimple::Id));

    q.bindValue(":name", name);
    q.bindValue(":id", id);

    if (!q.exec()) {
        qCritical() << QString("Error update() en tabla %1: %2")
        .arg(tableName, q.lastError().text());
        return false;
    }

    return true;
}

/* ============================================================
 * Verificar existencia
 * ============================================================ */
bool BaseSimpleDAO::exists(const QString& name) const {
    QSqlQuery q(db);
    q.prepare(QString("SELECT COUNT(*) FROM %1 WHERE %2 = :name").arg(
        tableName,
        Constants::Columns::GenericSimple::Name));

    q.bindValue(":name", name);

    if (!q.exec()) return false;
    if (!q.next()) return false;

    return q.value(0).toInt() > 0;
}

/* ============================================================
 * Obtener NAME por ID
 * ============================================================ */
QString BaseSimpleDAO::getNameById(int id) const {
    QSqlQuery q(db);
    q.prepare(QString("SELECT %1 FROM %2 WHERE %3 = :id").arg(
        Constants::Columns::GenericSimple::Name,
        tableName,
        Constants::Columns::GenericSimple::Id));

    q.bindValue(":id", id);

    if (!q.exec()) return {};
    if (!q.next()) return {};

    return q.value(0).toString();
}

/* ============================================================
 * Obtener ID por NAME
 * ============================================================ */
int BaseSimpleDAO::getIdByName(const QString& name) const {
    QSqlQuery q(db);
    q.prepare(QString("SELECT %1 FROM %2 WHERE %3 = :name").arg(
        Constants::Columns::GenericSimple::Id,
        tableName,
        Constants::Columns::GenericSimple::Name));

    q.bindValue(":name", name);

    if (!q.exec()) return -1;
    if (!q.next()) return -1;

    return q.value(0).toInt();
}

/* ============================================================
 * Contar registros
 * ============================================================ */
int BaseSimpleDAO::count() const {
    QSqlQuery q(db);
    q.prepare(QString("SELECT COUNT(*) FROM %1").arg(tableName));

    if (!q.exec()) return 0;
    if (!q.next()) return 0;

    return q.value(0).toInt();
}
