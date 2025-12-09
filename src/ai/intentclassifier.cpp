#include "intentclassifier.h"
#include "keyworddetector.h"
#include "tfindfclassifier.h"
#include "ruleengine.h"

IntentClassifier::IntentClassifier(KeywordDetector *kd,
                                   TFIDFClassifier *tfidf,
                                   RuleEngine *rules)
    : kd(kd), tfidf(tfidf), rules(rules)
{
}

void IntentClassifier::setKeywordCategories(const QHash<QString, QString> &categories)
{
    keywordCategories = categories;
}

IntentResult IntentClassifier::classify(const QString &userText) const
{
    IntentResult result;
    result.intent = "UNKNOWN";
    result.confidence = 0.0;

    if (userText.isEmpty()) return result;
    // 1️ Reglas duras
    if (rules) {
        QString r = rules->match(userText); // ya normalizado
        if (!r.isEmpty()) {
            result.intent = r;
            result.confidence = 1.0;
            return result;
        }
    }

    // 2️ Keywords
    QVector<QString> encontrados;
    if (kd) encontrados = kd->detectar(userText); // pasar texto normalizado

    result.matchedKeywords = encontrados;

    for (const QString &k : std::as_const(encontrados)) {
        if (keywordCategories.contains(k)) {
            result.intent = keywordCategories.value(k);
            result.confidence = 0.7;
            return result;
        }
    }

    // 3️ TF-IDF fallback
    if (tfidf) {
        QString best = tfidf->classify(userText); // tokenize interno
        if (!best.isEmpty()) {
            result.intent = best;
            result.confidence = 0.5;
            return result;
        }
    }

    return result;
}
