#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void fillTable();


    ~MainWindow();
private slots:
    void on_actionExit_triggered();

    void on_actionExport_triggered();

    void on_actionMake_new_entry_triggered();

    void on_actionImport_triggered();

    void on_tblView_clicked(const QModelIndex &index);

    void on_actionRefresh_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionAbout_Password_Manager_triggered();

private:
    QString key;
    int sessionId = -1;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
