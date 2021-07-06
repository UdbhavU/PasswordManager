#include "dbmanager.h"
#include "makeentrydialog.h"
#include "registerdialog.h"
#include "ui_registerdialog.h"
#include<QDebug>
#include <QCryptographicHash>
#include <QMessageBox>

registerDialog::registerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerDialog)
{
    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);
    ui->rPassword->setEchoMode(QLineEdit::Password);
}

registerDialog::~registerDialog()
{
    delete ui;
}

void registerDialog::on_pushButton_2_clicked()
{

//    makeEntryDialog me;
//    me.setModal(true);
//    me.exec();

    QByteArray pass = ui->password->text().toUtf8();
    QByteArray rPass = ui->rPassword->text().toUtf8();
    int passValid = 0;
    if(pass != rPass){
        QMessageBox mb;
        mb.setIcon(QMessageBox::Critical);
        mb.setText("Password mismatched");
        mb.exec();
    }
    else{
        for(auto i: ui->password->text()){
            if(i.isDigit()) passValid |=1;
            if(i.isLower()) passValid |=2;
            if(i.isUpper()) passValid |=4;

       }
        qDebug()<<passValid<<"|"<<ui->password->text().size();
        if(ui->password->text().size()>8 && passValid == 7){
        QString hashpass =QString(QCryptographicHash::hash(pass,QCryptographicHash::RealSha3_512));

        DbManager *db = new DbManager();
        if(db->createMaster(hashpass)){
            delete db;
            close();
        }
        }
        else{
            QMessageBox mb;
            mb.setIcon(QMessageBox::Critical);
            mb.setText("Enter a strong Password.\n Password should contain atleast \n 1 Upper Case\n 1 Lower Case \n 1 Number \n and should have more than 7 characters ");
            mb.exec();
        }

    }

}

