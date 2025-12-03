#ifndef GAMETAGSDAO_H
#define GAMETAGSDAO_H
#include "baserelationdao.h"
class GameTagsDAO : public BaseRelationDAO
{
public:
    GameTagsDAO(QSqlDatabase& db):BaseRelationDAO("game_tags",
                          "game_id",
                          "tag_id",
                          db){}
};

#endif // GAMETAGSDAO_H
