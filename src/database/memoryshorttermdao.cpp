#include "memoryshorttermdao.h"

MemoryShortTermDAO::MemoryShortTermDAO(QSqlDatabase& db)
    : BaseEntityDAO<MemoryShortTerm>("memory_short_term", db)
{
}

MemoryShortTerm MemoryShortTermDAO::fromQuery(const QSqlQuery& q) const {
    MemoryShortTerm m;
    m.id = q.value("id").toInt();
    m.value = q.value("value").toString();
    m.expires_at = q.value("expires_at").toString();
    m.related_intent = q.value("related_intent").toString();
    m.created_at = q.value("created_at").toString();
    return m;
}

void MemoryShortTermDAO::bindInsert(
    QSqlQuery& q,
    const MemoryShortTerm& m) const
{
    q.prepare(R"(
        INSERT INTO memory_short_term
        (id, value, expires_at, related_intent, created_at)
        VALUES (NULL, :value, :expires_at, :related_intent, :created_at)
    )");

    q.bindValue(":value", m.value);
    q.bindValue(":expires_at", m.expires_at.isEmpty() ? QVariant() : m.expires_at);
    q.bindValue(":related_intent", m.related_intent.isEmpty() ? QVariant() : m.related_intent);
    q.bindValue(":created_at", m.created_at);
}

void MemoryShortTermDAO::bindUpdate(
    QSqlQuery& q,
    const MemoryShortTerm& m) const
{
    q.prepare(R"(
        UPDATE memory_short_term
        SET value = :value,
            expires_at = :expires_at,
            related_intent = :related_intent,
            created_at = :created_at
        WHERE id = :id
    )");

    q.bindValue(":value", m.value);
    q.bindValue(":expires_at", m.expires_at.isEmpty() ? QVariant() : m.expires_at);
    q.bindValue(":related_intent", m.related_intent.isEmpty() ? QVariant() : m.related_intent);
    q.bindValue(":created_at", m.created_at);
    q.bindValue(":id", m.id);
}
