#include "dbmanager.h"
#include "editdialog.h"
#include "ui_editdialog.h"
#include <QDebug>
editDialog::editDialog(QWidget *parent, QString website, QString uname, QString password, QString comment,QString keyX) :
    QDialog(parent),
    ui(new Ui::editDialog)
{
    key = keyX;
    ui->setupUi(this);
    ui->website->setText(website);
    ui->website->setEnabled(false);
    ui->uname->setText(uname);
    ui->password->setText(password);
    ui->comment->setPlainText(comment);
}


void editDialog::on_updateBtn_clicked()
{
    QString uname = ui->uname->text();
    QString website = ui->website->text();
    QString comment = ui->comment->toPlainText();
    QString password= ui->password->text();
    qDebug()<<uname<<website<<comment<<password;
    DbManager db;
    if(db.updateEntry(website,uname,password,comment,key)){
        this->close();
}
}
editDialog::~editDialog()
{
    delete ui;
}
