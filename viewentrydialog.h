#ifndef VIEWENTRYDIALOG_H
#define VIEWENTRYDIALOG_H

#include "editdialog.h"

#include <QDialog>

namespace Ui {
class viewEntryDialog;
}

class viewEntryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit viewEntryDialog(QWidget *parent = nullptr, int id=-1,QString website="", QString uname="", QString password="", QString comment="",QString keyX="");
    ~viewEntryDialog();

private slots:
    void on_editBtn_clicked();

    void on_cpyPass_clicked();

    void on_cpyUname_clicked();

private:
    QString key;
    QString Pass,uname;
    editDialog *ed;
    Ui::viewEntryDialog *ui;
};

#endif // VIEWENTRYDIALOG_H
