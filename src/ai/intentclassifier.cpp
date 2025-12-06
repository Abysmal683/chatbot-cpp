#include "intentclassifier.h"
#include "textprocessor.h"
#include "keyworddetector.h"
#include "tfindfclassifier.h"
#include "ruleengine.h"

IntentClassifier::IntentClassifier(TextProcessor *tp,
   KeywordDetector *kd,
   TFIDFClassifier *tfidf,
   RuleEngine *rules)
    : tp(tp), kd(kd), tfidf(tfidf), rules(rules)
{
}

void IntentClassifier::setKeywordCategories(const QHash<QString, QString> &categories)
{
    keywordCategories = categories;
}

IntentResult IntentClassifier::classify(const QString &userText)
{
    IntentResult result;
    result.intent = "UNKNOWN";
    result.confidence = 0.0;

    // 1. reglas duras
    if (rules) {
        QString r = classifyByRules(userText);
        if (!r.isEmpty()) {
            result.intent = r;
            result.confidence = 1.0;
            return result;
        }
    }

    // 2. keywords
    QVector<QString> encontrados = kd->detectar(userText);

    result.matchedKeywords = encontrados;

    QString fromKW = classifyByKeywords(encontrados);
    if (!fromKW.isEmpty()) {
        result.intent = fromKW;
        result.confidence = 0.7;
        return result;
    }

    // 3. TF-IDF fallback
    if (tfidf) {
        QString best = tfidf->classify(userText);
        if (!best.isEmpty()) {
            result.intent = best;
            result.confidence = 0.5;
            return result;
        }
    }

    return result;
}

QString IntentClassifier::classifyByRules(const QString &text) const
{
    if (!rules)
        return QString();

    return rules->match(text);   // match() será implementado en RuleEngine
}

QString IntentClassifier::classifyByKeywords(const QVector<QString> &found) const
{
    if (found.isEmpty())
        return QString();

    for (const QString &k : found) {
        QString normalized = tp->normalizeText(k);
        if (keywordCategories.contains(normalized))
            return keywordCategories.value(normalized);
    }

    return QString();
}
