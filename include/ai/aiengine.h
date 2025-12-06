#ifndef AIENGINE_H
#define AIENGINE_H

#include <memory>
#include <QString>

// Forward declarations
class TextProcessor;
class DialogueMemory;
class ConversationHistoryDAO;
class IntentClassifier;
class KeywordDetector;
class RuleEngine;
class RecommendationEngine;
class ContextBuilder;
class ResponseGenerator;
class LongTermStore;
class TFIDFClassifier;

class AIEngine
{
public:
    // Constructor por defecto construye módulos básicos y DAOs usando DatabaseManager
    AIEngine();

    // Constructor que recibe punteros inyectados (para tests / DI)
    AIEngine(TextProcessor* tp,
             DialogueMemory* sessionMem,
             ConversationHistoryDAO* historyDao,
             IntentClassifier* intentCls,
             KeywordDetector* kwd,
             RuleEngine* rules,
             RecommendationEngine* recomm,
             ContextBuilder* ctx,
             ResponseGenerator* respGen,
             LongTermStore* longTerm);

    ~AIEngine();

    // Entrada principal: recibe user input y devuelve respuesta textual del bot
    QString process(const QString& userInput);

private:
    std::unique_ptr<TextProcessor> textProcessor;
    std::unique_ptr<DialogueMemory> sessionMemory;
    std::unique_ptr<ConversationHistoryDAO> historyDao;
    std::unique_ptr<IntentClassifier> intentClassifier;
    std::unique_ptr<KeywordDetector> keywordDetector;
    std::unique_ptr<RuleEngine> ruleEngine;
    std::unique_ptr<RecommendationEngine> recommendationEngine;
    std::unique_ptr<ContextBuilder> contextBuilder;
    std::unique_ptr<ResponseGenerator> responseGenerator;
    std::unique_ptr<LongTermStore> longTermStore;
    std::unique_ptr<TFIDFClassifier> tfidf;

    void ensureInitialized();
    bool initialized = false;
};

#endif // AIENGINE_H
