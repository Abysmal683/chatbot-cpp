#include "keyworddetector.h"
#include <QRegularExpression>
KeywordDetector::KeywordDetector()
{
}

void KeywordDetector::setKeywords(const QStringList &keywords)
{
    this->keywords = keywords;
    rebuildCache();
}

void KeywordDetector::rebuildCache()
{
     qDebug() << "[KeywordDetector] dentro de rebuildCache";
    normalizedKeywords.clear();
    normalizedKeywords.reserve(keywords.size());
    for (const QString &kw : std::as_const(keywords))
        normalizedKeywords.append(kw);
     qDebug() << "[KeywordDetector] saliendo de rebuild cache";
}

QVector<QString> KeywordDetector::detectar(const QString &texto,const QStringList &tokens) const
{
    qDebug() << "[KeywordDetector] dentro de dectectar";
    QVector<QString> encontrados;

    if (texto.isEmpty())
        return encontrados;

    QSet<QString> c_tokens(tokens.begin(), tokens.end());

    // Usar un QSet para filtrar duplicados
    QSet<QString> encontradosSet;

    // Comparación keywords-normalizadas
    qDebug() << "[KeywordDetector] entrando en for";
    for (int i = 0; i < normalizedKeywords.size(); ++i)
    {
        const QString &kwNorm = normalizedKeywords.at(i);
        const QString &kwOrig = keywords.at(i);

        // Coincidencia exacta por token
        if (tokens.contains(kwNorm)) {
            if (!encontradosSet.contains(kwOrig)) {
                encontrados.append(kwOrig);
                encontradosSet.insert(kwOrig);
                qDebug() << "[KeywordDetector] token exacto encontrado:" << kwOrig;
            }
            continue;
        }

        // Coincidencia parcial
        if (texto.contains(kwNorm)) {
            if (!encontradosSet.contains(kwOrig)) {
                encontrados.append(kwOrig);
                encontradosSet.insert(kwOrig);
                qDebug() << "[KeywordDetector] token parcial encontrado:" << kwOrig;
            }
        }
    }

    qDebug() << "[KeywordDetector] saliendo de dectectar";
    return encontrados;
}
