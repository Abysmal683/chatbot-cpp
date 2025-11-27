#ifndef BASERELATIONDAO_H
#define BASERELATIONDAO_H

#include <QString>
#include <QList>

class BaseRelationDAO
{
public:
    BaseRelationDAO(const QString& tableName,
                    const QString& leftColumn,
                    const QString& rightColumn);

    // Métodos genéricos
    bool add(int leftId, int rightId) const;
    bool remove(int leftId, int rightId) const;
    bool clearLeft(int leftId) const;
    QList<int> getRights(int leftId) const;
    QList<int> getLefts(int rightId) const;
    bool exists(int leftId, int rightId) const;

protected:
    QString table;
    QString leftCol;
    QString rightCol;
};

#endif // BASERELATIONDAO_H
