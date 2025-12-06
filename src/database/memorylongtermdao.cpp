#include "memorylongtermdao.h"
#include <QDateTime>
MemoryLongTermDAO::MemoryLongTermDAO(QSqlDatabase& db)
    : BaseEntityDAO("memory_long_term", db)
{}

// -------------------------------------------
// Convertir fila SQL → struct
// -------------------------------------------
MemoryLongTerm MemoryLongTermDAO::fromQuery(const QSqlQuery& q) const {
    MemoryLongTerm m;
    m.id = q.value("id").toInt();
    m.key = q.value("key").toString();
    m.value = q.value("value").toString();
    m.importance = q.value("importance").toInt();
    m.created_at = q.value("created_at").toString();
    return m;
}

// -------------------------------------------
// INSERT
// -------------------------------------------
void MemoryLongTermDAO::bindInsert(QSqlQuery& q, const MemoryLongTerm& m) const {
    q.prepare(
        "INSERT INTO memory_long_term (id, key, value, importance, created_at) "
        "VALUES (NULL, :key, :value, :importance, :created_at)"
        );

    q.bindValue(":key", m.key);
    q.bindValue(":value", m.value);
    q.bindValue(":importance", m.importance);
    q.bindValue(":created_at", m.created_at.isEmpty()
       ? QDateTime::currentDateTime().toString(Qt::ISODate)
       : m.created_at);
}

// -------------------------------------------
// UPDATE
// -------------------------------------------
void MemoryLongTermDAO::bindUpdate(QSqlQuery& q, const MemoryLongTerm& m) const {
    q.prepare(
        "UPDATE memory_long_term "
        "SET key = :key, value = :value, importance = :importance "
        "WHERE id = :id"
        );

    q.bindValue(":key", m.key);
    q.bindValue(":value", m.value);
    q.bindValue(":importance", m.importance);
    q.bindValue(":id", m.id);
}

// -------------------------------------------
// QUERY EXTRA
// -------------------------------------------
QList<MemoryLongTerm> MemoryLongTermDAO::findByKey(const QString& key) const {
    QList<MemoryLongTerm> list;
    QSqlQuery q(db);

    q.prepare("SELECT * FROM memory_long_term WHERE key = :key ORDER BY created_at DESC");
    q.bindValue(":key", key);

    if (!q.exec()) return list;

    while (q.next())
        list.append(fromQuery(q));

    return list;
}

QList<MemoryLongTerm> MemoryLongTermDAO::findImportant(int minImportance) const {
    QList<MemoryLongTerm> list;
    QSqlQuery q(db);

    q.prepare("SELECT * FROM memory_long_term WHERE importance >= :imp ORDER BY importance DESC");
    q.bindValue(":imp", minImportance);

    if (!q.exec()) return list;

    while (q.next())
        list.append(fromQuery(q));

    return list;
}
QList<QString> MemoryLongTermDAO::listKeys() const
{
    QList<QString> keys;
    QSqlQuery q(db);

    q.prepare("SELECT DISTINCT key FROM memory_long_term ORDER BY key ASC");

    if (!q.exec()) return keys;

    while (q.next())
        keys.append(q.value(0).toString());

    return keys;
}
