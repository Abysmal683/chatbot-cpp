#include "responsegenerator.h"
#include "contextbuilder.h"
#include "ruleengine.h"
#include "recommendationengine.h"

ResponseGenerator::ResponseGenerator(ContextBuilder* ctx,
                                     RuleEngine* rules,
                                     RecommendationEngine* recs)
    : contextBuilder(ctx),
    ruleEngine(rules),
    recommendationEngine(recs),
    intentClassifier(nullptr),
    keywordDetector(nullptr)
{
}

// ======================================================================
// Respuesta basada en reglas
// ======================================================================
QString ResponseGenerator::generateFromRule(const QString& userInput)
{
    if (!ruleEngine)
        return "disculpa no logre entender tu peticion";

    QString match = ruleEngine->match(userInput);
    if (!match.isEmpty())
        return QString("Detecté la intención '%1' basándome en reglas.").arg(match);

    return "disculpa no logre entender tu peticion";
}

// ======================================================================
// Generador general
// ======================================================================
QString ResponseGenerator::generateResponse(const QString& userInput)
{
    if (!contextBuilder)
        return "disculpa no logre entender tu peticion";

    // Construye contexto completo internamente
    QString context = contextBuilder->buildContext(userInput, "none", {});

    // Recomendaciones internas si existe engine
    QStringList recs;
    if (recommendationEngine)
        recs = recommendationEngine->recommend(userInput);

    QString response = QString("Respuesta generada usando contexto:\n%1").arg(context);

    if (!recs.isEmpty())
        response += QString("\nRecomendaciones: %1").arg(recs.join(", "));

    return response;
}
