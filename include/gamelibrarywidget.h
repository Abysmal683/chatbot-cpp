#ifndef GAMELIBRARYWIDGET_H
#define GAMELIBRARYWIDGET_H

#include <QWidget>
#include <QSqlTableModel>
#include <QMap>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui {
class GameLibraryWidget;
}
QT_END_NAMESPACE

class GameLibraryWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameLibraryWidget(QSqlDatabase& db, QWidget *parent = nullptr);
    ~GameLibraryWidget();

private slots:
    void onComboBoxTablaChanged(int index);
    void onAgregarClicked();
    void onActualizarClicked();
    void onEliminarClicked();

private:
    Ui::GameLibraryWidget *ui;
    QSqlDatabase& db;
    QMap<QString, QSqlTableModel*> tableModels;

    void setupModels();
    void loadTable(const QString& tableName);

};

#endif // GAMELIBRARYWIDGET_H
