#ifndef RULEENGINE_H
#define RULEENGINE_H

#include <QString>
#include <QVector>
#include "rule.h"  // Struct Rule ya definido

class TextProcessor;
class KeywordDetector;
class RulesDAO;
//busca encontrar triggers o palabras claves de rules para asi reaccionar
class RuleEngine
{
public:
    explicit RuleEngine(TextProcessor *processor,
                        KeywordDetector *detector,
                        RulesDAO *dao);

    // Cargar reglas activas desde DB
    void loadRules();

    // Agregar regla manualmente (opcional)
    void addRule(const Rule &rule);

    // Match: devuelve trigger de la regla encontrada o ""
    QString match(const QString &texto) const;

private:
    TextProcessor *processor;
    KeywordDetector *detector;
    RulesDAO *rulesDao;

    QVector<Rule> rules; // todas las reglas cargadas
};

#endif // RULEENGINE_H
