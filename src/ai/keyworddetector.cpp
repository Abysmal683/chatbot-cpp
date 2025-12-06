#include "keyworddetector.h"
#include "textprocessor.h"

KeywordDetector::KeywordDetector(TextProcessor *textProcessor)
    : textProcessor(textProcessor)
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

    if (!textProcessor)
        return;

    for (int i = 0; i < keywords.size(); ++i) {
        const QString &kw = keywords.at(i);
        normalizedKeywords.append(textProcessor->normalizeText(kw));
    }
}

QVector<QString> KeywordDetector::detectar(const QString &texto) const
{
    QVector<QString> encontrados;

    if (!textProcessor || texto.isEmpty())
        return encontrados;

    QString normalizado = textProcessor->normalizeText(texto);

    // Tokenizar y convertir a conjunto para búsqueda O(1)
    QStringList tokensList = normalizado.split(' ', Qt::SkipEmptyParts);
    QSet<QString> tokens(tokensList.begin(), tokensList.end());

    for (int i = 0; i < normalizedKeywords.size(); ++i) {

        const QString &kwNorm = normalizedKeywords.at(i);
        const QString &kwOriginal = keywords.at(i);

        // Coincidencia exacta por token
        if (tokens.contains(kwNorm)) {
            encontrados.append(kwOriginal);
            continue;
        }

        // Coincidencia parcial
        if (normalizado.contains(kwNorm)) {
            encontrados.append(kwOriginal);
        }
    }

    return encontrados;
}
