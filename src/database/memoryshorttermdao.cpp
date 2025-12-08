#include "memoryshorttermdao.h"
#include <QDateTime>

// ----------------------------------
MemoryShortTermDAO::MemoryShortTermDAO(QSqlDatabase& db)
    : BaseEntityDAO(T, db)
{
}

// ----------------------------------
MemoryShortTerm MemoryShortTermDAO::fromQuery(const QSqlQuery& q) const {
    MemoryShortTerm m;

    m.id            = q.value(C_Id).toInt();
    m.value         = q.value(C_Val).toString();
    m.expires_at    = q.value(C_Exp).toString();
    m.related_intent= q.value(C_Int).toString();
    m.created_at    = q.value(C_Crt).toString();

    return m;
}

// ----------------------------------
void MemoryShortTermDAO::bindInsert(QSqlQuery& q, const MemoryShortTerm& m) const {
    q.prepare(QStringLiteral(
                  "INSERT INTO %1 (%2, %3, %4, %5, %6) "
                  "VALUES (NULL, :value, :expires, :intent, :created)"
                  ).arg(T, C_Val, C_Exp, C_Int, C_Crt));

    q.bindValue(":value",  m.value);
    q.bindValue(":expires", m.expires_at.isEmpty() ? QVariant() : m.expires_at);
    q.bindValue(":intent",  m.related_intent.isEmpty() ? QVariant() : m.related_intent);
    q.bindValue(":created", m.created_at);
}

// ----------------------------------
void MemoryShortTermDAO::bindUpdate(QSqlQuery& q, const MemoryShortTerm& m) const {
    q.prepare(QStringLiteral(
                  "UPDATE %1 SET "
                  "%2 = :value, %3 = :expires, %4 = :intent, %5 = :created "
                  "WHERE %6 = :id"
                  ).arg(T, C_Val, C_Exp, C_Int, C_Crt, C_Id));

    q.bindValue(":value",   m.value);
    q.bindValue(":expires", m.expires_at.isEmpty() ? QVariant() : m.expires_at);
    q.bindValue(":intent",  m.related_intent.isEmpty() ? QVariant() : m.related_intent);
    q.bindValue(":created", m.created_at);
    q.bindValue(":id",      m.id);
}

// ==================================================
//      FUNCIONES EXTRA ÚTILES PARA SHORT TERM
// ==================================================

// Elimina memorias vencidas
bool MemoryShortTermDAO::removeExpired() const {
    QSqlQuery q(db);
    q.prepare(QString("DELETE FROM %1 WHERE %2 < datetime('now') AND %2 IS NOT NULL")
                  .arg(T, C_Exp));

    return q.exec();
}

// Obtiene solo memorias vigentes
QList<MemoryShortTerm> MemoryShortTermDAO::getValid() const {
    QList<MemoryShortTerm> list;
    QSqlQuery q(db);

    q.prepare(QString(
                  "SELECT * FROM %1 "
                  "WHERE (%2 IS NULL OR %2 >= datetime('now')) "
                  "ORDER BY %3 DESC"
                  ).arg(T, C_Exp, C_Crt));

    if (!q.exec()) return list;

    while (q.next())
        list.append(fromQuery(q));

    return list;
}

// Buscar por intención
QList<MemoryShortTerm> MemoryShortTermDAO::findByIntent(const QString& intent) const {
    QList<MemoryShortTerm> list;
    QSqlQuery q(db);

    q.prepare(QString("SELECT * FROM %1 WHERE %2 = :intent ORDER BY %3 DESC")
                  .arg(T, C_Int, C_Crt));

    q.bindValue(":intent", intent);

    if (!q.exec()) return list;

    while (q.next())
        list.append(fromQuery(q));

    return list;
}

// Extiende la expiración X minutos
void MemoryShortTermDAO::extendLifetime(int id, int minutes) const {
    QSqlQuery q(db);
    q.prepare(QString(
                  "UPDATE %1 SET %2 = datetime(%2, :mins) WHERE %3 = :id"
                  ).arg(T, C_Exp, C_Id));

    q.bindValue(":mins", QString("+%1 minutes").arg(minutes));
    q.bindValue(":id", id);

    q.exec();
}
