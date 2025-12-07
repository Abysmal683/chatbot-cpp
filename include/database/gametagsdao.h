#ifndef GAMETAGSDAO_H
#define GAMETAGSDAO_H
#include "baserelationdao.h"
#include "constants.h"
class GameTagsDAO : public BaseRelationDAO
{
public:
    GameTagsDAO(QSqlDatabase& db):BaseRelationDAO(
        Constants::Tables::GameTags,
        Constants::Columns::GameTags::GameId,
        Constants::Columns::GameTags::TagId,
        db){}
};

#endif // GAMETAGSDAO_H
