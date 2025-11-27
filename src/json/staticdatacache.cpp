#include "staticdatacache.h"
#include "datajsonmanager.h"
#include <QDebug>

QStringList StaticDataCache::genres;
QStringList StaticDataCache::platforms;
QStringList StaticDataCache::tags;

void StaticDataCache::loadAll() {
    auto &json = DataJsonManager::instance();

    genres    = json.loadGenres();
    platforms = json.loadPlatforms();
    tags      = json.loadTags();

    qDebug() << "Static data cache cargado:";
    qDebug() << "Genres:" << genres;
    qDebug() << "Platforms:" << platforms;
    qDebug() << "Tags:" << tags;
}
