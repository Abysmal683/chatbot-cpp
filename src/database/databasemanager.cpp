#include "databasemanager.h"
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

DataBaseManager::DataBaseManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/DataBase_ChatBot.db";
    QDir dir(QFileInfo(dbPath).path());
    if (!dir.exists()) dir.mkpath(dir.path());
    db.setDatabaseName(dbPath);
    qDebug() << "Se inicio ";
}

DataBaseManager::~DataBaseManager() {
    QString name = db.connectionName();
    db.close();
    QSqlDatabase::removeDatabase(name);
}

DataBaseManager& DataBaseManager::instance() {
    static DataBaseManager instance;
    return instance;
}

bool DataBaseManager::createTables() {
    QFile schemaFile(":/resources/database/chatbot_schema.sql");
    if (!schemaFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "No se pudo abrir chatbot_schema.sql desde recursos.";
        return false;
    }

    QTextStream stream(&schemaFile);
    QString sqlContent = stream.readAll();
    schemaFile.close();

    QSqlQuery q(db);

    if (!db.transaction()) qWarning() << "No se pudo iniciar transacción";

    const QStringList lines = sqlContent.split('\n', Qt::SkipEmptyParts);
    QString statement;

    for (QString line : lines) {
        line = line.trimmed();
        if (line.startsWith("--") || line.isEmpty()) continue; // ignora comentarios y líneas vacías
        statement += line + " ";
        if (line.endsWith(";")) {
            if (!q.exec(statement)) {
                qCritical() << "Error ejecutando SQL:" << statement;
                qCritical() << "Detalle:" << q.lastError().text();
                db.rollback();
                return false;
            }
            statement.clear();
        }
    }

    if (!db.commit()) {
        db.rollback();
        qCritical() << "No se pudo commitear creación de tablas";
        return false;
    }

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

QSqlDatabase& DataBaseManager::getDatabase() {
    return db;
}

bool DataBaseManager::clearTable(const QString &tableName) {
    if (!db.isOpen()) return false;
    QSqlQuery q(db);
    QString sql = QStringLiteral("DELETE FROM \"%1\"").arg(tableName);
    if (!q.exec(sql)) {
        qCritical() << "error limpiando tabla:" << tableName << q.lastError().text();
        return false;
    }
    return true;
}
