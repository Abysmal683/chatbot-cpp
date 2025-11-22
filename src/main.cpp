#include <QApplication>
//#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    /*if(!DatabaseManager::instance().initialize()){
        qCritical() << "No se pudo iniciar la base de datos.";
        return 1;
    }*/
    /*MainWindow mainWindow;
    mainWindow.setWindowTitle("Inventario de Autos");
    mainWindow.resize(600,400);
    mainWindow.show();*/
    main window(this);
    window.resize(600,400);
    return window.exec();
}

