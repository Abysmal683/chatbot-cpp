#ifndef KEYWORDDETECTOR_H
#define KEYWORDDETECTOR_H

#include <QString>
#include <QStringList>
#include <QVector>
#include <QSet>
//utiliza textproceesor para tokenizar la palabra pasada y encontrar parentescos en la db pasada
class TextProcessor; // forward declaration

class KeywordDetector {
public:
    explicit KeywordDetector(TextProcessor *processor);

    void setKeywords(const QStringList &keywords);
    QVector<QString> detectar(const QString &texto) const;

private:
    void rebuildCache();

    TextProcessor *processor;        // no ownership
    QStringList keywords;            // originales
    QStringList normalizedKeywords;  // normalizadas
};

#endif // KEYWORDDETECTOR_H
