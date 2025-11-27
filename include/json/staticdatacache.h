#ifndef STATICDATACACHE_H
#define STATICDATACACHE_H
#include <QStringList>
class StaticDataCache
{
     public:
        static QStringList genres;
        static QStringList platforms;
        static QStringList tags;

        static void loadAll();
};

#endif // STATICDATACACHE_H
