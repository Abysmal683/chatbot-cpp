#ifndef BASESIMPLEDAO_H
#define BASESIMPLEDAO_H

#include <QString>

class BaseSimpleDAO
{
    public:
        explicit BaseSimpleDAO(const QString& tableName);
        virtual ~BaseSimpleDAO() = default;

        // CRUD genérico
        QList<QPair<int, QString>> getAll() const;
        int insert(const QString& name) const;
        bool remove(int id) const;
        bool update(int id, const QString& name) const;

        // Utilitarios
        bool exists(const QString& name) const;
        QString getNameById(int id) const;
        int getIdByName(const QString& name) const;
        int count() const;

    protected:
        QString table;
};

#endif // BASESIMPLEDAO_H
