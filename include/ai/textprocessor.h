#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

#include <QString>
#include <QStringList>
#include <QSet>
//debe limpiar y preparar el texto para su posterior uso
class TextProcessor
{
public:
    TextProcessor();

    QString normalizeText(const QString& text) const;
    QStringList tokenize(const QString& text) const;
    QStringList removeStopWords(const QStringList& tokens) const;
    QString stemWord(const QString& word) const;        // Stemmer simple
    QStringList stemWords(const QStringList& tokens) const;
    QStringList process(const QString& text);
private:
    QString removeSpecialChars(const QString &text) const;

    QSet<QString> stopWords;
};

#endif // TEXTPROCESSOR_H
