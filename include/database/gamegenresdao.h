#ifndef GAMEGENRESDAO_H
#define GAMEGENRESDAO_H
#include "baserelationdao.h"
class GameGenresDAO: public BaseRelationDAO
{
public:
    GameGenresDAO(QSqlDatabase& db):BaseRelationDAO("game_genres",
                          "game_id",
                          "genre_id",
                          db){}
};
#endif // GAMEGENRESDAO_H
