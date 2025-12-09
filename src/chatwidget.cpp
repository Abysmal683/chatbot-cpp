#include "chatwidget.h"
#include "aiengine.h"
#include "ui_chatwidget.h"

ChatWidget::ChatWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatWidget)
{
    ui->setupUi(this);

    // Crear la instancia de AIEngine
    aiEngine = new AIEngine();

    // Conectar señales
    connect(ui->pushButtonEnviar, &QPushButton::clicked,
            this, &ChatWidget::onSendClicked);

    connect(ui->lineEditRespuesta, &QLineEdit::returnPressed,
            this, &ChatWidget::onReturnPressed);
}

ChatWidget::~ChatWidget()
{
    delete aiEngine;
    delete ui;
}

void ChatWidget::onSendClicked()
{
    QString userInput = ui->lineEditRespuesta->text().trimmed();
    if (userInput.isEmpty())
        return;

    // Mostrar mensaje del usuario
    appendToHistory("Usuario", userInput);
    ui->lineEditRespuesta->clear();

    // Obtener respuesta de la AI
    QString response = aiEngine->process(userInput, true, true, 5);

    // Mostrar respuesta de la AI
    appendToHistory("Bot", response);
}

void ChatWidget::onReturnPressed()
{
    onSendClicked();  // Mismo comportamiento que el botón
}

void ChatWidget::appendToHistory(const QString& sender, const QString& message)
{
    QString formatted = QString("<b>%1:</b> %2").arg(sender, message);
    ui->textBrowserHistorial->append(formatted);
}
