//realia el calculo de peso de las reglas con ruleDAO
#ifndef TFIDFCLASSIFIER_H
#define TFIDFCLASSIFIER_H

#include <QString>
#include <QStringList>
#include <QVector>
#include <QHash>
#include <QPair>
//carga, guarda, y crea los pesos de las rules con ruledao y tfindao
class TextProcessor;
class RulesDAO; // forward declaration
class TFIDFVectorDAO;

class TFIDFClassifier
{
public:
    explicit TFIDFClassifier(TextProcessor *processor, RulesDAO* rules,TFIDFVectorDAO* vector);

    // Cargar documentos manualmente (opcional)
    void addDocument(const QString &id, const QString &texto);
    void clear();

    // Reconstruye todos los vectores TF-IDF desde reglas activas
    void rebuild();
    void rebuildIfNeeded();
    // Clasificación / búsqueda
    QString classify(const QString &query) const;
    QVector<QPair<QString, double>> topN(const QString &query, int n = 3) const;
private:
    int rulesVersion = 0; // versión de las reglas
    // Utilidades internas
    QHash<QString, double> computeTf(const QStringList &tokens) const;
    QHash<QString, double> computeTfidf(const QHash<QString, double> &tf) const;
    double cosineSim(const QHash<QString, double> &v1, const QHash<QString, double> &v2) const;

    TextProcessor *processor;
    RulesDAO* rulesDao; // Puntero al DAO, no ownership
    TFIDFVectorDAO* vecDao;
    // Base documentos: id → trigger
    QHash<QString, QString> documents;

    // Vectores TF-IDF normalizados: id → tfidf vector
    QHash<QString, QHash<QString, double>> tfidfVectors;

    // Frecuencias de documento: palabra → #documentos donde aparece
    QHash<QString, int> df;

    int totalDocs = 0;
};

#endif // TFIDFCLASSIFIER_H
