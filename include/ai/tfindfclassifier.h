//realia el calculo de peso de las reglas con ruleDAO
#ifndef TFIDFCLASSIFIER_H
#define TFIDFCLASSIFIER_H

#include <QString>
#include <QStringList>
#include <QVector>
#include <QHash>
#include <QPair>

class TextProcessor;
class RulesDAO; // forward declaration

class TFIDFClassifier
{
public:
    explicit TFIDFClassifier(TextProcessor *processor, RulesDAO* dao);

    // Cargar documentos manualmente (opcional)
    void addDocument(const QString &id, const QString &texto);
    void clear();

    // Reconstruye todos los vectores TF-IDF desde reglas activas
    void rebuild();

    // Clasificación / búsqueda
    QString classify(const QString &query) const;
    QVector<QPair<QString, double>> topN(const QString &query, int n = 3) const;

private:
    // Utilidades internas
    QStringList tokenize(const QString &text) const;
    QHash<QString, double> computeTf(const QStringList &tokens) const;
    QHash<QString, double> computeTfidf(const QHash<QString, double> &tf) const;
    double cosineSim(const QHash<QString, double> &v1, const QHash<QString, double> &v2) const;

    TextProcessor *processor;
    RulesDAO* rulesDao; // Puntero al DAO, no ownership

    // Base documentos: id → trigger
    QHash<QString, QString> documents;

    // Vectores TF-IDF normalizados: id → tfidf vector
    QHash<QString, QHash<QString, double>> tfidfVectors;

    // Frecuencias de documento: palabra → #documentos donde aparece
    QHash<QString, int> df;

    int totalDocs = 0;
};

#endif // TFIDFCLASSIFIER_H
