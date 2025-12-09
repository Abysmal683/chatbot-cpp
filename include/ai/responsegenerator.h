#ifndef RESPONSEGENERATOR_H
#define RESPONSEGENERATOR_H

#include <QString>
#include <QStringList>

class ContextBuilder;
class RuleEngine;
class RecommendationEngine;
class IntentClassifier;
class KeywordDetector;

class ResponseGenerator
{
public:
    ResponseGenerator(ContextBuilder* ctx,
                      RuleEngine* rules,
                      RecommendationEngine* recs,
                      IntentClassifier* intent = nullptr,
                      KeywordDetector* keyword = nullptr);

    // Respuesta basada en reglas
    QString generateFromRule(const QString& userInput);

    // Generador general, integrando contexto y recomendaciones
    QString generateResponse(const QString& userInput,
                             bool includeMemory = true,
                             bool includeHistory = true,
                             int historyMessages = 5);

private:
    ContextBuilder* contextBuilder;
    RuleEngine* ruleEngine;
    RecommendationEngine* recommendationEngine;
    IntentClassifier* intentClassifier;
    KeywordDetector* keywordDetector;
};

#endif // RESPONSEGENERATOR_H
