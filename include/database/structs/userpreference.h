#ifndef USERPREFERENCE_H
#define USERPREFERENCE_H

#include <QString>

struct UserPreference {
    int id = 0;
    QString key;
    QString value;
    QString updated_at;   // ISO8601
};
#endif // USERPREFERENCE_H
