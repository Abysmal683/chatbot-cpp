#ifndef GENREDAO_H
#define GENREDAO_H
#include "basesimpledao.h"
class GenreDAO : public BaseSimpleDAO{
    public:
        GenreDAO() : BaseSimpleDAO("genres") {};
};
#endif // GENREDAO_H
