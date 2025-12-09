#include "textprocessor.h"
#include <QRegularExpression>

// ---------------------------------
// Constructor: carga stopwords
// ---------------------------------
TextProcessor::TextProcessor()
{
    stopWords = {
        "el","la","los","las","un","una","unos","unas",
        "de","del","al","a","en","por","para","con","sin",
        "y","o","pero","que","como","si","no","lo",
        "tu","su","mi","es","son","ser","hay"
    };
}
QStringList TextProcessor::process(const QString& text)
{
    QStringList tokens;
    tokens = removeStopWords(tokenize(text));
    return stemWords(tokens);
}
// ---------------------------------
// NORMALIZACIÓN GENERAL
// ---------------------------------
QString TextProcessor::normalizeText(const QString &text) const
{
    //qDebug() << "[TextProcessor] normalize text";
    QString t = text;
    t = t.toLower();
    t = removeSpecialChars(t);
    //qDebug() << "[TextProcessor] retornando simplificado";
    return t.simplified();
}

// ---------------------------------
// TOKENIZAR  (evita limpieza duplicada)
// ---------------------------------
QStringList TextProcessor::tokenize(const QString &text) const
{
    //qDebug() << "[TextProcessor] tokenizando";
    return normalizeText(text).split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
}

// ---------------------------------
// REMOVER STOP WORDS (seguro)
// ---------------------------------
QStringList TextProcessor::removeStopWords(const QStringList &tokens) const
{
    //qDebug() << "[TextProcessor] remove stopswords";
    QStringList filtered;
    filtered.reserve(tokens.size());

    for (const QString &token : tokens)
    {
        QString t = token.toLower();
        if (!stopWords.contains(t))
            filtered.append(t);
    }
    return filtered;
}

// ---------------------------------
// STEMMER SIMPLE (mejor validación)
// ---------------------------------
QString TextProcessor::stemWord(const QString &word) const
{
    //qDebug() << "[TextProcessor] steam word";
    QString w = word;

    const QStringList suffixes = {
        "mente", "ción", "sión",
        "ando", "iendo",
        "ado", "ido",
        "os", "as", "es", "s"
    };

    for (const QString &suf : suffixes)
    {
        if (w.endsWith(suf))
        {
            if (w.length() - suf.length() >= 3)
                return w.left(w.length() - suf.length());
        }
    }
    return w;
}

// ---------------------------------
// STEM LIST
// ---------------------------------
QStringList TextProcessor::stemWords(const QStringList &tokens) const
{
    //qDebug() << "[TextProcessor] stem words";
    QStringList result;
    result.reserve(tokens.size());

    for (const QString &t : tokens)
        result.append(stemWord(t));

    return result;
}

// ---------------------------------
// REMOVER CARACTERES ESPECIALES (permitir números)
// ---------------------------------
QString TextProcessor::removeSpecialChars(const QString &text) const
{
    //qDebug() << "[TextProcessor] remover special caracteres";
    QString cleaned = text;
    cleaned.replace(QRegularExpression("[^a-zA-Z0-9áéíóúÁÉÍÓÚñÑ\\s]"), " ");
    return cleaned.trimmed();
}
