#ifndef RULE_H
#define RULE_H

#include <QString>

struct Rule {
    int id = 0;
    QString trigger;         // palabra que activa la regla
    QString response;        // respuesta asociada
    int priority = 0;        // peso o prioridad de la regla
    QString category;        // opcional, categoría de la regla
    QString source = "manual";// de dónde viene la regla
    bool is_active = true;   // si la regla está activa
    QString created_at;      // timestamp de creación
    QString updated_at;      // timestamp de actualización
};

#endif // RULE_H
