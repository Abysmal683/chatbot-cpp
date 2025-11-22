#ifndef GAMELIBRARYWIDGET_H
#define GAMELIBRARYWIDGET_H

#include <QWidget>

namespace Ui {
class GameLibraryWidget;
}

class GameLibraryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameLibraryWidget(QWidget *parent = nullptr);
    ~GameLibraryWidget();

private:
    Ui::GameLibraryWidget *ui;
};

#endif // GAMELIBRARYWIDGET_H
