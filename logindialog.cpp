#include "dbmanager.h"
#include "logindialog.h"
#include "registerdialog.h"
#include "ui_logindialog.h"

#include <QCryptographicHash>
#include <QMessageBox>

loginDialog::loginDialog(QWidget *parent,QString *pass) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{

    key = pass;


    ui->setupUi(this);
    this->setWindowTitle("Login");
    ui->password->setEchoMode(QLineEdit::Password);
}

int loginDialog::getLoginStatus()
{
    return loginStatus;
}

int loginDialog::login()
{


    QByteArray pass = ui->password->text().toUtf8();
    DbManager db;
    *key = QString(QCryptographicHash::hash(pass,QCryptographicHash::RealSha3_512));
    loginStatus = db.validate(*key);
    if(loginStatus == 0){
        QMessageBox mb;
        mb.setWindowTitle("ERROR");
        mb.setText("Failed to log in");
        mb.exec();
    }
    return loginStatus;
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





