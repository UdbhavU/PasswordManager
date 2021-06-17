#include "logindialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    while(sessionId==-1){
        loginDialog ld(this,&userName,&key);
        ld.setModal(true);
        ld.exec();
        sessionId = ld.getLoginId();
    }
    QLabel *user = new QLabel;
    user->setText(userName);
    statusBar()->addPermanentWidget(user);
}

void MainWindow::setSession(QString& uname,QString& key)
{


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionExit_triggered()
{
    exit(EXIT_SUCCESS);
}


void MainWindow::on_actionExport_triggered()
{
    QString fname = QFileDialog::getSaveFileName();
    QFile file(fname);
    if(file.open(QFile::Append | QFile::Text))
        statusBar()->showMessage(fname+"|opened",5000);
    file.close();

}

