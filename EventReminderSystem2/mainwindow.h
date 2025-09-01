#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_quickAddButton_clicked();
    void on_addButton_clicked();
    void on_removeButton_clicked();
    void on_toggleButton_clicked();
    void on_viewCompletedButton_clicked();
    void on_filterComboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;

    // helpers
    void addEvent(const QString &title, const QString &desc, const QDate &date, bool completed=false);
    void showAllRows();
    void showOnlyCompleted();
    void showOnlyPending();

    // persistence
    QString storagePath() const;
    void saveEvents() const;
    void loadEvents();
};

#endif // MAINWINDOW_H
