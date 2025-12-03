#ifndef TAGDAO_H
#define TAGDAO_H
#include "basesimpledao.h"
#include "tag.h"
class TagDAO : public BaseSimpleDAO{
    public:
    TagDAO(QSqlDatabase& db) : BaseSimpleDAO("tags",db){};
        // CRUD adaptados
        int add(const Tag& t) const;
        bool update(const Tag& t) const;
        bool remove(int id) const;
        Tag get(int id) const;
        QList<Tag> getAllTags() const;
};

#endif // TAGDAO_H
