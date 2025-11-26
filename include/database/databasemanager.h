#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QSqlDatabase>
class DataBaseManager{
    public:
        static DataBaseManager &instance();
        bool initialize();
        QSqlDatabase &getDatabase();
    private:
        DataBaseManager();
        bool createTables();
        QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
