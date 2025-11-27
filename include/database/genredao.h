#ifndef GENREDAO_H
#define GENREDAO_H
#include <QString>
#include <QList>
#include "basesimpledao.h"
class GenreDAO : public BaseSimpleDAO{
    public:
        GenreDAO() : BaseSimpleDAO("genres") {}
        bool insert(const QString& name);
        int getIdByName(const QString& name);
        QStringList getAll();
};

#endif // GENREDAO_H
