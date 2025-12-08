#include "gamesftsdao.h"

GamesFtsDAO::GamesFtsDAO(QSqlDatabase& db) : db(db) {}

// ---------------------------------------------------------
// MAPEO → Game
// ---------------------------------------------------------
QList<Game> GamesFtsDAO::mapQueryToGames(QSqlQuery& q) const
{
    QList<Game> results;

    while (q.next()) {
        Game g;
        g.id          = q.value(C_Id).toInt();
        g.title       = q.value(C_Title).toString();
        g.rating      = q.value(C_Rating).toInt();
        g.description = q.value(C_Description).toString();
        g.avgPlaytime = q.value(C_AvgPlay).toInt();
        // tags/genres/platforms se pueden cargar después si se desea
        results.append(g);
    }

    return results;

}

// ---------------------------------------------------------
// Búsqueda FTS general
// ---------------------------------------------------------
QList<Game> GamesFtsDAO::search(const QString &term) const
{
    QSqlQuery q(db);

    QString sql = QString(R"(
    SELECT g.%1, g.%2, g.%3, g.%4, g.%5
    FROM %6 f
    JOIN %7 g ON g.%1 = f.content_rowid
    WHERE f MATCH :term
    ORDER BY bm25(f)
)").arg(C_Id, C_Title, C_Rating, C_Description, C_AvgPlay, T_Fts, T_Games);

    q.prepare(sql);
    q.bindValue(":term", term);

    if (!q.exec()) {
        qWarning() << "Error en búsqueda FTS:" << q.lastError().text();
    }

    return mapQueryToGames(q);

}

// ---------------------------------------------------------
// Búsqueda por título
// ---------------------------------------------------------
QList<Game> GamesFtsDAO::searchTitle(const QString &term) const
{
    return search(QString("title:%1").arg(term));
}

// ---------------------------------------------------------
// Búsqueda por descripción
// ---------------------------------------------------------
QList<Game> GamesFtsDAO::searchDescription(const QString &term) const
{
    return search(QString("description:%1").arg(term));
}
