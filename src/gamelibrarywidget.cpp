#include "gamelibrarywidget.h"
#include "ui_gamelibrarywidget.h"

GameLibraryWidget::GameLibraryWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameLibraryWidget)
{
    ui->setupUi(this);
}

GameLibraryWidget::~GameLibraryWidget()
{
    delete ui;
}
