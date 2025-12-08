#include <QApplication>
#include "mainwindow.h"
#include "databasemanager.h"
#include <QTranslator>
#include <QLocale>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // -------------------------------
    // Inicializar Base de Datos
    // -------------------------------
    DataBaseManager& dbManager = DataBaseManager::instance();
    if (!dbManager.initialize()) {
        qCritical() << "No se pudo inicializar la base de datos. Saliendo...";
        return -1;
    }

    // -------------------------------
    // Configurar traducciones
    // -------------------------------
    /*QTranslator translator;
    QString locale = QLocale::system().name();
    QString path = QApplication::applicationDirPath() + "/translations";
    QString file = QString("ChatBot_%1.qm").arg(locale);

    if(translator.load(file, path)) {
        app.installTranslator(&translator);
        qDebug() << "Traducción cargada: " << path << "/" << file;
    } else {
        qWarning() << "No se pudo cargar traducción:" << path << "/" << file;
    }*/

    // -------------------------------
    // Mostrar ventana principal
    // -------------------------------
    MainWindow mainWindow;

    // Pasamos la referencia de la base de datos al MainWindow o a los widgets
    // Por ejemplo: mainWindow.setDatabase(DataBaseManager::instance().getDatabase());

    mainWindow.show();

    return app.exec();
}
