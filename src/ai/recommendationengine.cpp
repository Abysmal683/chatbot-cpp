#include "recommendationengine.h"
#include "gamedao.h"
#include "tagdao.h"
#include "genredao.h"
#include "platformdao.h"
#include "contextbuilder.h"
#include "intentclassifier.h"
#include "game.h"

#include <QtMath>
#include <QDebug>
#include <QRegularExpression>

RecommendationEngine::RecommendationEngine(GameDAO* gDao,
                                           TagDAO* tDao,
                                           GenreDAO* genDao,
                                           PlatformDAO* pDao,
                                           ContextBuilder* ctx,
                                           IntentClassifier* intent)
    : gameDao(gDao),
    tagDao(tDao),
    genreDao(genDao),
    platformDao(pDao),
    contextBuilder(ctx),
    intentClassifier(intent)
{
}

// ======================================================================
// Genera recomendaciones para un prompt de usuario
// ======================================================================
QStringList RecommendationEngine::recommend(const QString& userPrompt)
{
    if (!gameDao)
        return {"Error: GameDAO no disponible"};

    // 1️ Detectar intención real si hay intentClassifier
    IntentResult intent = intentClassifier
                              ? intentClassifier->classify(userPrompt)
                              : IntentResult{"generic", 0.0, {}};

    // 2️ Construir contexto completo usando ContextBuilder
    QString context = contextBuilder
                          ? contextBuilder->buildContext(userPrompt, intent.intent, intent.matchedKeywords, true, true, 5)
                          : "";

    // 3️ Combinar prompt + intención + keywords + contexto
    QString combinedQuery = (userPrompt + " " +
                             intent.intent + " " +
                             intent.matchedKeywords.join(" ") + " " +
                             context).toLower();

    // 4️ Obtener juegos completos con todas sus relaciones
    const auto games = gameDao->getAllFull();
    QVector<QString> docs;
    docs.reserve(games.size());

    for (const auto& g : games) {
        QString doc;

        doc += g.title + " ";
        doc += g.description + " ";

        // TAGS
        for (int tagId : g.tags) {
            QString tag = tagDao->getNameById(tagId);
            if (!tag.isEmpty())
                doc += tag + " ";
        }

        // GENRES
        for (int geId : g.genres) {
            QString ge = genreDao->getNameById(geId);
            if (!ge.isEmpty())
                doc += ge + " ";
        }

        // PLATFORMS
        for (int platId : g.platforms) {
            QString p = platformDao->getNameById(platId);
            if (!p.isEmpty())
                doc += p + " ";
        }

        docs.append(doc.trimmed().toLower());
    }

    // 5 Calcular TF-IDF en memoria
    auto scores = computeTfIdfScores(combinedQuery, docs);

    // 6️ Seleccionar Top N títulos reales
    return pickTop(scores, games, 5);
}

// ======================================================================
// TF-IDF dinámico en memoria
// ======================================================================
QMap<int, double> RecommendationEngine::computeTfIdfScores(const QString& text,
                                                           const QVector<QString>& docs) const
{
    QMap<int, double> scores;

    const QStringList queryTerms = text.split(QRegularExpression("\\W+"), Qt::SkipEmptyParts);

    // Calcular DF para cada término
    QMap<QString, int> dfCache;
    for (const QString& term : queryTerms) {
        if (dfCache.contains(term)) continue;
        int df = 0;
        for (const auto& d : docs)
            if (d.contains(term)) df++;
        dfCache[term] = df;
    }

    // Calcular TF-IDF por documento
    for (int i = 0; i < docs.size(); ++i) {
        const QString& doc = docs[i];
        double score = 0.0;
        for (const QString& term : queryTerms) {
            int tf = doc.count(term);
            if (tf == 0) continue;
            int df = dfCache[term];
            if (df == 0) continue;
            double idf = qLn(double(docs.size()) / double(df));
            score += tf * idf;
        }
        scores[i] = score;
    }

    return scores;
}

// ======================================================================
// Seleccionar Top N títulos reales con sus scores
// ======================================================================
QStringList RecommendationEngine::pickTop(const QMap<int, double>& scores,
                                          const QList<Game>& games,
                                          int limit) const
{
    QVector<QPair<int, double>> ordered;
    for (auto it = scores.begin(); it != scores.end(); ++it)
        ordered.append({it.key(), it.value()});

    std::sort(ordered.begin(), ordered.end(),
              [](auto& a, auto& b) { return a.second > b.second; });

    QStringList result;
    int count = 0;
    for (auto& p : ordered) {
        if (count >= limit) break;
        const Game& g = games[p.first];
        result << QString("%1 (score %2)").arg(g.title).arg(p.second, 0, 'f', 3);
        count++;
    }

    return result;
}
