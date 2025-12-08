#ifndef RULE_H
#define RULE_H

#include <QString>

struct Rule {
    int id = 0;
    QString trigger;     // palabra que activa la regla
    QString response;    // respuesta asociada
    int priority = 0;    // peso o prioridad de la regla
};

#endif // RULE_H
