#ifndef MEMORYSHORTTERM_H
#define MEMORYSHORTTERM_H
#include <QString>

struct MemoryShortTerm {
    int id = 0;
    QString value;
    QString expires_at;      // Puede ser NULL → QString vacía
    QString related_intent;  // Puede ser NULL → QString vacía
    QString created_at;
};
#endif // MEMORYSHORTTERM_H
