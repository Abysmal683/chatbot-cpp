#ifndef LONGTERMSTORE_H
#define LONGTERMSTORE_H

#include <QString>
#include <QHash>
#include "memorylongterm.h"
class UserPreferenceDAO;
class MemoryLongTermDAO;

class LongTermStore
{
public:
    LongTermStore(UserPreferenceDAO* prefDao, MemoryLongTermDAO* memDao);

    // Preferencias del usuario
    void savePreference(const QString& key, const QString& value);
    QString getPreference(const QString& key) const;

    // Memoria general de largo plazo
    void saveMemory(const QString& key, const QString& value, int importance);
    QString getMemory(const QString& key) const;
    QList<MemoryLongTerm> getAllMemories(const QString& key) const;
    QList<QString> listKeys() const;
private:
    UserPreferenceDAO* prefDao;
    MemoryLongTermDAO* memDao;
};

#endif
