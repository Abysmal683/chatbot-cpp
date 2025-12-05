#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

#include <QString>
#include <QStringList>
#include <QSet>

class TextProcessor
{
public:
    TextProcessor();

    QString normalizeText(const QString& text) const;
    QString toLower(const QString& text) const;

    QStringList tokenize(const QString& text) const;
    QStringList removeStopWords(const QStringList& tokens) const;
    QString removeSpecialChars(const QString &text) const;
    QString stemWord(const QString& word) const;        // Stemmer simple
    QStringList stemWords(const QStringList& tokens) const;

private:
    QSet<QString> stopWords;
};

#endif // TEXTPROCESSOR_H
