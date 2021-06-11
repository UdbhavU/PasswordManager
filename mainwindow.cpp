#include "logindialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    while(sessionID==-1){
        loginDialog ld;
        ld.setModal(true);
        ld.exec();
        sessionID = ld.getLoginId();
    }
}

void MainWindow::setSession(int id)
{
    sessionID = id;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionExit_triggered()
{
    exit(EXIT_SUCCESS);
}

