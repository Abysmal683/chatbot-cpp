#ifndef PLATFORMDAO_H
#define PLATFORMDAO_H
#include "basesimpledao.h"
#include "platform.h"
class PlatformDAO : public BaseSimpleDAO{
    public:
    PlatformDAO(QSqlDatabase& db) : BaseSimpleDAO("platforms",db){};
    int add(const Platform& p) const;
    bool update(const Platform& p) const;
    bool remove(int id) const;

    Platform get(int id) const;
    QList<Platform> getAll() const;
};

#endif // PLATFORMDAO_H
