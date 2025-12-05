#include "textprocessor.h"
#include <QRegularExpression>
#include <QSet>
#include <QStringList>

// -----------------------------
// Constructor: carga stopwords
// -----------------------------
TextProcessor::TextProcessor()
{
    stopWords = {
        "el","la","los","las","un","una","unos","unas",
        "de","del","al","a","en","por","para","con","sin",
        "y","o","pero","que","como","si","no","lo",
        "tu","su","mi","es","son","ser","hay"
    };
}

// -----------------------------
// NORMALIZACIÓN GENERAL
// -----------------------------
QString TextProcessor::normalizeText(const QString &text) const
{
    QString t = text;
    t = toLower(t);
    t = removeSpecialChars(t);
    return t.simplified();
}

// -----------------------------
// MINUSCULAS
// -----------------------------
QString TextProcessor::toLower(const QString &text) const
{
    return text.toLower();
}

// -----------------------------
// TOKENIZAR
// -----------------------------
QStringList TextProcessor::tokenize(const QString &text) const
{
    QString cleaned = removeSpecialChars(text);

    // Separar por espacios
    QStringList tokens = cleaned.split(
        QRegularExpression("\\s+"),
        Qt::SkipEmptyParts
        );

    return tokens;
}

// -----------------------------
// REMOVER STOP WORDS
// -----------------------------
QStringList TextProcessor::removeStopWords(const QStringList &tokens) const
{
    QStringList filtered;
    for (const QString &token : tokens)
        if (!stopWords.contains(token))
            filtered.append(token);

    return filtered;
}

// -----------------------------
// STEMMING / LEMMATIZACIÓN SIMPLE
// -----------------------------
QString TextProcessor::stemWord(const QString &word) const
{
    QString w = word;

    // Ejemplo MUY simplificado de stemmer español
    // (Sufijos comunes)
    const QStringList suffixes = {
        "mente", "ción", "sión",
        "ando", "iendo",
        "ado", "ido",
        "os", "as", "es", "s"
    };

    for (const QString &suf : suffixes)
    {
        if (w.endsWith(suf) && w.length() > suf.length())
        {
            return w.left(w.length() - suf.length());
        }
    }
    return w;
}

// Procesar lista de tokens
QStringList TextProcessor::stemWords(const QStringList &tokens) const
{
    QStringList result;
    for (const QString &t : tokens)
        result.append(stemWord(t));

    return result;
}

// -----------------------------
// Remover caracteres especiales
// -----------------------------
QString TextProcessor::removeSpecialChars(const QString &text) const
{
    QString cleaned = text;

    // Permitir solo letras y espacios
    cleaned.replace(QRegularExpression("[^a-zA-ZáéíóúÁÉÍÓÚñÑ\\s]"), " ");

    return cleaned;
}
