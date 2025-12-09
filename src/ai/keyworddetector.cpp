#include "keyworddetector.h"
#include "textprocessor.h"
#include <QRegularExpression>
KeywordDetector::KeywordDetector(TextProcessor *processor)
    : processor(processor)
{
}

void KeywordDetector::setKeywords(const QStringList &keywords)
{
    this->keywords = keywords;
    rebuildCache();
}

void KeywordDetector::rebuildCache()
{
    normalizedKeywords.clear();

    TextProcessor *p = processor;
    if (!p) return;

    normalizedKeywords.reserve(keywords.size());

    for (const QString &kw : std::as_const(keywords))
        normalizedKeywords.append(p->normalizeText(kw));
}

QVector<QString> KeywordDetector::detectar(const QString &texto) const
{
    QVector<QString> encontrados;

    if (!processor || texto.isEmpty())
        return encontrados;
    // Tokenizar en espacios
    QSet<QString> tokens(
        processor->tokenize(texto).cbegin(),
        processor->tokenize(texto).cend()
        );

    // Comparación keywords-normalizadas
    for (int i = 0; i < normalizedKeywords.size(); ++i)
    {
        const QString &kwNorm = normalizedKeywords.at(i);
        const QString &kwOrig = keywords.at(i);

        // Coincidencia exacta por token
        if (tokens.contains(kwNorm)) {
            encontrados.append(kwOrig);
            continue;
        }

        // Coincidencia parcial
        if (processor->normalizeText(texto).contains(kwNorm))
            encontrados.append(kwOrig);
    }

    return encontrados;
}
