#include "databasemanager.h"
#include <QStandardPaths>
#include <QDir>
#include <QSqlError>
#include <QSqlQuery>
DataBaseManager::DataBaseManager() {
    //tipo de sql que se utilizara
    db = QSqlDatabase::addDatabase("QSQLITE");
    //ubicacion donde se buscara o creara el db
    QString dbpath = QStandardPaths::writableLocation(
        QStandardPaths::AppDataLocation)+ "/DataBase_ChatBot.db";
    //crea una carpeta si no existe
    QDir dir(QFileInfo(dbpath).path());
    //si no existe se crea
    if(!dir.exists()) dir.mkpath(dir.path());
    db.setDatabaseName(dbpath);
}
DataBaseManager& DataBaseManager::instance() {
    //la primera ves crea una instancia, la siguiente la reutiliza
    static DataBaseManager instance;
    return instance;
}
bool DataBaseManager::createTables() {
    //ubica el schema
    QFile schemaFile(":/database/chatbot_schema.sql");
    //abre el archivo en modo lectura de texto
    if (!schemaFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "No se pudo abrir chatbot_schema.sql desde recursos.";
        return false;
    }
    //lee todo el contenido y cierra el archivo
    QTextStream stream(&schemaFile);
    QString sqlContent = stream.readAll();
    schemaFile.close();
    //divide los comandos para ejecutarlo 1 a 1 seperados por el ;,puede fallar si ahi ; en comentarios
    QSqlQuery query;
    const QStringList commands = sqlContent.split(';', Qt::SkipEmptyParts);

    if (!db.transaction()) qWarning() << "No se pudo iniciar transacción";
    //recorre los comandos y limpia para ejecutar, o captura errores
    for (const QString& cmd : commands) {
        QString trimmed = cmd.trimmed();
        if (trimmed.isEmpty())
            continue;

        if (!query.exec(trimmed)) {
            qCritical() << "Error ejecutando SQL:" << trimmed;
            qCritical() << "Detalle:" << query.lastError().text();
            return false;
        }
    }
    if (!db.commit()) {
        db.rollback();
        qCritical() << "No se pudo commitear creación de tablas";
        return false;
    }
    //si todo funciona, tira un qdebug para avisar su estado
    qDebug() << "Tablas creadas/verificadas correctamente.";
    return true;
}
bool DataBaseManager::initialize() {
    if (!db.open()) {
        qCritical() << "ERROR al abrir la base de datos:" << db.lastError().text();
        return false;
    }
    return createTables();
}
