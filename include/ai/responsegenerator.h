#ifndef RESPONSEGENERATOR_H
#define RESPONSEGENERATOR_H

#include <QString>
#include <QStringList>
#include "intentclassifier.h"
#include "keyworddetector.h"
#include "recommendationengine.h"
#include "contextbuilder.h"
#include "ruleengine.h"

class ResponseGenerator
{
public:
    // Nuevo constructor: recibe los módulos una sola vez
    ResponseGenerator(ContextBuilder* ctx,
                      RuleEngine* rules,
                      RecommendationEngine* recs);

    // Cuando hay una regla dura
    QString generateFromRule(const QString& userInput);

    // Generador general
    QString generateResponse(const QString& userInput);

private:
    ContextBuilder* contextBuilder;
    RuleEngine* ruleEngine;
    RecommendationEngine* recommendationEngine;
    IntentClassifier* intentClassifier;     // se puede inyectar si quieres
    KeywordDetector* keywordDetector;       // se puede inyectar si quieres
};

#endif
