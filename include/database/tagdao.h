#ifndef TAGDAO_H
#define TAGDAO_H
#include "basesimpledao.h"
class TagDAO : public BaseSimpleDAO{
    public:
    TagDAO() : BaseSimpleDAO("tags"){};
};

#endif // TAGDAO_H
