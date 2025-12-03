#include "gamedao.h"

GameDAO::GameDAO(QSqlDatabase& db,
                 GameTagsDAO& tagRel,
                 GameGenresDAO& genreRel,
                 GamePlatformsDAO& platformRel)
    : BaseEntityDAO<Game>("games", db),
    tagRelation(tagRel),
    genreRelation(genreRel),
    platformRelation(platformRel)
{}
// ------------------------------
// MAPEAR QUERIES → Game
// ------------------------------
Game GameDAO::fromQuery(const QSqlQuery& q) const {
    Game g;
    g.id                  = q.value("id").toInt();
    g.title               = q.value("title").toString();
    g.rating              = q.value("rating").toInt();
    g.description         = q.value("description").toString();
    g.avg_playtime_minutes = q.value("avg_playtime_minutes").toInt();
    return g;
}

// ------------------------------
// BIND PARA INSERTAR
// ------------------------------
void GameDAO::bindInsert(QSqlQuery& q, const Game& g) const {
    q.prepare("INSERT INTO games "
              "(id, title, rating, description, avg_playtime_minutes) "
              "VALUES (NULL, :title, :rating, :desc, :play)");

    q.bindValue(":title", g.title);
    q.bindValue(":rating", g.rating);
    q.bindValue(":desc",  g.description);
    q.bindValue(":play",  g.avg_playtime_minutes);
}

// ------------------------------
// BIND PARA UPDATE
// ------------------------------
void GameDAO::bindUpdate(QSqlQuery& q, const Game& g) const {
    q.prepare("UPDATE games SET "
              " title = :title, "
              " rating = :rating, "
              " description = :desc, "
              " avg_playtime_minutes = :play "
              "WHERE id = :id");

    q.bindValue(":title", g.title);
    q.bindValue(":rating", g.rating);
    q.bindValue(":desc",  g.description);
    q.bindValue(":play",  g.avg_playtime_minutes);

    q.bindValue(":id", g.id);
}

// ------------------------------
// GET COMPLETO CON RELACIONES
// ------------------------------
Game GameDAO::getFull(int id) const {
    Game g = getById(id);
    if (g.id == 0) return g;

    g.tags      = tagRelation.getRights(id);
    g.genres    = genreRelation.getRights(id);
    g.platforms = platformRelation.getRights(id);
    return g;
}

QList<Game> GameDAO::getAllFull() const {
    QList<Game> list = getAll();
    for (Game& g : list) {
        g.tags      = tagRelation.getRights(g.id);
        g.genres    = genreRelation.getRights(g.id);
        g.platforms = platformRelation.getRights(g.id);
    }
    return list;
}
