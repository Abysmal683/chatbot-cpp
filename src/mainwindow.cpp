#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "welcomewidget.h"
#include "chatwidget.h"
#include "gamelibrarywidget.h"
#include "databasemanager.h"
#include <QMenuBar>
#include <QAction>
#include <QVBoxLayout>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupStacked();
    setupMenuBar();
    setCentralWidget(stack);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setupStacked(){
    //se declaran los punteros
    stack = new QStackedWidget(this);
    welcomeWidget = new WelcomeWidget(this);
    chatWidget = new ChatWidget(this);

    gameLibraryWidget = new GameLibraryWidget(DataBaseManager::instance().getDatabase(),this);
    //se agregan los widgets al stacked e indica el primero
    stack->addWidget(welcomeWidget);
    stack->addWidget(chatWidget);
    stack->addWidget(gameLibraryWidget);
    stack->setCurrentWidget(welcomeWidget);
    //se crea un connet para x widget
    connect(welcomeWidget,&WelcomeWidget::goToChatWidgetRequest,
        this,&MainWindow::goToChatWidget);
}
void MainWindow::setupMenuBar(){
    QMenu *menuInicio = menuBar()->addMenu(tr("Inicio"));
    QMenu *menuChat = menuBar()->addMenu(tr("Chat Bot"));
    QMenu *menuLibreria = menuBar()->addMenu(tr("Librería"));
    QAction *actWelcome = menuInicio->addAction(tr("Pantalla de Inicio"));
    QAction *actChat = menuChat->addAction(tr("Abrir Chat"));
    QAction *actLibrary = menuLibreria->addAction(tr("Juegos"));
    connect(actWelcome,&QAction::triggered,this,&MainWindow::goToWelcomeWidget);
    connect(actChat,&QAction::triggered,this,&MainWindow::goToChatWidget);
    connect(actLibrary,&QAction::triggered,this,&MainWindow::goToGameLibraryWidget);
}
void MainWindow::goToWelcomeWidget(){
    stack->setCurrentWidget(welcomeWidget);
}
void MainWindow::goToChatWidget(){
    stack->setCurrentWidget(chatWidget);
}
void MainWindow::goToGameLibraryWidget(){
    stack->setCurrentWidget(gameLibraryWidget);
}
