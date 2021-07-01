#include "dbmanager.h"
#include "editdialog.h"
#include "ui_editdialog.h"
#include <QDebug>
editDialog::editDialog(QWidget *parent, int id, QString website, QString uname, QString password, QString comment, QString keyX) :
    QDialog(parent),
    ui(new Ui::editDialog)
{
    this->id = id;
    this->website = website;
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
    if(db.updateEntry(id,website,uname,password,comment,key)){
        this->close();
}
}
editDialog::~editDialog()
{
    delete ui;
}

void editDialog::on_cancelBtn_clicked()
{
    this->close();
}


void editDialog::on_delBtn_clicked()
{
    DbManager db;
    if(db.deleteEntry(website,id,key)){
        this->close();
}
}

