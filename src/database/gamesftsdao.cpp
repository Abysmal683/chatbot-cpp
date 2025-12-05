#include "gamesftsdao.h"
#include <QSqlError>
#include <QDebug>

GamesFtsDAO::GamesFtsDAO(QSqlDatabase& db) : db(db)
{
}

QList<Game> GamesFtsDAO::search(const QString &term)
{
    QSqlQuery q(db);

    q.prepare(R"(
        SELECT
            g.id,
            g.title,
            g.rating,
            g.description,
            g.avg_playtime_minutes
        FROM games_fts f
        JOIN games g ON g.id = f.content_rowid
        WHERE f MATCH :term
        ORDER BY bm25(f)
    )");

    q.bindValue(":term", term);

    if (!q.exec()) {
        qWarning() << "Error en búsqueda FTS:" << q.lastError().text();
    }

    return mapQueryToGames(q);
}

QList<Game> GamesFtsDAO::searchTitle(const QString &term)
{
    return search(QString("title:%1").arg(term));
}

QList<Game> GamesFtsDAO::searchDescription(const QString &term)
{
    return search(QString("description:%1").arg(term));
}

QList<Game> GamesFtsDAO::mapQueryToGames(QSqlQuery &q)
{
    QList<Game> results;

    while (q.next()) {
        Game g;

        g.id                   = q.value(0).toInt();
        g.title                = q.value(1).toString();
        g.rating               = q.value(2).toInt();
        g.description          = q.value(3).toString();
        g.avg_playtime_minutes = q.value(4).toInt();

        // tags, genres, platforms → se cargan luego por otros DAO N-N

        results.append(g);
    }

    return results;
}
