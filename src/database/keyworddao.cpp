#include "keyworddao.h"

KeywordDAO::KeywordDAO(QSqlDatabase& db)
    : BaseEntityDAO<Keyword>(T, db)
{}

/* ----------------------------------------------------------
 * MAPEAR QUERY → Keyword
 * ----------------------------------------------------------*/
Keyword KeywordDAO::fromQuery(const QSqlQuery& q) const {
    Keyword k;
    k.id       = q.value(C_Id).toInt();
    k.keyword  = q.value(C_Key).toString();
    k.category = q.value(C_Cat).toString();
    return k;
}

/* ----------------------------------------------------------
 * INSERT
 * ----------------------------------------------------------*/
void KeywordDAO::bindInsert(QSqlQuery& q, const Keyword& k) const {
    q.prepare(QString("INSERT INTO %1 (%2, %3) "
                      "VALUES (:keyword, :category)")
                  .arg(T, C_Key, C_Cat));

    q.bindValue(":keyword",  k.keyword);
    q.bindValue(":category", k.category);
}

/* ----------------------------------------------------------
 * UPDATE
 * ----------------------------------------------------------*/
void KeywordDAO::bindUpdate(QSqlQuery& q, const Keyword& k) const {
    q.prepare(QString("UPDATE %1 SET %2 = :keyword, %3 = :category "
                      "WHERE %4 = :id")
                  .arg(T, C_Key, C_Cat, C_Id));

    q.bindValue(":keyword",  k.keyword);
    q.bindValue(":category", k.category);
    q.bindValue(":id",       k.id);
}

/* ----------------------------------------------------------
 * FILTRAR POR CATEGORÍA
 * ----------------------------------------------------------*/
QList<Keyword> KeywordDAO::findByCategory(const QString& category) const {
    QList<Keyword> list;
    QSqlQuery q(db);

    q.prepare(QString("SELECT * FROM %1 WHERE %2 = :category ORDER BY %3 ASC")
                  .arg(T, C_Cat, C_Key));

    q.bindValue(":category", category);
    q.exec();

    while (q.next())
        list.append(fromQuery(q));

    return list;
}

/* ----------------------------------------------------------
 * BÚSQUEDA FLEXIBLE
 * ----------------------------------------------------------*/
QList<Keyword> KeywordDAO::search(const QString& text) const {
    QList<Keyword> list;
    QSqlQuery q(db);

    q.prepare(QString("SELECT * FROM %1 WHERE %2 LIKE :text ORDER BY %2 ASC")
                  .arg(T, C_Key));

    q.bindValue(":text", "%" + text + "%");
    q.exec();

    while (q.next())
        list.append(fromQuery(q));

    return list;
}
