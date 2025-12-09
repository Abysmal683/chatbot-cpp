#include "tfindfclassifier.h"
#include "rulesdao.h"
#include "tfidfvectordao.h"
#include "rule.h"
#include <QtMath>
#include <QSet>
#include <algorithm>

TFIDFClassifier::TFIDFClassifier( RulesDAO* rules, TFIDFVectorDAO* vector)
    : rulesDao(rules), vecDao(vector)
{
    rebuildIfNeeded();
}

void TFIDFClassifier::addDocument(const QString &id, const QString &texto)
{
    documents[id] = texto;
}

void TFIDFClassifier::clear()
{
    documents.clear();
    tfidfVectors.clear();
    df.clear();
    totalDocs = 0;
}

void TFIDFClassifier::rebuild()
{
    if (!rulesDao || !vecDao)
        return;

    clear();
    const QList<Rule> activeRules = rulesDao->getActiveRules();
    totalDocs = activeRules.size();
    if (totalDocs == 0) return;

    for (const Rule &r : activeRules) {
        documents[r.trigger] = r.response;

        // Recuperar vectores persistidos
        const QList<TFIDFVector> persisted = vecDao->getByRuleId(r.id);
        QHash<QString,double> tfidf;

        if (!persisted.isEmpty()) {
            for (const TFIDFVector &v : persisted)
                tfidf[v.token] = v.tfidf;
        } else {
            QStringList tokens = tokenize(r.response);
            tfidf = computeTfidf(computeTf(tokens));

            // Persistir TF-IDF
            for (auto it = tfidf.begin(); it != tfidf.end(); ++it) {
                TFIDFVector v{r.id, it.key(), it.value()};
                vecDao->insert(v);
            }
        }

        tfidfVectors[r.trigger] = tfidf;

        // Actualizar DF una sola vez
        for (const QString &token : tfidf.keys())
            df[token] += 1;
    }
}

void TFIDFClassifier::rebuildIfNeeded()
{
    if (!rulesDao)
        return;

    const QList<Rule> activeRules = rulesDao->getActiveRules();
    int currentVersion = activeRules.size();
    if (currentVersion == rulesVersion)
        return; // Sin cambios

    rulesVersion = currentVersion;
    clear();

    totalDocs = currentVersion;
    if (totalDocs == 0) return;

    for (const Rule &r : activeRules) {
        documents[r.trigger] = r.response;

        const QList<TFIDFVector> persisted = vecDao->getByRuleId(r.id);
        QHash<QString,double> tfidf;

        if (!persisted.isEmpty()) {
            for (const TFIDFVector &v : persisted)
                tfidf[v.token] = v.tfidf;
        } else {
            QStringList tokens = tokenize(r.response);
            tfidf = computeTfidf(computeTf(tokens));

            // Guardar en DB
            for (auto it = tfidf.begin(); it != tfidf.end(); ++it)
                vecDao->insert({r.id, it.key(), it.value()});
        }

        tfidfVectors[r.trigger] = tfidf;

        for (const QString &token : tfidf.keys())
            df[token] += 1;
    }
}

QString TFIDFClassifier::classify(const QStringList &tokens) const
{
    if (documents.isEmpty()) return {};
    auto qtfidf = computeTfidf(computeTf(tokens));

    QString bestId;
    double bestScore = -1.0;

    for (auto it = tfidfVectors.begin(); it != tfidfVectors.end(); ++it) {
        double sim = cosineSim(qtfidf, it.value());
        if (sim > bestScore) {
            bestScore = sim;
            bestId = it.key();
        }
    }
    return bestId;
}

QVector<QPair<QString,double>> TFIDFClassifier::topN(const QStringList &tokens, int n) const
{
    QVector<QPair<QString,double>> ranked;
    if (documents.isEmpty()) return ranked;
    auto qtfidf = computeTfidf(computeTf(tokens));

    for (auto it = tfidfVectors.begin(); it != tfidfVectors.end(); ++it)
        ranked.append({it.key(), cosineSim(qtfidf, it.value())});

    std::sort(ranked.begin(), ranked.end(),
              [](const auto &a, const auto &b){ return a.second > b.second; });

    if (ranked.size() > n) ranked.resize(n);
    return ranked;
}

QHash<QString,double> TFIDFClassifier::computeTf(const QStringList &tokens) const
{
    QHash<QString,double> tf;
    for (const QString &t : tokens) tf[t] += 1.0;
    double total = tokens.size();
    if (total == 0) return tf;
    for (auto it = tf.begin(); it != tf.end(); ++it) it.value() /= total;
    return tf;
}

QHash<QString,double> TFIDFClassifier::computeTfidf(const QHash<QString,double> &tf) const
{
    QHash<QString,double> result;
    for (auto it = tf.begin(); it != tf.end(); ++it) {
        double docFreq = df.value(it.key(), 1);
        double idf = qLn((double(totalDocs) + 1.0) / (docFreq + 1.0)) + 1.0;
        result[it.key()] = it.value() * idf;
    }
    return result;
}

double TFIDFClassifier::cosineSim(const QHash<QString,double> &v1, const QHash<QString,double> &v2) const
{
    double dot = 0, mag1 = 0, mag2 = 0;
    for (auto it = v1.begin(); it != v1.end(); ++it) {
        mag1 += it.value() * it.value();
        if (v2.contains(it.key())) dot += it.value() * v2[it.key()];
    }
    for (auto it = v2.begin(); it != v2.end(); ++it)
        mag2 += it.value() * it.value();

    double denom = qSqrt(mag1) * qSqrt(mag2);
    return denom == 0 ? 0 : dot / denom;
}
