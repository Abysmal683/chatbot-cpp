#include "tfindfclassifier.h"
#include "textprocessor.h"

#include <QtMath>

TFIDFClassifier::TFIDFClassifier(TextProcessor *processor)
    : processor(processor)
{
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
    if (!processor)
        return;

    tfidfVectors.clear();
    df.clear();
    totalDocs = documents.size();

    // 1. Calcular DF (document frequency)
    for (auto it = documents.begin(); it != documents.end(); ++it) {
        QStringList tokens = tokenize(it.value());
        QSet<QString> unique(tokens.begin(), tokens.end());
        for (const QString &w : unique)
            df[w] += 1;
    }

    // 2. Calcular TF-IDF por documento
    for (auto it = documents.begin(); it != documents.end(); ++it) {
        QStringList tokens = tokenize(it.value());
        auto tf = computeTf(tokens);
        auto tfidf = computeTfidf(tf);
        tfidfVectors[it.key()] = tfidf;
    }
}

QString TFIDFClassifier::classify(const QString &query) const
{
    if (!processor || documents.isEmpty())
        return QString();

    auto qTokens = tokenize(query);
    auto qtf = computeTf(qTokens);
    auto qtfidf = computeTfidf(qtf);

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

QVector<QPair<QString, double>> TFIDFClassifier::topN(const QString &query, int n) const
{
    QVector<QPair<QString, double>> ranked;

    if (!processor || documents.isEmpty())
        return ranked;

    auto qTokens = tokenize(query);
    auto qtf = computeTf(qTokens);
    auto qtfidf = computeTfidf(qtf);

    // Medir similitud con cada documento
    for (auto it = tfidfVectors.begin(); it != tfidfVectors.end(); ++it) {
        double sim = cosineSim(qtfidf, it.value());
        ranked.append({it.key(), sim});
    }

    // Ordenar por similitud descendente
    std::sort(ranked.begin(), ranked.end(),
              [](auto &a, auto &b) { return a.second > b.second; });

    if (ranked.size() > n)
        ranked.resize(n);

    return ranked;
}

QStringList TFIDFClassifier::tokenize(const QString &text) const
{
    QString t = processor->normalizeText(text);
    return t.split(' ', Qt::SkipEmptyParts);
}

QHash<QString, double> TFIDFClassifier::computeTf(const QStringList &tokens) const
{
    QHash<QString, double> tf;

    for (const QString &t : tokens)
        tf[t] += 1.0;

    // normalizar por longitud del documento
    double total = tokens.size();
    for (auto it = tf.begin(); it != tf.end(); ++it)
        it.value() /= total;

    return tf;
}

QHash<QString, double> TFIDFClassifier::computeTfidf(const QHash<QString, double> &tf) const
{
    QHash<QString, double> result;

    for (auto it = tf.begin(); it != tf.end(); ++it) {
        const QString &word = it.key();
        double tfVal = it.value();
        double docFreq = df.value(word, 1);

        double idf = qLn((double(totalDocs) + 1.0) / (docFreq + 1.0)) + 1.0;

        result[word] = tfVal * idf;
    }

    return result;
}

double TFIDFClassifier::cosineSim(const QHash<QString, double> &v1,
    const QHash<QString, double> &v2) const
{
    double dot = 0.0, mag1 = 0.0, mag2 = 0.0;

    for (auto it = v1.begin(); it != v1.end(); ++it) {
        mag1 += it.value() * it.value();
        if (v2.contains(it.key()))
            dot += it.value() * v2[it.key()];
    }

    for (auto it = v2.begin(); it != v2.end(); ++it)
        mag2 += it.value() * it.value();

    double denom = (qSqrt(mag1) * qSqrt(mag2));
    if (denom == 0)
        return 0.0;

    return dot / denom;
}
