#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
namespace Ui {
class MainWindow;
}
class WelcomeWidget;
class GameLibraryWidget;
class ChatWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void goToWelcomeWidget();
    void goToChatWidget();
    void goToGameLibraryWidget();
private:
    Ui::MainWindow *ui;
    QStackedWidget *stack;
    WelcomeWidget *welcomeWidget;
    GameLibraryWidget *gameLibraryWidget;
    ChatWidget *chatWidget;
    void setupMenuBar();
    void setupStacked();
};

#endif // MAINWINDOW_H
