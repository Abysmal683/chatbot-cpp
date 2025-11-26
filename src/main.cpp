#include <QApplication>
#include "mainwindow.h"
#include <QTranslator>
#include <QLocale>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTranslator translator;
    MainWindow mainWindow;
    //ubica la aplicacion y busca la carpeta de traduccion con los qm
    QString locale = QLocale::system().name();
    QString path = QApplication::applicationDirPath()+"/translations";
    QString file = QString("ChatBot_%1.qm").arg(locale);

    if(translator.load(file,path)){
        app.installTranslator(&translator);
        qDebug()<< "traduccion cargada: " << path << "/" << file;
    } else{
        qWarning() << "no se pudo cargar traduccion" << path << "/" << file;
    }
    mainWindow.show();
   return app.exec();
}

