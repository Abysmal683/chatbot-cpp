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
    QString t = normalizeText(text);
    auto tokens = tokenize(t);
    tokens = removeStopWords(tokens);
    return stemWords(tokens);
}
// ---------------------------------
// NORMALIZACIÓN GENERAL
// ---------------------------------
QString TextProcessor::normalizeText(const QString &text) const
{
    QString t = text;
    t = t.toLower();
    t = removeSpecialChars(t);
    return t.simplified();
}

// ---------------------------------
// TOKENIZAR  (evita limpieza duplicada)
// ---------------------------------
QStringList TextProcessor::tokenize(const QString &text) const
{
    return normalizeText(text).split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
}

// ---------------------------------
// REMOVER STOP WORDS (seguro)
// ---------------------------------
QStringList TextProcessor::removeStopWords(const QStringList &tokens) const
{
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
    QString cleaned = text;
    cleaned.replace(QRegularExpression("[^a-zA-Z0-9áéíóúÁÉÍÓÚñÑ\\s]"), " ");
    return cleaned.trimmed();
}
