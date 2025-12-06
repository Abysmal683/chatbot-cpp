#include "aiengine.h"

// Módulos
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
#include "database/genredao.h"
#include "database/platformdao.h"
#include "database/userpreferencedao.h"
#include "database/memorylongtermdao.h"
#include "database/conversationhistorydao.h"

#include <QDebug>

AIEngine::AIEngine()
{
    QSqlDatabase& db = DataBaseManager::instance().getDatabase();

    // Módulos básicos
    textProcessor   = std::make_unique<TextProcessor>();
    tfidf           = std::make_unique<TFIDFClassifier>(textProcessor.get());
    sessionMemory   = std::make_unique<DialogueMemory>();
    keywordDetector = std::make_unique<KeywordDetector>(textProcessor.get());
    ruleEngine      = std::make_unique<RuleEngine>(textProcessor.get(), keywordDetector.get());

    // DAOs
    auto gameTagsDao     = std::make_unique<GameTagsDAO>(db);
    auto gameGenresDao   = std::make_unique<GameGenresDAO>(db);
    auto gamePlatformsDao= std::make_unique<GamePlatformsDAO>(db);

    auto gameDao         = std::make_unique<GameDAO>(db, *gameTagsDao, *gameGenresDao, *gamePlatformsDao);
    auto tagDao          = std::make_unique<TagDAO>(db);
    auto genreDao        = std::make_unique<GenreDAO>(db);
    auto platformDao     = std::make_unique<PlatformDAO>(db);

    auto prefDao         = std::make_unique<UserPreferenceDAO>(db);
    auto memLongDao      = std::make_unique<MemoryLongTermDAO>(db);
    historyDao           = std::make_unique<ConversationHistoryDAO>(db);

    // LongTermStore con parámetros correctos
    longTermStore = std::make_unique<LongTermStore>(prefDao.get(), memLongDao.get());

    // IntentClassifier
    intentClassifier = std::make_unique<IntentClassifier>(
        textProcessor.get(),
        keywordDetector.get(),
        tfidf.get(),
        ruleEngine.get()
        );

    // ContextBuilder
    contextBuilder = std::make_unique<ContextBuilder>(
        sessionMemory.get(),
        historyDao.get(),
        longTermStore.get(),
        intentClassifier.get(),
        keywordDetector.get()
        );

    // RecommendationEngine
    recommendationEngine = std::make_unique<RecommendationEngine>(
        gameDao.get(),
        tagDao.get(),
        genreDao.get(),
        platformDao.get(),
        contextBuilder.get(),
        intentClassifier.get()
        );

    // ResponseGenerator
    responseGenerator = std::make_unique<ResponseGenerator>(
        contextBuilder.get(),
        ruleEngine.get(),
        recommendationEngine.get()
        );

    initialized = true;
}

AIEngine::~AIEngine() = default;

void AIEngine::ensureInitialized()
{
    if (!initialized)
        qWarning() << "AIEngine no inicializado completamente";
}

QString AIEngine::process(const QString& userInput)
{
    ensureInitialized();
    QString input = textProcessor->normalizeText(userInput);

    if (sessionMemory)
        sessionMemory->addUserMessage(input);

    IntentResult intent = intentClassifier ? intentClassifier->classify(input)
                                           : IntentResult{"unknown", 0.0, {}};

    QVector<QString> found = keywordDetector ? keywordDetector->detectar(input) : QVector<QString>{};

    QString ruleMatch = ruleEngine ? ruleEngine->match(input) : QString();
    QString resp;

    if (!ruleMatch.isEmpty() && responseGenerator) {
        resp = responseGenerator->generateFromRule(input);
    } else if (responseGenerator) {
        resp = responseGenerator->generateResponse(input);
    } else {
        resp = "No response generator configured.";
    }

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
