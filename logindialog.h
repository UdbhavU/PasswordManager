#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include "mainwindow.h"

#include <QDialog>

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = nullptr,QString *pass=0);

    int login();
    ~loginDialog();

    int getLoginStatus();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


private:
    QString *key;
    int loginStatus = -1;
    Ui::loginDialog *ui;
};

#endif // LOGINDIALOG_H
