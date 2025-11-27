#include "datajsonmanager.h"
#include <QFile>
#include <QDebug>

DataJsonManager& DataJsonManager::instance() {
    static DataJsonManager i;
    return i;
}
QJsonDocument DataJsonManager::loadJson(const QString& resourcePath) {
    QFile file(resourcePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qCritical() << "No se pudo abrir JSON:" << resourcePath;
        return QJsonDocument();
    }

    auto data = file.readAll();
    file.close();

    QJsonParseError err;
    auto doc = QJsonDocument::fromJson(data, &err);

    if (err.error != QJsonParseError::NoError) {
        qCritical() << "Error parseando JSON:" << err.errorString();
    }

    return doc;
}
QJsonObject DataJsonManager::loadObject(const QString& resourcePath) {
    auto doc = loadJson(resourcePath);
    return doc.isObject() ? doc.object() : QJsonObject();
}

QJsonArray DataJsonManager::loadArray(const QString& resourcePath, const QString& key) {
    auto obj = loadObject(resourcePath);
    return obj[key].toArray();
}
//--- Funciones específicas

QStringList DataJsonManager::loadGenres() {
    const QJsonArray& arr = loadArray(":/database/genres.json", "genres");
    QStringList result;
    for (const auto &v : arr) result << v.toString();
    return result;
}

QStringList DataJsonManager::loadPlatforms() {
    const QJsonArray& arr = loadArray(":/database/platforms.json", "platforms");
    QStringList result;
    for (const auto &v : arr) result << v.toString();
    return result;
}

QStringList DataJsonManager::loadTags() {
    const QJsonArray& arr = loadArray(":/database/tags.json", "tags");
    QStringList result;
    for (const auto &v : arr) result << v.toString();
    return result;
}

QJsonObject DataJsonManager::loadLanguage(const QString& langCode) {
    return loadObject(":/languages/" + langCode + ".json");
}
