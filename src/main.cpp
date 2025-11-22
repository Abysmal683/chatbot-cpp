#include <QApplication>
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    /*if(!DatabaseManager::instance().initialize()){
        qCritical() << "No se pudo iniciar la base de datos.";
        return 1;
    }*/
    MainWindow mainWindow;
    mainWindow.setWindowTitle("Chat Bot");
    mainWindow.show();
   return app.exec();
}

