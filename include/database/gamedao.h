#ifndef GAMEDAO_H
#define GAMEDAO_H
#include "baseentitydao.h"
#include "game.h"
#include "gametagsdao.h"
#include "gameplatformsdao.h"
#include "gamegenresdao.h"
class GameDAO : public BaseEntityDAO<Game>
{
public:
    GameDAO(QSqlDatabase& db,
            GameTagsDAO& tagRel,
            GameGenresDAO& genreRel,
            GamePlatformsDAO& platformRel);

    // Implementaciones obligatorias
    Game fromQuery(const QSqlQuery& q) const override;
    void bindInsert(QSqlQuery& q, const Game& g) const override;
    void bindUpdate(QSqlQuery& q, const Game& g) const override;

    // Métodos de acceso completo
    Game getFull(int id) const;
    QList<Game> getAllFull() const;
private:
    GameTagsDAO& tagRelation;
    GameGenresDAO& genreRelation;
    GamePlatformsDAO& platformRelation;
};


#endif // GAMEDAO_H
