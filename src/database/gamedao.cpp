#include "gamedao.h"
#include "gametagsdao.h"
#include "gameplatformsdao.h"
#include "gamegenresdao.h"

GameDAO::GameDAO(QSqlDatabase& db,
                 GameTagsDAO& tagRel,
                 GameGenresDAO& genreRel,
                 GamePlatformsDAO& platformRel)
    : BaseEntityDAO<Game>(T, db),
    tagRelation(tagRel),
    genreRelation(genreRel),
    platformRelation(platformRel)
{}

/* ----------------------------------------------------------
 * MAPEAR QUERY → Game
 * Uso q.record().value("col") para indexación por nombre
 * ----------------------------------------------------------*/
Game GameDAO::fromQuery(const QSqlQuery& q) const {
    Game g;
    g.id = q.value(C_Id).toInt();
    g.title = q.value(C_Title).toString();
    g.rating = q.value(C_Rating).toInt();
    g.description = q.value(C_Description).toString();
    g.avgPlaytime = q.value(C_AvgPlay).toInt();
    return g;
}

/* ----------------------------------------------------------
 * BIND INSERT
 * ----------------------------------------------------------*/
void GameDAO::bindInsert(QSqlQuery& q, const Game& g) const {
    // INSERT INTO games (title, rating, description, avgPlaytime) VALUES (:title, :rating, :desc, :play)
    q.prepare(QString("INSERT INTO %1 (%2, %3, %4, %5) "
                      "VALUES (:title, :rating, :desc, :play)")
                  .arg(T, C_Title, C_Rating, C_Description, C_AvgPlay));

    q.bindValue(":title", g.title);
    q.bindValue(":rating", g.rating);
    q.bindValue(":desc", g.description);
    q.bindValue(":play", g.avgPlaytime);
}

/* ----------------------------------------------------------
 * BIND UPDATE
 * ----------------------------------------------------------*/
void GameDAO::bindUpdate(QSqlQuery& q, const Game& g) const {
    // UPDATE games SET title = :title, rating = :rating, description = :desc, avgPlaytime = :play WHERE id = :id
    q.prepare(QString("UPDATE %1 SET %2 = :title, %3 = :rating, %4 = :desc, %5 = :play WHERE %6 = :id")
                  .arg(T, C_Title, C_Rating, C_Description, C_AvgPlay, C_Id));

    q.bindValue(":title", g.title);
    q.bindValue(":rating", g.rating);
    q.bindValue(":desc", g.description);
    q.bindValue(":play", g.avgPlaytime);
    q.bindValue(":id", g.id);
}

/* ----------------------------------------------------------
 * GET COMPLETO (con relaciones)
 * ----------------------------------------------------------*/
Game GameDAO::getFull(int id) const {
    Game g = getById(id);
    if (g.id == 0) return g;

    g.tags = tagRelation.getRights(id);
    g.genres = genreRelation.getRights(id);
    g.platforms = platformRelation.getRights(id);
    return g;
}

QList<Game> GameDAO::getAllFull() const {
    QList<Game> list = getAll();
    for (Game& g : list) {
        g.tags = tagRelation.getRights(g.id);
        g.genres = genreRelation.getRights(g.id);
        g.platforms = platformRelation.getRights(g.id);
    }
    return list;
}
