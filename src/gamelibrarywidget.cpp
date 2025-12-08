#include "gamelibrarywidget.h"
#include "ui_gamelibrarywidget.h"
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlError>
#include "constants.h"
GameLibraryWidget::GameLibraryWidget(QSqlDatabase& db, QWidget *parent)
    : QWidget(parent), ui(new Ui::GameLibraryWidget), db(db)
{
    ui->setupUi(this);

    // Lista de tablas
    ui->comboBoxTabla->addItems({
        Constants::Tables::Games,
        Constants::Tables::Genres,
        Constants::Tables::Platforms,
        Constants::Tables::Tags,
        Constants::Tables::Keywords,
        Constants::Tables::Rules,
        Constants::Tables::UserPreferences,
        Constants::Tables::Logs,
        Constants::Tables::MemoryLongTerm,
        Constants::Tables::MemoryShortTerm
    });

    // Inicializa modelos
    for (int i = 0; i < ui->comboBoxTabla->count(); ++i) {
        QString tableName = ui->comboBoxTabla->itemText(i);
        QSqlTableModel* model = new QSqlTableModel(this, db);
        model->setTable(tableName);
        model->setEditStrategy(QSqlTableModel::OnManualSubmit); // Manual!
        model->select();
        tableModels.insert(tableName, model);
    }

    connect(ui->comboBoxTabla, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &GameLibraryWidget::onComboBoxTablaChanged);
    connect(ui->pushButtonAgregar, &QPushButton::clicked,
            this, &GameLibraryWidget::onAgregarClicked);
    connect(ui->pushButtonActualizar, &QPushButton::clicked,
            this, &GameLibraryWidget::onActualizarClicked);
    connect(ui->pushButtonEliminar, &QPushButton::clicked,
            this, &GameLibraryWidget::onEliminarClicked);

    // Mostrar primera tabla
    loadTable(ui->comboBoxTabla->currentText());
}

GameLibraryWidget::~GameLibraryWidget()
{
    qDeleteAll(tableModels);
    delete ui;
}

// Inicializa QSqlTableModel para cada tabla
void GameLibraryWidget::setupModels()
{
    for (int i = 0; i < ui->comboBoxTabla->count(); ++i) {
        QString tableName = ui->comboBoxTabla->itemText(i);
        QSqlTableModel* model = new QSqlTableModel(this, db);
        model->setTable(tableName);
        model->setEditStrategy(QSqlTableModel::OnFieldChange);
        model->select();
        tableModels.insert(tableName, model);
    }
}

// Cambia tabla mostrada en QTableView
void GameLibraryWidget::loadTable(const QString& tableName)
{
    if (!tableModels.contains(tableName)) return;

    QSqlTableModel* model = tableModels[tableName];
    ui->tableViewLibreria->setModel(model);

    // Evitamos edición directa en la vista
    ui->tableViewLibreria->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableViewLibreria->resizeColumnsToContents();
}

// Combobox cambió
void GameLibraryWidget::onComboBoxTablaChanged(int index)
{
    QString tableName = ui->comboBoxTabla->itemText(index);
    loadTable(tableName);
}

// Botones CRUD (simple, se puede mejorar)
void GameLibraryWidget::onAgregarClicked()
{
    QString tableName = ui->comboBoxTabla->currentText();
    if (!tableModels.contains(tableName)) return;

    QSqlTableModel* model = tableModels[tableName];
    int row = model->rowCount();
    model->insertRow(row);

    // Abrir un diálogo o usar QInputDialog para pedir datos antes de submit
}

void GameLibraryWidget::onActualizarClicked()
{
    QString tableName = ui->comboBoxTabla->currentText();
    if (!tableModels.contains(tableName)) return;

    QSqlTableModel* model = tableModels[tableName];
    if (!model->submitAll()) {
        QMessageBox::warning(this, "Error", model->lastError().text());
    } else {
        model->select(); // Refresca la tabla
    }
}

void GameLibraryWidget::onEliminarClicked()
{
    QString tableName = ui->comboBoxTabla->currentText();
    if (!tableModels.contains(tableName)) return;

    QItemSelectionModel* sel = ui->tableViewLibreria->selectionModel();
    if (!sel || sel->selectedRows().isEmpty()) return;

    QSqlTableModel* model = tableModels[tableName];
    for (const QModelIndex& idx : sel->selectedRows()) {
        model->removeRow(idx.row());
    }

    if (!model->submitAll()) {
        QMessageBox::warning(this, "Error", model->lastError().text());
    } else {
        model->select();
    }
}
