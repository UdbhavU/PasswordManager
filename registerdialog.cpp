#include "dbmanager.h"
#include "makeentrydialog.h"
#include "registerdialog.h"
#include "ui_registerdialog.h"

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
    QString uname = ui->uname->text();
    QByteArray pass = ui->password->text().toUtf8();
    QByteArray rPass = ui->rPassword->text().toUtf8();
    if(pass != rPass){
        QMessageBox mb;
        mb.setText("Password mismatched");
        mb.exec();
    }
    else{
        QString hashpass =QString(QCryptographicHash::hash(pass,QCryptographicHash::RealSha3_512));

        DbManager db(QString(uname+".db"));
        if(db.createNewUser(1,uname,hashpass)){
            close();
        }

    }

}

