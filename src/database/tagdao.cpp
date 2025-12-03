#include "tagdao.h"

int TagDAO::add(const Tag& t) const {
    return BaseSimpleDAO::insert(t.name);
}

bool TagDAO::update(const Tag& t) const {
    return BaseSimpleDAO::update(t.id, t.name);
}

bool TagDAO::remove(int id) const {
    return BaseSimpleDAO::remove(id);
}

Tag TagDAO::get(int id) const {
    Tag t;
    t.id = id;
    t.name = BaseSimpleDAO::getNameById(id);
    return t;
}

QList<Tag> TagDAO::getAllTags() const {
    QList<Tag> result;
    const auto list = BaseSimpleDAO::getAll();

    for (auto& item : list) {
        Tag t;
        t.id = item.first;
        t.name = item.second;
        result.append(t);
    }

    return result;
}
