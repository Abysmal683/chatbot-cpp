#ifndef GAMEPLATFORMSDAO_H
#define GAMEPLATFORMSDAO_H
#include "baserelationdao.h"
#include "constants.h"
class GamePlatformsDAO : public BaseRelationDAO
{
public:
    GamePlatformsDAO(QSqlDatabase& db):BaseRelationDAO(
        Constants::Tables::GamePlatforms,
        Constants::Columns::GamePlatforms::GameId,
        Constants::Columns::GamePlatforms::PlatformId,
        db){}
};

#endif // GAMEPLATFORMSDAO_H
