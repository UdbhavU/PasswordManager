#include "dbmanager.h"
#include "logindialog.h"
#include "registerdialog.h"
#include "ui_logindialog.h"

#include <QCryptographicHash>
#include <QMessageBox>

loginDialog::loginDialog(QWidget *parent,QString *uname, QString *pass) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{
    username = uname;
    key = pass;


    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);
}

int loginDialog::getLoginId()
{
    return loginId;
}

int loginDialog::login()
{

    *username = ui->uname->text();
    QByteArray pass = ui->password->text().toUtf8();
    DbManager db(QString(*username+".db"));
    *key = QString(QCryptographicHash::hash(pass,QCryptographicHash::Sha3_512));
    loginId = db.validateUser(*username,*key);
    if(loginId == -1){
        QMessageBox mb;
        mb.setWindowTitle("ERROR");
        mb.setText("Failed to log in");
        mb.exec();
    }
    return loginId;
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_pushButton_clicked()
{
   int res = login();
    if(res == -1){
        login();
    }else{
        close();
    }
}


void loginDialog::on_pushButton_2_clicked()
{
    exit(EXIT_FAILURE);
}




void loginDialog::on_commandLinkButton_clicked()
{
    registerDialog rd;
    rd.setModal(true);
    rd.exec();

}

