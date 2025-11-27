#ifndef DATAJSONMANAGER_H
#define DATAJSONMANAGER_H
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
class DataJsonManager{
    public:
        static DataJsonManager& instance();

        //Carga generica
        QJsonDocument loadJson(const QString& resourcePath);
        QJsonArray loadArray(const QString& resourcePath, const QString& key);
        QJsonObject loadObject(const QString& resourcePath);

        //Carga específica
        QStringList loadGenres();
        QStringList loadPlatforms();
        QStringList loadTags();

        //Internacionalización
        QJsonObject loadLanguage(const QString& langCode);
    private:
        DataJsonManager() = default;
        DataJsonManager(const DataJsonManager&) = delete;
        DataJsonManager& operator=(const DataJsonManager&) = delete;
};

#endif // DATAJSONMANAGER_H
