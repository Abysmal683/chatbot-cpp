#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>
#include "genredao.h"
#include "databasemanager.h"
bool GenreDAO::insert(const QString& name) {
    QSqlQuery q(DataBaseManager::instance().getDatabase());

    q.prepare("INSERT OR IGNORE INTO genres (name) VALUES (:name)");
    q.bindValue(":name", name);

    if (!q.exec()) {
        qCritical() << "Error insertando género:"
                    << q.lastError().text();
        return false;
    }
    return true;
}

int GenreDAO::getIdByName(const QString& name) {
    QSqlQuery q(DataBaseManager::instance().getDatabase());

    q.prepare("SELECT id FROM genres WHERE name = :name");
    q.bindValue(":name", name);

    if (!q.exec()) return -1;

    if (q.next()) {
        return q.value(0).toInt();
    }
    return -1;
}

QStringList GenreDAO::getAll() {
    QSqlQuery q(DataBaseManager::instance().getDatabase());

    if (!q.exec("SELECT name FROM genres ORDER BY name ASC"))
        return {};

    QStringList list;
    while (q.next()) {
        list << q.value(0).toString();
    }
    return list;
}
