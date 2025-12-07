#ifndef BASERELATIONDAO_H
#define BASERELATIONDAO_H

#include <QString>
#include <QList>
#include <QSqlDatabase>
class BaseRelationDAO
{
public:
    BaseRelationDAO(const QString& tableName,
                    const QString& leftColumn,
                    const QString& rightColumn,
                    QSqlDatabase& db);

    // Métodos genéricos
    bool add(int leftId, int rightId) const;
    bool remove(int leftId, int rightId) const;
    bool clearLeft(int leftId) const;
    QList<int> getRights(int leftId) const;
    QList<int> getLefts(int rightId) const;
    bool exists(int leftId, int rightId) const;

protected:
    QString tableName;
    QString leftCol;
    QString rightCol;
    QSqlDatabase& db;
};

#endif // BASERELATIONDAO_H
