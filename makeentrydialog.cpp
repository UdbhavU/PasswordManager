#include "dbmanager.h"
#include "makeentrydialog.h"
#include "ui_makeentrydialog.h"

#include <QMessageBox>

makeEntryDialog::makeEntryDialog(QWidget *parent,QString tkey) :
    QDialog(parent),
    ui(new Ui::makeEntryDialog)
{
    this->key=tkey;
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);
    ui->rePassword->setEchoMode(QLineEdit::Password);
}

makeEntryDialog::~makeEntryDialog()
{
    delete ui;
}

void makeEntryDialog::on_commandLinkButton_clicked()
{
   this->close();
}


void makeEntryDialog::on_pushButton_clicked()
{
    QString uname = ui->uname->text();
    QString website = ui->website->text();
    QString comment = ui->comment->toPlainText();
    QString password= ui->password->text();;
    if(password != ui->rePassword->text()){
        QMessageBox::critical(this,"Error","Password Mismatched");
        ui->password->clear();
        ui->rePassword->clear();
    }
    else{
        DbManager db;
        if(db.makeAnEntry(website,uname,password,comment,key)){
            this->close();

    }
}
}

