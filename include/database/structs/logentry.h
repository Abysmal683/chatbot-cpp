#ifndef LOGENTRY_H
#define LOGENTRY_H
#include <QString>

struct LogEntry {
    int id = 0;
    QString level;
    QString message;
    QString created_at;   // texto ISO8601
};
#endif // LOGENTRY_H
