#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>

namespace Ui {
class editDialog;
}

class editDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editDialog(QWidget *parent = nullptr,int id = -1, QString website="", QString uname="", QString password="", QString comment="", QString keyX="");
    ~editDialog();

private slots:
    void on_updateBtn_clicked();

    void on_cancelBtn_clicked();

    void on_delBtn_clicked();

private:
    QString key,website;
    int id;
    Ui::editDialog *ui;
};

#endif // EDITDIALOG_H
