#include "logindialog.h"
#include "registerdialog.h"
#include "ui_logindialog.h"

loginDialog::loginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginDialog)
{

    ui->setupUi(this);
    ui->password->setEchoMode(QLineEdit::Password);
}

int loginDialog::getLoginId()
{
    return loginId;
}

int loginDialog::login()
{
    loginId = 1;
    if(1){
        registerDialog rd;
        rd.setModal(true);
        rd.exec();

    }
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_pushButton_clicked()
{
    login();
    close();
}


void loginDialog::on_pushButton_2_clicked()
{
    exit(EXIT_FAILURE);
}

