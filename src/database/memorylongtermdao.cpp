#include "memorylongtermdao.h"
#include <QDateTime>

MemoryLongTermDAO::MemoryLongTermDAO(QSqlDatabase& db)
    : BaseEntityDAO(T, db)
{}

// -------------------------------------------
// fromQuery
// -------------------------------------------
MemoryLongTerm MemoryLongTermDAO::fromQuery(const QSqlQuery& q) const {
    MemoryLongTerm m;

    m.id         = q.value(C_Id).toInt();
    m.key        = q.value(C_Key).toString();
    m.value      = q.value(C_Val).toString();
    m.importance = q.value(C_Imp).toInt();
    m.created_at = q.value(C_Created).toString();

    return m;
}

// -------------------------------------------
// INSERT
// -------------------------------------------
void MemoryLongTermDAO::bindInsert(QSqlQuery& q, const MemoryLongTerm& m) const {
    q.prepare(QString(
                  "INSERT INTO %1 (%2, %3, %4, %5, %6) "
                  "VALUES (NULL, :key, :value, :importance, :created)"
                  ).arg(T, C_Key, C_Val, C_Imp, C_Created));

    q.bindValue(":key", m.key);
    q.bindValue(":value", m.value);
    q.bindValue(":importance", m.importance);

    q.bindValue(":created",
                m.created_at.isEmpty()
                    ? QDateTime::currentDateTime().toString(Qt::ISODate)
                    : m.created_at
                );
}

// -------------------------------------------
// UPDATE
// -------------------------------------------
void MemoryLongTermDAO::bindUpdate(QSqlQuery& q, const MemoryLongTerm& m) const {
    q.prepare(QString(
                  "UPDATE %1 SET %2 = :key, %3 = :value, %4 = :importance "
                  "WHERE %5 = :id"
                  ).arg(T, C_Key, C_Val, C_Imp, C_Id));

    q.bindValue(":key", m.key);
    q.bindValue(":value", m.value);
    q.bindValue(":importance", m.importance);
    q.bindValue(":id", m.id);
}

// -------------------------------------------
// findByKey
// -------------------------------------------
QList<MemoryLongTerm> MemoryLongTermDAO::findByKey(const QString& key) const {
    QList<MemoryLongTerm> list;
    QSqlQuery q(db);

    q.prepare(QString("SELECT * FROM %1 WHERE %2 = :key ORDER BY %3 DESC")
                  .arg(T, C_Key, C_Created));
    q.bindValue(":key", key);

    if (!q.exec()) return list;

    while (q.next())
        list.append(fromQuery(q));

    return list;
}

// -------------------------------------------
// findImportant
// -------------------------------------------
QList<MemoryLongTerm> MemoryLongTermDAO::findImportant(int minImportance) const {
    QList<MemoryLongTerm> list;
    QSqlQuery q(db);

    q.prepare(QString("SELECT * FROM %1 WHERE %2 >= :imp ORDER BY %2 DESC")
                  .arg(T, C_Imp));
    q.bindValue(":imp", minImportance);

    if (!q.exec()) return list;

    while (q.next())
        list.append(fromQuery(q));

    return list;
}

// -------------------------------------------
// listKeys
// -------------------------------------------
QList<QString> MemoryLongTermDAO::listKeys() const {
    QList<QString> keys;
    QSqlQuery q(db);

    q.prepare(QString("SELECT DISTINCT %1 FROM %2 ORDER BY %1 ASC")
                  .arg(C_Key, T));

    if (!q.exec()) return keys;

    while (q.next())
        keys.append(q.value(0).toString());

    return keys;
}
