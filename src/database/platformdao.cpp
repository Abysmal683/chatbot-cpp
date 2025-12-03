#include "platformdao.h"

int PlatformDAO::add(const Platform& p) const {
    return BaseSimpleDAO::insert(p.name);
}

bool PlatformDAO::update(const Platform& p) const {
    return BaseSimpleDAO::update(p.id, p.name);
}

bool PlatformDAO::remove(int id) const {
    return BaseSimpleDAO::remove(id);
}

Platform PlatformDAO::get(int id) const {
    Platform p;
    p.id = id;
    p.name = getNameById(id);
    return p;
}

QList<Platform> PlatformDAO::getAll() const {
    QList<Platform> list;
    for (auto& q : BaseSimpleDAO::getAll()) {
        Platform p;
        p.id = q.first;
        p.name = q.second;
        list.append(p);
    }
    return list;
}
