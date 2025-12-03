#include "keyworddao.h"

KeywordDAO::KeywordDAO(QSqlDatabase& db)
    : BaseEntityDAO("keywords", db)
{}

// ----------------------------
// fromQuery
// ----------------------------
Keyword KeywordDAO::fromQuery(const QSqlQuery& q) const {
    Keyword k;
    k.id       = q.value("id").toInt();
    k.keyword  = q.value("keyword").toString();
    k.category = q.value("category").toString();
    return k;
}

// ----------------------------
// bindInsert
// ----------------------------
void KeywordDAO::bindInsert(QSqlQuery& q, const Keyword& k) const {
    q.prepare("INSERT INTO keywords (id, keyword, category) "
              "VALUES (NULL, :keyword, :category)");

    q.bindValue(":keyword",  k.keyword);
    q.bindValue(":category", k.category);
}

// ----------------------------
// bindUpdate
// ----------------------------
void KeywordDAO::bindUpdate(QSqlQuery& q, const Keyword& k) const {
    q.prepare("UPDATE keywords "
              "SET keyword = :keyword, category = :category "
              "WHERE id = :id");

    q.bindValue(":keyword", k.keyword);
    q.bindValue(":category", k.category);
    q.bindValue(":id",      k.id);
}

// ----------------------------
// findByCategory
// ----------------------------
QList<Keyword> KeywordDAO::findByCategory(const QString& cat) const {
    QList<Keyword> list;
    QSqlQuery q(db);

    q.prepare("SELECT * FROM keywords WHERE category = :category ORDER BY keyword ASC");
    q.bindValue(":category", cat);

    if (!q.exec()) {
        qCritical() << "Error findByCategory():" << q.lastError().text();
        return list;
    }

    while (q.next())
        list.append(fromQuery(q));

    return list;
}
