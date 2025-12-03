#ifndef RULE_H
#define RULE_H
#include <QString>

struct Rule {
    int id = 0;
    QString trigger;
    QString response;
    int priority = 0;
};

#endif // RULE_H
