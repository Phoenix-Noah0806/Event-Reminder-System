#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTableWidgetItem>
#include <QHeaderView>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QFile>
#include <QStandardPaths>
#include <QDir>
#include <QCloseEvent>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Ensure table has 4 columns & headers
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList{"Title", "Description", "Date", "Done"});
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    ui->tableWidget->setWordWrap(true);

    // Connect buttons
    connect(ui->quickAddButton, &QPushButton::clicked, this, &MainWindow::on_quickAddButton_clicked);
    connect(ui->addButton, &QPushButton::clicked, this, &MainWindow::on_addButton_clicked);
    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::on_removeButton_clicked);
    connect(ui->toggleButton, &QPushButton::clicked, this, &MainWindow::on_toggleButton_clicked);
    connect(ui->viewCompletedButton, &QPushButton::clicked, this, &MainWindow::on_viewCompletedButton_clicked);
    connect(ui->filterComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::on_filterComboBox_currentIndexChanged);

    // Make sure filter has the 3 common entries
    if (ui->filterComboBox->count() == 0)
        ui->filterComboBox->addItems(QStringList{"All", "Completed", "Pending"});

    // Load saved events from previous session
    loadEvents();
}

MainWindow::~MainWindow()
{
    saveEvents();
    delete ui;
}

// -------------------- helper that inserts a row --------------------
void MainWindow::addEvent(const QString &title, const QString &desc, const QDate &date, bool completed)
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    auto *itTitle = new QTableWidgetItem(title);
    itTitle->setFlags(itTitle->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
    ui->tableWidget->setItem(row, 0, itTitle);

    auto *itDesc = new QTableWidgetItem(desc);
    itDesc->setFlags(itDesc->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
    ui->tableWidget->setItem(row, 1, itDesc);

    auto *itDate = new QTableWidgetItem(date.toString(Qt::ISODate));
    itDate->setFlags(itDate->flags() | Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
    ui->tableWidget->setItem(row, 2, itDate);

    auto *itDone = new QTableWidgetItem();
    itDone->setFlags(itDone->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    itDone->setCheckState(completed ? Qt::Checked : Qt::Unchecked);
    ui->tableWidget->setItem(row, 3, itDone);

    // Adjust row height so wrapped text is visible
    ui->tableWidget->resizeRowsToContents();
}

// -------------------- Quick Add --------------------
void MainWindow::on_quickAddButton_clicked()
{
    QString title = ui->titleLineEdit->text().trimmed();
    QString desc  = ui->descriptionLineEdit->text().trimmed();

    if (title.isEmpty()) {
        QMessageBox::warning(this, "Missing title", "Please type a title in the top field before Quick Add.");
        return;
    }

    QDate date = ui->dateEdit->date();
    addEvent(title, desc, date, false);

    ui->titleLineEdit->clear();
    ui->descriptionLineEdit->clear();
}

// -------------------- Add (dialog or same as quick) --------------------
void MainWindow::on_addButton_clicked()
{
    // Currently same as Quick Add
    on_quickAddButton_clicked();
}

// -------------------- Remove --------------------
void MainWindow::on_removeButton_clicked()
{
    auto rows = ui->tableWidget->selectionModel()->selectedRows();
    if (rows.isEmpty()) {
        QMessageBox::information(this, "Remove", "No events selected.");
        return;
    }
    if (QMessageBox::question(this, "Confirm", QString("Remove %1 selected event(s)?").arg(rows.size()))
        != QMessageBox::Yes) return;

    QList<int> toRemove;
    for (const QModelIndex &m : rows) toRemove << m.row();
    std::sort(toRemove.begin(), toRemove.end(), std::greater<int>());
    for (int r : toRemove) ui->tableWidget->removeRow(r);
}

// -------------------- Toggle completed --------------------
void MainWindow::on_toggleButton_clicked()
{
    auto rows = ui->tableWidget->selectionModel()->selectedRows();
    if (rows.isEmpty()) return;
    for (const QModelIndex &m : rows) {
        int r = m.row();
        QTableWidgetItem *it = ui->tableWidget->item(r, 3);
        if (!it) continue;
        it->setCheckState(it->checkState() == Qt::Checked ? Qt::Unchecked : Qt::Checked);
    }
}

// -------------------- View Completed --------------------
void MainWindow::on_viewCompletedButton_clicked()
{
    ui->filterComboBox->setCurrentIndex(1);
    showOnlyCompleted();
}

// -------------------- Filtering --------------------
void MainWindow::on_filterComboBox_currentIndexChanged(int index)
{
    if (index == 0) showAllRows();
    else if (index == 1) showOnlyCompleted();
    else if (index == 2) showOnlyPending();
}

void MainWindow::showAllRows()
{
    for (int i=0; i<ui->tableWidget->rowCount(); ++i) ui->tableWidget->setRowHidden(i, false);
}

void MainWindow::showOnlyCompleted()
{
    for (int i=0; i<ui->tableWidget->rowCount(); ++i) {
        QTableWidgetItem *it = ui->tableWidget->item(i, 3);
        bool done = it && it->checkState() == Qt::Checked;
        ui->tableWidget->setRowHidden(i, !done);
    }
}

void MainWindow::showOnlyPending()
{
    for (int i=0; i<ui->tableWidget->rowCount(); ++i) {
        QTableWidgetItem *it = ui->tableWidget->item(i, 3);
        bool done = it && it->checkState() == Qt::Checked;
        ui->tableWidget->setRowHidden(i, done);
    }
}

// -------------------- Persistence --------------------
QString MainWindow::storagePath() const
{
    QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dir);
    return QDir(dir).filePath("events.json");
}

void MainWindow::saveEvents() const
{
    QJsonArray arr;
    for (int i=0; i<ui->tableWidget->rowCount(); ++i) {
        QJsonObject o;
        o["title"] = ui->tableWidget->item(i,0) ? ui->tableWidget->item(i,0)->text() : QString();
        o["desc"]  = ui->tableWidget->item(i,1) ? ui->tableWidget->item(i,1)->text() : QString();
        o["date"]  = ui->tableWidget->item(i,2) ? ui->tableWidget->item(i,2)->text() : QString();
        o["completed"] = ui->tableWidget->item(i,3) ? (ui->tableWidget->item(i,3)->checkState() == Qt::Checked) : false;
        arr.append(o);
    }
    QJsonDocument doc(arr);
    QFile f(storagePath());
    if (!f.open(QIODevice::WriteOnly)) {
        qWarning("Could not write events.json");
        return;
    }
    f.write(doc.toJson(QJsonDocument::Indented));
    f.close();
}

void MainWindow::loadEvents()
{
    QFile f(storagePath());
    if (!f.exists()) return;
    if (!f.open(QIODevice::ReadOnly)) {
        qWarning("Could not open events.json");
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    f.close();
    if (!doc.isArray()) return;
    ui->tableWidget->setRowCount(0);
    for (const QJsonValue &v : doc.array()) {
        if (!v.isObject()) continue;
        QJsonObject o = v.toObject();
        QDate date = QDate::fromString(o.value("date").toString(), Qt::ISODate);
        if (!date.isValid()) date = QDate::currentDate();
        addEvent(o.value("title").toString(), o.value("desc").toString(), date, o.value("completed").toBool(false));
    }
}

// -------------------- Save on close --------------------
void MainWindow::closeEvent(QCloseEvent *event)
{
    saveEvents();
    QMainWindow::closeEvent(event);
}
