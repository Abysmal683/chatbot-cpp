#ifndef INTENTCLASSIFIER_H
#define INTENTCLASSIFIER_H

#include <QString>
#include <QVector>
#include <QHash>

class TextProcessor;
class KeywordDetector;
class TFIDFClassifier;
class RuleEngine;

struct IntentResult {
    QString intent;
    double confidence;
    QVector<QString> matchedKeywords;
};

class IntentClassifier {
public:
    IntentClassifier(TextProcessor *tp,
                     KeywordDetector *kd,
                     TFIDFClassifier *tfidf,
                     RuleEngine *rules);

    IntentResult classify(const QString &userText);

    void setKeywordCategories(const QHash<QString, QString> &categories);

private:
    TextProcessor *tp;
    KeywordDetector *kd;
    TFIDFClassifier *tfidf;
    RuleEngine *rules;

    // mapa: keyword_normalizada → categoría
    QHash<QString, QString> keywordCategories;

    QString classifyByKeywords(const QVector<QString> &found) const;
    QString classifyByRules(const QString &text) const;
};

#endif // INTENTCLASSIFIER_H
