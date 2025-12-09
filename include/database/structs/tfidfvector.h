#ifndef TFIDFVECTOR_H
#define TFIDFVECTOR_H

#include <QString>

struct TFIDFVector {
    int ruleId = 0;        // id de la regla
    QString token;          // palabra/token
    double tfidf = 0.0;    // valor TF-IDF
};

#endif // TFIDFVECTOR_H
