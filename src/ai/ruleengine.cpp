#include "ruleengine.h"
#include "textprocessor.h"
#include "keyworddetector.h"

RuleEngine::RuleEngine(TextProcessor *processor, KeywordDetector *detector)
    : processor(processor), detector(detector)
{
}

void RuleEngine::addRule(const QString &intentId, const QStringList &keywords)
{
    rules.append({intentId, keywords});
}

QString RuleEngine::match(const QString &texto) const
{
    if (!processor || !detector || texto.isEmpty())
        return "";

    QString normalizado = processor->normalizeText(texto);
    QStringList tokens = normalizado.split(' ', Qt::SkipEmptyParts);

    for (const Rule &r : rules) {

        bool ok = true;

        for (const QString &kw : r.keywords) {
            QString norm = processor->normalizeText(kw);
            if (!tokens.contains(norm)) {
                ok = false;
                break;
            }
        }

        if (ok)
            return r.intentId;
    }

    return "";
}
