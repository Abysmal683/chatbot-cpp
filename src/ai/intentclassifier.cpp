#include "intentclassifier.h"
#include "keyworddetector.h"
#include "textprocessor.h"
#include "tfindfclassifier.h"
#include "ruleengine.h"
#include <qdebug.h>

IntentClassifier::IntentClassifier(KeywordDetector *kd,
                                   TFIDFClassifier *tfidf,
                                   RuleEngine *rules,
                                   TextProcessor *tp)
    : kd(kd), tfidf(tfidf), rules(rules),tp(tp)
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

    if (userText.isEmpty())
        return result;

    // ---------------------------
    // 1️ Normalización centralizada
    // ---------------------------
    QString normalizedText = userText;
    if (tp) { // asumimos que KeywordDetector tiene acceso al TextProcessor
        normalizedText = tp->normalizeText(userText);
    }

    // ---------------------------
    // 2️⃣Reglas duras
    // ---------------------------
    if (rules) {
        QString r = rules->match(normalizedText);
        if (!r.isEmpty()) {
            result.intent = r;
            result.confidence = 1.0;
            return result;
        }
    }

    // ---------------------------
    // 3️ Keywords
    // ---------------------------
    if (kd) {
        QVector<QString> encontrados = kd->detectar(normalizedText);

        const QSet<QString> uniqueKeywords = QSet<QString>(encontrados.begin(), encontrados.end());
        result.matchedKeywords = uniqueKeywords.values().toVector();

        for (const QString &k : uniqueKeywords) {
            if (keywordCategories.contains(k)) {
                result.intent = keywordCategories.value(k);
                result.confidence = 0.7;
                return result;
            }
        }
    }

    // ---------------------------
    // 4️ TF-IDF fallback
    // ---------------------------
    if (tfidf) {
        QString best = tfidf->classify(normalizedText);
        if (!best.isEmpty()) {
            result.intent = best;
            result.confidence = 0.5;
            return result;
        }
    }

    return result;
}
