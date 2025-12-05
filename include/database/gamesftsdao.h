#ifndef GAMESFTSDAO_H
#define GAMESFTSDAO_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include "game.h"

class GamesFtsDAO
{
public:
    explicit GamesFtsDAO(QSqlDatabase& db);

    QList<Game> search(const QString &term);
    QList<Game> searchTitle(const QString &term);
    QList<Game> searchDescription(const QString &term);

private:
    QSqlDatabase& db;
    QList<Game> mapQueryToGames(QSqlQuery& q);
};

#endif // GAMESFTSDAO_H
