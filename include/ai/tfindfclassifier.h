#ifndef TFIDFCLASSIFIER_H
#define TFIDFCLASSIFIER_H

#include <QString>
#include <QStringList>
#include <QVector>
#include <QHash>

class TextProcessor; // forward declaration

class TFIDFClassifier
{
public:
    explicit TFIDFClassifier(TextProcessor *processor);

    // Cargar documentos
    void addDocument(const QString &id, const QString &texto);
    void clear();

    // Reconstruye todos los vectores de TF-IDF
    void rebuild();

    // Clasificación / búsqueda
    QString classify(const QString &query) const;                // mejor match
    QVector<QPair<QString, double>> topN(const QString &query,
        int n = 3) const;       // top N matches

private:
    // Utilidades internas
    QStringList tokenize(const QString &text) const;
    QHash<QString, double> computeTf(const QStringList &tokens) const;
    QHash<QString, double> computeTfidf(const QHash<QString, double> &tf) const;
    double cosineSim(const QHash<QString, double> &v1,
        const QHash<QString, double> &v2) const;

private:
    TextProcessor *processor;

    // Base documentos
    QHash<QString, QString> documents;

    // Vectores TF-IDF normalizados
    QHash<QString, QHash<QString, double>> tfidfVectors;

    // Frecuencias de documento: palabra → #documentos donde aparece
    QHash<QString, int> df;

    int totalDocs = 0;
};

#endif // TFIDFCLASSIFIER_H
