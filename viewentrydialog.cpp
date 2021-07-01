#include "viewentrydialog.h"
#include "ui_viewentrydialog.h"
#include "editdialog.h"

#include <QClipboard>
#include <QThread>

viewEntryDialog::viewEntryDialog(QWidget *parent, int id, QString website, QString uname, QString password, QString comment, QString keyX) :
    QDialog(parent),
    ui(new Ui::viewEntryDialog)
{
    key = keyX;
    Pass = password;
    this->uname = uname;
    ed = new editDialog(this,id, website, uname, password, comment,key);
    ui->setupUi(this);
    ui->website->setText(website);
    ui->uname->setText(uname);
    ui->password->setText(password);
    ui->comment->setText(comment);
}

viewEntryDialog::~viewEntryDialog()
{
    delete ui;
}

void viewEntryDialog::on_editBtn_clicked()
{
    ed->setModal(true);
    this->hide();
    ed->exec();
}


void viewEntryDialog::on_cpyPass_clicked()
{
    QClipboard* clipboard = QApplication::clipboard();

    clipboard->setText(Pass, QClipboard::Clipboard);

    if (clipboard->supportsSelection()) {
        clipboard->setText(Pass, QClipboard::Selection);
    }

    #if defined(Q_OS_LINUX)
        QThread::msleep(1); //workaround for copied text not being available...

    #endif
}


void viewEntryDialog::on_cpyUname_clicked()
{
    QClipboard* clipboard = QApplication::clipboard();

    clipboard->setText(uname, QClipboard::Clipboard);

    if (clipboard->supportsSelection()) {
        clipboard->setText(uname, QClipboard::Selection);
    }

    #if defined(Q_OS_LINUX)
        QThread::msleep(1); //workaround for copied text not being available...

    #endif

}

