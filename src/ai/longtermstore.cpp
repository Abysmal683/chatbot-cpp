#include "longtermstore.h"
#include "userpreferencedao.h"
#include "memorylongtermdao.h"
#include "userpreference.h"
#include "memorylongterm.h"
#include <QDateTime>

LongTermStore::LongTermStore(UserPreferenceDAO* prefDao,
                             MemoryLongTermDAO* memDao)
    : prefDao(prefDao), memDao(memDao)
{
}

/* =====================================
 *   PREFERENCIAS del usuario
 * ===================================== */
void LongTermStore::savePreference(const QString& key, const QString& value)
{
    if (!prefDao) return;

    UserPreference pref;
    pref.key = key;
    pref.value = value;

    // insert() ya maneja upsert gracias a ON CONFLICT
    prefDao->insert(pref);
}

QString LongTermStore::getPreference(const QString& key) const
{
    if (!prefDao) return "";

    UserPreference pref = prefDao->getByKey(key);
    return pref.value;
}

/* =====================================
 *     MEMORIA LARGO PLAZO
 * ===================================== */
void LongTermStore::saveMemory(const QString& key, const QString& value, int importance)
{
    if (!memDao) return;

    MemoryLongTerm mem;
    mem.key = key;
    mem.value = value;
    mem.importance = importance;
    mem.created_at = QDateTime::currentDateTime().toString(Qt::ISODate);

    memDao->insert(mem);
}

QString LongTermStore::getMemory(const QString& key) const
{
    if (!memDao) return "";

    QList<MemoryLongTerm> list = memDao->findByKey(key);
    if (list.isEmpty()) return "";

    // Tomar la memoria más reciente
    return list.first().value;
}

QList<MemoryLongTerm> LongTermStore::getAllMemories(const QString& key) const
{
    if (!memDao) return {};

    return memDao->findByKey(key);
}

QList<QString> LongTermStore::listKeys() const
{
    if (!memDao) return {};

    return memDao->listKeys();
}
