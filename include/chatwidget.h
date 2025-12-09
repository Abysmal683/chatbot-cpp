#ifndef CHATWIDGET_H
#define CHATWIDGET_H

#include <QWidget>
#include "ai/aiengine.h"  // Asegúrate de tener el AIEngine

namespace Ui {
class ChatWidget;
}

class ChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChatWidget(QWidget *parent = nullptr);
    ~ChatWidget();

private slots:
    void onSendClicked();
    void onReturnPressed();

private:
    Ui::ChatWidget *ui;
    AIEngine* aiEngine;  // Instancia de la AI

    void appendToHistory(const QString& sender, const QString& message);
};

#endif // CHATWIDGET_H
