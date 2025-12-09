#ifndef KEYWORDDETECTOR_H
#define KEYWORDDETECTOR_H

#include <QString>
#include <QStringList>
#include <QVector>
#include <QSet>
//utiliza textproceesor para tokenizar la palabra pasada y encontrar parentescos en la db pasada
class KeywordDetector {
public:
    explicit KeywordDetector();

    void setKeywords(const QStringList &keywords);
    QVector<QString> detectar(const QString &texto,const QStringList &tokens) const;

private:
    void rebuildCache();
    QStringList keywords;            // originales
    QStringList normalizedKeywords;  // normalizadas
};

#endif // KEYWORDDETECTOR_H
