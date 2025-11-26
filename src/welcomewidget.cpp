#include "welcomewidget.h"
#include "ui_welcomewidget.h"

WelcomeWidget::WelcomeWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WelcomeWidget)
{
    ui->setupUi(this);

    connect(ui->pushButtonContinuar,&QPushButton::clicked,this,[=](){
        emit goToChatWidgetRequest();
    });
}

WelcomeWidget::~WelcomeWidget()
{
    delete ui;
}
