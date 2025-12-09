#include "aiengine.h"

// Módulos internos
#include "ai/textprocessor.h"
#include "ai/dialoguememory.h"
#include "ai/intentclassifier.h"
#include "ai/keyworddetector.h"
#include "ai/ruleengine.h"
#include "ai/recommendationengine.h"
#include "ai/contextbuilder.h"
#include "ai/responsegenerator.h"
#include "ai/longtermstore.h"
#include "ai/tfindfclassifier.h"

// DAOs y manager
#include "database/databasemanager.h"
#include "database/gamedao.h"
#include "database/gametagsdao.h"
#include "database/gamegenresdao.h"
#include "database/gameplatformsdao.h"
#include "database/tagdao.h"
#include "database/rulesdao.h"
#include "database/tfidfvectordao.h"
#include "database/genredao.h"
#include "database/platformdao.h"
#include "database/userpreferencedao.h"
#include "database/memorylongtermdao.h"
#include "database/conversationhistorydao.h"

#include <QDebug>

AIEngine::AIEngine()
{
    QSqlDatabase& db = DataBaseManager::instance().getDatabase();
        // 2. DAOs
    auto gameTagsDao      = std::make_unique<GameTagsDAO>(db);
    auto gameGenresDao    = std::make_unique<GameGenresDAO>(db);
    auto gamePlatformsDao = std::make_unique<GamePlatformsDAO>(db);

    auto gameDao    = std::make_unique<GameDAO>(db, *gameTagsDao,
                                             *gameGenresDao,
                                             *gamePlatformsDao);
    auto tagDao     = std::make_unique<TagDAO>(db);
    auto genreDao   = std::make_unique<GenreDAO>(db);
    auto platformDao= std::make_unique<PlatformDAO>(db);
    auto rulesDao   = std::make_unique<RulesDAO>(db);
    auto tfindDao   = std::make_unique<TFIDFVectorDAO>(db);
    auto prefDao    = std::make_unique<UserPreferenceDAO>(db);
    auto memLongDao = std::make_unique<MemoryLongTermDAO>(db);
    auto historyDao = std::make_unique<ConversationHistoryDAO>(db);
    // 1. Módulos básicos
    textProcessor   = std::make_unique<TextProcessor>();
    tfidf           = std::make_unique<TFIDFClassifier>(textProcessor.get(),
                                              rulesDao.get(),
                                              tfindDao.get());
    sessionMemory   = std::make_unique<DialogueMemory>();
    keywordDetector = std::make_unique<KeywordDetector>(textProcessor.get());
    ruleEngine      = std::make_unique<RuleEngine>(textProcessor.get(),
                                              keywordDetector.get(),
                                              rulesDao.get());


    // 3. LongTermStore
    longTermStore = std::make_unique<LongTermStore>(prefDao.get(), memLongDao.get());

    // 4. IntentClassifier
    intentClassifier = std::make_unique<IntentClassifier>(
        keywordDetector.get(),
        tfidf.get(),
        ruleEngine.get()
        );

    // 5. ContextBuilder
    contextBuilder = std::make_unique<ContextBuilder>(
        sessionMemory.get(),
        historyDao.get(),
        longTermStore.get(),
        intentClassifier.get(),
        keywordDetector.get()
        );

    // 6. RecommendationEngine
    recommendationEngine = std::make_unique<RecommendationEngine>(
        gameDao.get(),
        tagDao.get(),
        genreDao.get(),
        platformDao.get(),
        contextBuilder.get(),
        intentClassifier.get()
        );

    // 7. ResponseGenerator
    responseGenerator = std::make_unique<ResponseGenerator>(
        contextBuilder.get(),
        ruleEngine.get(),
        recommendationEngine.get(),
        intentClassifier.get(),
        keywordDetector.get()
        );

    initialized = true;
}

AIEngine::~AIEngine() = default;

void AIEngine::ensureInitialized()
{
    if (!initialized)
        qWarning() << "AIEngine no inicializado completamente";
}

QString AIEngine::process(const QString& userInput,
                          bool includeMemory,
                          bool includeHistory,
                          int historyMessages)
{
    ensureInitialized();

    QString input = textProcessor->normalizeText(userInput);

    if (sessionMemory)
        sessionMemory->addUserMessage(input);

    // Clasificación de intención y keywords
    //QString intentStr = intentClassifier ? intentClassifier->classify(input).intent : "none";
    //QStringList kws   = keywordDetector ? keywordDetector->detectar(input) : QStringList{};

    // Generación de respuesta
    QString resp;
    QString ruleMatch = ruleEngine ? ruleEngine->match(input) : QString();

    if (!ruleMatch.isEmpty())
        resp = responseGenerator->generateFromRule(input);
    else
        resp = responseGenerator->generateResponse(input, includeMemory, includeHistory, historyMessages);

    // Registrar en historial persistente
    if (historyDao) {
        ConversationHistory m;
        m.user_message = userInput;
        m.bot_message  = resp;
        historyDao->insert(m);
    }

    if (sessionMemory)
        sessionMemory->addBotMessage(resp);

    return resp;
}
