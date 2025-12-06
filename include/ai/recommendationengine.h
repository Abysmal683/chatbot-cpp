#ifndef RECOMMENDATIONENGINE_H
#define RECOMMENDATIONENGINE_H

#include <QString>
#include <QStringList>
#include <QVector>
#include <QMap>

#include "game.h"          // Necesario para QList<Game>
//#include "intentresult.h"  // Para usar IntentResult correctamente

class GameDAO;
class TagDAO;
class GenreDAO;
class PlatformDAO;
class ContextBuilder;
class IntentClassifier;

class RecommendationEngine
{
public:
    RecommendationEngine(GameDAO* gDao,
                         TagDAO* tDao,
                         GenreDAO* genDao,
                         PlatformDAO* pDao,
                         ContextBuilder* ctx,
                         IntentClassifier* intent);

    // Entrada principal
    QStringList recommend(const QString& userPrompt);

private:
    // DAOs
    GameDAO* gameDao;
    TagDAO* tagDao;
    GenreDAO* genreDao;
    PlatformDAO* platformDao;

    // Capa superior
    ContextBuilder* contextBuilder;
    IntentClassifier* intentClassifier;

    // TF-IDF
    QMap<int, double> computeTfIdfScores(const QString& text,
                                         const QVector<QString>& docs) const;

    // Top N, devolviendo títulos reales
    QStringList pickTop(const QMap<int, double>& scores,
                        const QList<Game>& games,
                        int limit = 5) const;
};

#endif // RECOMMENDATIONENGINE_H
