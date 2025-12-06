#include "longtermstore.h"
#include "userpreferencedao.h"
#include "memorylongtermdao.h"
#include "userpreference.h"
#include "memorylongterm.h"

LongTermStore::LongTermStore(UserPreferenceDAO* prefDao,
                             MemoryLongTermDAO* memDao)
    : prefDao(prefDao), memDao(memDao)
{
}

/* =====================================
 *   PREFERENCIAS del usuario (estilo saveOrUpdate)
 * ===================================== */
void LongTermStore::savePreference(const QString& key, const QString& value)
{
    if (!prefDao)
        return;

    if (prefDao->exists(key)) {

        // Obtener registro existente
        UserPreference pref = prefDao->getByKey(key);
        pref.value = value;

        prefDao->update(pref);

    } else {

        // Insertar uno nuevo
        UserPreference pref;
        pref.id = 0;
        pref.key = key;
        pref.value = value;

        prefDao->insert(pref);
    }
}

QString LongTermStore::getPreference(const QString& key) const
{
    if (!prefDao)
        return "";

    if (!prefDao->exists(key))
        return "";

    UserPreference pref = prefDao->getByKey(key);
    return pref.value;
}

/* =====================================
 *     MEMORIA LARGO PLAZO (knowledge)
 * ===================================== */
void LongTermStore::saveMemory(const QString& key, const QString& value, int importance)
{
    if (!memDao)
        return;

    MemoryLongTerm mem;
    mem.id = 0;
    mem.key = key;
    mem.value = value;
    mem.importance = importance;

    memDao->insert(mem);
}

QString LongTermStore::getMemory(const QString& key) const
{
    if (!memDao)
        return "";

    QList<MemoryLongTerm> list = memDao->findByKey(key);
    if (list.isEmpty())
        return "";

    // Tomar la memoria más reciente
    return list.first().value;
}
QList<MemoryLongTerm> LongTermStore::getAllMemories(const QString& key) const
{
    if (!memDao)
        return {};

    return memDao->findByKey(key);
}
QList<QString> LongTermStore::listKeys() const
{
    if (!memDao)
        return {};

    return memDao->listKeys();
}
