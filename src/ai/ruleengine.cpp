#include "ruleengine.h"
#include "textprocessor.h"
#include "keyworddetector.h"
#include "rulesdao.h"
#include <algorithm>
#include <QDebug>

RuleEngine::RuleEngine(TextProcessor *processor,
                       KeywordDetector *detector,
                       RulesDAO *dao)
    : processor(processor), detector(detector), rulesDao(dao)
{
}

/**
 * Carga las reglas activas desde la base de datos
 * y las ordena por prioridad descendente.
 */
void RuleEngine::loadRules()
{
    if (!rulesDao)
        return;

    QList<Rule> activeRules = rulesDao->getActiveRules();

    // Ordenar por prioridad descendente
    std::sort(activeRules.begin(), activeRules.end(),
              [](const Rule &a, const Rule &b) { return a.priority > b.priority; });

    // Convertir a QVector para acceso rápido
    rules = QVector<Rule>(activeRules.begin(), activeRules.end());
}

/**
 * Permite agregar reglas manualmente, opcional
 */
void RuleEngine::addRule(const Rule &rule)
{
    rules.append(rule);
}

/**
 * Busca la primera regla cuyo trigger esté contenido en el texto normalizado
 * Devuelve trigger de la regla o "" si no hay coincidencias.
 */
QString RuleEngine::match(const QString &texto) const
{
    if (!processor || !detector || texto.isEmpty())
        return "";

    QString normalizedText = processor->normalizeText(texto);

    for (const Rule &r : rules) {
        // Solo verificar coincidencia directa
        if (normalizedText.contains(r.trigger))
            return r.trigger; // Si quieres, podrías devolver r.response
    }

    return "";
}
