#ifndef INTENTCLASSIFIER_H
#define INTENTCLASSIFIER_H

#include <QString>
#include <QVector>
#include <QHash>
//elige entre 3 metodos de rastreo para la mejor repuesta por pesos
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
    IntentClassifier(KeywordDetector *kd,
                     TFIDFClassifier *tfidf,
                     RuleEngine *rules);

    IntentResult classify(const QString &userText) const;

    void setKeywordCategories(const QHash<QString, QString> &categories);

private:
    KeywordDetector *kd;
    TFIDFClassifier *tfidf;
    RuleEngine *rules;

    // mapa: keyword_normalizada → categoría
    QHash<QString, QString> keywordCategories;
};

#endif // INTENTCLASSIFIER_H
