#include "makeentrydialog.h"
#include "ui_makeentrydialog.h"

makeEntryDialog::makeEntryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::makeEntryDialog)
{
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
    exit(EXIT_SUCCESS);
}

