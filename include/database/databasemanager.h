#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H
#include <QSqlDatabase>
class DataBaseManager{
    public:
        static DataBaseManager &instance();
        bool initialize();
        QSqlDatabase &getDatabase();
        //Control de conexion
        bool open();
        void close();
        bool isOpen() const;
        //Transacciones
        bool beginTransaction();
        bool commit();
        void rollback();
        //Funciones utilitarias
        bool clearTable(const QString &tableName);




    private:
        DataBaseManager();
        DataBaseManager(const DataBaseManager&) = delete;
        DataBaseManager& operator=(const DataBaseManager&) = delete;
        bool createTables();
        QSqlDatabase db;
        //Funciones utilitarias
        bool rebuildFTS();

};

#endif // DATABASEMANAGER_H
