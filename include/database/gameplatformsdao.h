#ifndef GAMEPLATFORMSDAO_H
#define GAMEPLATFORMSDAO_H
#include "baserelationdao.h"
class GamePlatformsDAO : public BaseRelationDAO
{
public:
    GamePlatformsDAO(QSqlDatabase& db):BaseRelationDAO("game_platforms",
                          "game_id",
                          "platform_id",
                          db){}
};

#endif // GAMEPLATFORMSDAO_H
