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
#include "database/keyworddao.h"
#include "database/genredao.h"
#include "database/platformdao.h"
#include "database/userpreferencedao.h"
#include "database/memorylongtermdao.h"
#include "database/conversationhistorydao.h"

#include <QDebug>

AIEngine::AIEngine()
{
    qDebug() << "[AIEngine] Inicio de inicialización";

    QSqlDatabase& db = DataBaseManager::instance().getDatabase();

    // --- 1. DAOs --- //
    qDebug() << "[AIEngine] Creando DAOs";
    tagDao           = std::make_unique<TagDAO>(db);
    genreDao         = std::make_unique<GenreDAO>(db);
    platformDao      = std::make_unique<PlatformDAO>(db);
    gameTagsDao      = std::make_unique<GameTagsDAO>(db);
    gameGenresDao    = std::make_unique<GameGenresDAO>(db);
    gamePlatformsDao = std::make_unique<GamePlatformsDAO>(db);
    rulesDao         = std::make_unique<RulesDAO>(db);
    tfindDao         = std::make_unique<TFIDFVectorDAO>(db);
    keyDao         = std::make_unique<KeywordDAO>(db);
    prefDao          = std::make_unique<UserPreferenceDAO>(db);
    memLongDao       = std::make_unique<MemoryLongTermDAO>(db);
    historyDao       = std::make_unique<ConversationHistoryDAO>(db);
    qDebug() << "[AIEngine] DAOs creados";

    // --- 2. GameDAO (depende de otros DAOs) --- //
    qDebug() << "[AIEngine] Creando GameDAO";
    gameDao = std::make_unique<GameDAO>(db, *gameTagsDao, *gameGenresDao, *gamePlatformsDao);
    qDebug() << "[AIEngine] GameDAO creado";

    // --- 3. Módulos básicos --- //
    qDebug() << "[AIEngine] Inicializando módulos básicos";
    textProcessor   = std::make_unique<TextProcessor>();
    tfidf           = std::make_unique<TFIDFClassifier>(rulesDao.get(), tfindDao.get());
    sessionMemory   = std::make_unique<DialogueMemory>();
    keywordDetector = std::make_unique<KeywordDetector>();
    // Obtener todas las keywords desde la base de datos
    qDebug() << "[AIEngine] llenando keyworddectector";
    const QList<Keyword> t_keywords = keyDao->getAll();
    // Convertir a QStringList

    QStringList keywordList;
    for (const Keyword &k : t_keywords)
        keywordList.append(k.keyword);  // aquí usamos el campo de texto real
    // Pasar la lista al detector
    keywordDetector->setKeywords(keywordList);
    qDebug() << "[AIEngine] se termino de llenar keyworddectetor";
    ruleEngine      = std::make_unique<RuleEngine>(keywordDetector.get(), rulesDao.get());
    qDebug() << "[AIEngine] Módulos básicos inicializados";

    // --- 4. LongTermStore --- //
    longTermStore = std::make_unique<LongTermStore>(prefDao.get(), memLongDao.get());

    // --- 5. IntentClassifier --- //
    intentClassifier = std::make_unique<IntentClassifier>(keywordDetector.get(), tfidf.get(), ruleEngine.get(),textProcessor.get());

    // --- 6. ContextBuilder --- //
    contextBuilder = std::make_unique<ContextBuilder>(
        sessionMemory.get(),
        historyDao.get(),
        longTermStore.get());

    // --- 7. RecommendationEngine --- //
    recommendationEngine = std::make_unique<RecommendationEngine>(
        gameDao.get(),
        tagDao.get(),
        genreDao.get(),
        platformDao.get(),
        contextBuilder.get(),
        intentClassifier.get()
        );

    // --- 8. ResponseGenerator --- //
    responseGenerator = std::make_unique<ResponseGenerator>(
        contextBuilder.get(),
        ruleEngine.get(),
        recommendationEngine.get(),
        intentClassifier.get(),
        keywordDetector.get()
        );

    initialized = true;
    qDebug() << "[AIEngine] Inicialización completa";
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
    qDebug() << "entrada exitosa en procces, guardando input" ;
    QString input = textProcessor->normalizeText(userInput);
    QStringList tokens = textProcessor->tokenize(userInput);
    if (sessionMemory)
        sessionMemory->addUserMessage(input);
    qDebug() << "memoria almacenada en session memory" ;
    // Clasificación de intención y keywords
    //QString intentStr = intentClassifier ? intentClassifier->classify(input).intent : "none";
    //QStringList kws   = keywordDetector ? keywordDetector->detectar(input) : QStringList{};

    // Generación de respuesta
    qDebug() << "generando respuesta" ;
    QString resp;
    QString ruleMatch = ruleEngine ? ruleEngine->match(input) : QString();
    qDebug() << "eligiendo entre rule match o generate response" ;
    if (!ruleMatch.isEmpty()){
        qDebug() << "[AiEngine]solicitando una repuesta de response generator->generate from rules" ;
        resp = responseGenerator->generateFromRule(input);
        qDebug() << "[AiEngine]se consiguio una respuesta de response generator" ;
    }
    else{
        qDebug() << "[AiEngine]solicitando una respuesta desde response generator -> generate response" ;
        resp = responseGenerator->generateResponse(input,tokens, includeMemory, includeHistory, historyMessages);
        qDebug() << "[AiEngine]se consiguio una repuesta de generate response" ;
    }
    qDebug() << "guardar historial persistente" ;
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
