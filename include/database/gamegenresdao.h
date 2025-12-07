#ifndef GAMEGENRESDAO_H
#define GAMEGENRESDAO_H
#include "baserelationdao.h"
#include "constants.h"
class GameGenresDAO: public BaseRelationDAO
{
public:
    GameGenresDAO(QSqlDatabase& db):BaseRelationDAO(
        Constants::Tables::GameGenres,
        Constants::Columns::GameGenres::GameId,
        Constants::Columns::GameGenres::GenreId,
        db){}
};
#endif // GAMEGENRESDAO_H
