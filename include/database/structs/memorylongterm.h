#ifndef MEMORYLONGTERM_H
#define MEMORYLONGTERM_H

#include <QString>

struct MemoryLongTerm {
    int id = 0;
    QString key;
    QString value;
    int importance = 5;
    QString created_at;   // texto ISO8601
};

#endif // MEMORYLONGTERM_H
