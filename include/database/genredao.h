#ifndef GENREDAO_H
#define GENREDAO_H
#include "basesimpledao.h"
#include "genre.h"

class GenreDAO : public BaseSimpleDAO {
public:
    explicit GenreDAO(QSqlDatabase& db)
        : BaseSimpleDAO("genres", db) {}

    int add(const Genre& g) const;
    bool update(const Genre& g) const;
    bool remove(int id) const;

    Genre get(int id) const;
    QList<Genre> getAll() const;
};

#endif // GENREDAO_H
