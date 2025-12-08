#ifndef GAMESFTSDAO_H
#define GAMESFTSDAO_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "game.h"
#include "constants.h"

class GamesFtsDAO
{
public:
    explicit GamesFtsDAO(QSqlDatabase& db);

    // Búsquedas FTS
    QList<Game> search(const QString &term) const;
    QList<Game> searchTitle(const QString &term) const;
    QList<Game> searchDescription(const QString &term) const;

private:
    QSqlDatabase& db;

    // Conversión de query → Game
    QList<Game> mapQueryToGames(QSqlQuery& q) const;

    // Alias para facilitar lectura
    static inline const QString& T_Fts    = "games_fts";
    static inline const QString& T_Games  = Constants::Tables::Games;

    static inline const QString& C_Id        = Constants::Columns::Games::Id;
    static inline const QString& C_Title     = Constants::Columns::Games::Title;
    static inline const QString& C_Rating    = Constants::Columns::Games::Rating;
    static inline const QString& C_Description = Constants::Columns::Games::Description;
    static inline const QString& C_AvgPlay  = Constants::Columns::Games::AvgPlaytime;

};

#endif // GAMESFTSDAO_H
