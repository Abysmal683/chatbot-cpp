#ifndef GAME_H
#define GAME_H
#include <QString>
#include <QList>

struct Game {
    int id = 0;
    QString title;
    int rating = 1;
    QString description;
    int avg_playtime_minutes;

    // solo IDs
    QList<int> tags;
    QList<int> genres;
    QList<int> platforms;
};

#endif // GAME_H
