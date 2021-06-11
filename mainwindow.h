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
    void setSession(int id);

    ~MainWindow();
private slots:
    void on_actionExit_triggered();

private:
    int sessionID = -1;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
