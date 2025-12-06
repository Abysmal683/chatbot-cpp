#ifndef KEYWORDDETECTOR_H
#define KEYWORDDETECTOR_H

#include <QString>
#include <QStringList>
#include <QVector>
#include <QSet>

class TextProcessor; // Forward declaration

class KeywordDetector {
public:
    explicit KeywordDetector(TextProcessor *textProcessor);

    void setKeywords(const QStringList &keywords);

    QVector<QString> detectar(const QString &texto) const;

private:
    void rebuildCache();

    TextProcessor *textProcessor;   // No ownership
    QStringList keywords;
    QStringList normalizedKeywords;
};

#endif // KEYWORDDETECTOR_H
