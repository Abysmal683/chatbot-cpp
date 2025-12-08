#ifndef GAMEDAO_H
#define GAMEDAO_H

#include "baseentitydao.h"
#include "game.h"
#include "constants.h"

class GameTagsDAO;
class GameGenresDAO;
class GamePlatformsDAO;

class GameDAO : public BaseEntityDAO<Game>
{
public:
    GameDAO(QSqlDatabase& db,
            GameTagsDAO& tagRel,
            GameGenresDAO& genreRel,
            GamePlatformsDAO& platformRel);

    // Métodos de acceso completo (incluyen relaciones)
    Game getFull(int id) const;
    QList<Game> getAllFull() const;

private:
    GameTagsDAO& tagRelation;
    GameGenresDAO& genreRelation;
    GamePlatformsDAO& platformRelation;

    // Implementaciones obligatorias
    Game fromQuery(const QSqlQuery& q) const override;
    void bindInsert(QSqlQuery& q, const Game& g) const override;
    void bindUpdate(QSqlQuery& q, const Game& g) const override;

    // Alias inline para facilitar el uso en .cpp
    static inline const QString& T = Constants::Tables::Games;
    static inline const QString& C_Id = Constants::Columns::Games::Id;
    static inline const QString& C_Title = Constants::Columns::Games::Title;
    static inline const QString& C_Description = Constants::Columns::Games::Description;
    static inline const QString& C_Rating = Constants::Columns::Games::Rating;
    static inline const QString& C_AvgPlay = Constants::Columns::Games::AvgPlaytime;
};

#endif // GAMEDAO_H
