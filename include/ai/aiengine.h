#ifndef AIENGINE_H
#define AIENGINE_H

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
// En AIEngine.h
class GameTagsDAO ;
class GameGenresDAO ;
class GamePlatformsDAO ;
class GameDAO ;
class TagDAO ;
class GenreDAO ;
class PlatformDAO ;
class RulesDAO ;
class TFIDFVectorDAO ;
class KeywordDAO;
class UserPreferenceDAO ;
class MemoryLongTermDAO ;
class ConversationHistoryDAO ;
class AIEngine {
public:
    // Constructor por defecto: inicializa todos los módulos
    AIEngine();

    // Constructor para inyección de dependencias (tests / DI)
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

    // Entrada principal para el chat
    QString process(const QString& userInput,
                    bool includeMemory = true,
                    bool includeHistory = true,
                    int historyMessages = 5);

private:
    void ensureInitialized();

    std::unique_ptr<TextProcessor> textProcessor;
    std::unique_ptr<DialogueMemory> sessionMemory;
    std::unique_ptr<IntentClassifier> intentClassifier;
    std::unique_ptr<KeywordDetector> keywordDetector;
    std::unique_ptr<RuleEngine> ruleEngine;
    std::unique_ptr<RecommendationEngine> recommendationEngine;
    std::unique_ptr<ContextBuilder> contextBuilder;
    std::unique_ptr<ResponseGenerator> responseGenerator;
    std::unique_ptr<LongTermStore> longTermStore;
    std::unique_ptr<TFIDFClassifier> tfidf;
    // En AIEngine.h
    std::unique_ptr<GameTagsDAO> gameTagsDao;
    std::unique_ptr<GameGenresDAO> gameGenresDao;
    std::unique_ptr<GamePlatformsDAO> gamePlatformsDao;
    std::unique_ptr<GameDAO> gameDao;
    std::unique_ptr<TagDAO> tagDao;
    std::unique_ptr<GenreDAO> genreDao;
    std::unique_ptr<PlatformDAO> platformDao;
    std::unique_ptr<RulesDAO> rulesDao;
    std::unique_ptr<TFIDFVectorDAO> tfindDao;
    std::unique_ptr<KeywordDAO> keyDao;
    std::unique_ptr<UserPreferenceDAO> prefDao;
    std::unique_ptr<MemoryLongTermDAO> memLongDao;
    std::unique_ptr<ConversationHistoryDAO> historyDao;
    bool initialized = false;
};

#endif // AIENGINE_H
