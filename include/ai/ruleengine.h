#ifndef RULEENGINE_H
#define RULEENGINE_H

#include <QString>
#include <QStringList>
#include <QVector>

class TextProcessor;
class KeywordDetector;

class RuleEngine
{
public:
    RuleEngine(TextProcessor *processor, KeywordDetector *detector);

    void addRule(const QString &intentId, const QStringList &keywords);

    QString match(const QString &texto) const;   // Regla encontrada o ""

private:
    struct Rule {
        QString intentId;
        QStringList keywords;
    };

    TextProcessor *processor;
    KeywordDetector *detector;
    QVector<Rule> rules;
};

#endif // RULEENGINE_H
