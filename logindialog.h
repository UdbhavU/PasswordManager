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
    explicit loginDialog(QWidget *parent = nullptr);
    int getLoginId();
    int login();
    ~loginDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    int loginId = -1;
    Ui::loginDialog *ui;
};

#endif // LOGINDIALOG_H
