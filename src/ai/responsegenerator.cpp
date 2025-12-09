#include "responsegenerator.h"
#include "contextbuilder.h"
#include "ruleengine.h"
#include "recommendationengine.h"
#include "intentclassifier.h"
#include "keyworddetector.h"
#include <qdebug.h>

ResponseGenerator::ResponseGenerator(ContextBuilder* ctx,
                                     RuleEngine* rules,
                                     RecommendationEngine* recs,
                                     IntentClassifier* intent,
                                     KeywordDetector* keyword)
    : contextBuilder(ctx),
    ruleEngine(rules),
    recommendationEngine(recs),
    intentClassifier(intent),
    keywordDetector(keyword)
{
}

// ---------------------------------------------------------
// Respuesta basada en reglas
// ---------------------------------------------------------
QString ResponseGenerator::generateFromRule(const QString& userInput)
{
    if (!ruleEngine)
        return "Disculpa, no logré entender tu petición.";

    QString match = ruleEngine->match(userInput);
    if (!match.isEmpty())
        return QString("Detecté la intención '%1' basándome en reglas.").arg(match);

    return "Disculpa, no logré entender tu petición.";
}

// ---------------------------------------------------------
// Generador general
// ---------------------------------------------------------
QString ResponseGenerator::generateResponse(const QString& userInput,
                                            const QStringList& tokens,
                                            bool includeMemory,
                                            bool includeHistory,
                                            int historyMessages)
{
    qDebug() << "[ResponseGenerator] adentro de generate response" ;
    if (!contextBuilder)
        return "Disculpa, no logré entender tu petición.";

    // Determinar intención y keywords
    qDebug() << "[ResponseGenerator] determinando intencion y keyword" ;
    QString intentStr = intentClassifier ? intentClassifier->classify(userInput).intent : "none";
    qDebug() << "[ResponseGenerator]intenciones obtenidas de intent classifier" ;
    QStringList kws = keywordDetector ? keywordDetector->detectar(userInput,tokens): QStringList();
        qDebug() << "[ResponseGenerator]respuesta obtenida de keyword dectector" ;
    qDebug() << "[ResponseGenerator] construyendo contexto con contextbuilder->buildcontext" ;
    // Construir contexto completo usando el nuevo ContextBuilder
    QString context = contextBuilder->buildContext(userInput,
                                                   intentStr,
                                                   kws,
                                                   includeMemory,
                                                   includeHistory,
                                                   historyMessages);

    // Recomendaciones si existe engine
    QStringList recs;
    if (recommendationEngine){
        qDebug() << "[ResponseGenerator]solicitando recomendacion de recommendatonEngine->recommend" ;
        recs = recommendationEngine->recommend(userInput);
        qDebug() << "[ResponseGenerator]respuesta obtenida de recommendation engine" ;
    }

    // Formatear la respuesta final
    qDebug() << "[ResponseGenerator]creando respuesta final" ;
    QStringList output;
    output << "=== RESPONSE ===";
    output << context;
    if (!recs.isEmpty())
        output << "\n=== RECOMMENDATIONS ===" << recs;
    output << "=== END RESPONSE ===";

    return output.join("\n");
}
