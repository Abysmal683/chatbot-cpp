#include "genredao.h"

int GenreDAO::add(const Genre& g) const {
    return BaseSimpleDAO::insert(g.name);
}

bool GenreDAO::update(const Genre& g) const {
    return BaseSimpleDAO::update(g.id, g.name);
}

bool GenreDAO::remove(int id) const {
    return BaseSimpleDAO::remove(id);
}

Genre GenreDAO::get(int id) const {
    Genre g;
    g.id = id;
    g.name = getNameById(id);
    return g;
}

QList<Genre> GenreDAO::getAll() const {
    QList<Genre> list;
    for (auto& p : BaseSimpleDAO::getAll()) {
        Genre g;
        g.id = p.first;
        g.name = p.second;
        list.append(g);
    }
    return list;
}
