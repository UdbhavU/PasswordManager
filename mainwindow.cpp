#include "dbmanager.h"
#include "logindialog.h"
#include "mainwindow.h"
#include "registerdialog.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QLabel>
#include <QTableView>
#include <QTextStream>
#include "makeentrydialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Password Manager");

    //this file is where all the accounts will be stored; this is encrypted
    QFile dbFile("passList.db");

   //checks if the file with accounts exists or not; if it exists then the user has registered with master password else prompt to register new account
    if(!dbFile.exists()){
        //creating a instance of register dialog and prompting it as a modal for user to register new user
        registerDialog rd;
        rd.setModal(true);
        rd.exec();
    }
    else
    {
        //the below loop will persist the login window till the the correct password is entered; exit can be done only through the close button in the dialog
        while(sessionId !=1){

            loginDialog ld(this,&key);
            ld.setModal(true);
            ld.exec();
            sessionId = ld.getLoginStatus();

        }
    }
    QLabel *status = new QLabel;
    if(sessionId == 1) status->setText("Logged");
    statusBar()->addPermanentWidget(status);
    //fill the table with the passList content
    fillTable();

}

void MainWindow::fillTable()
{
    DbManager db;
    auto model = db.getModel(key);
    ui->tblView->setModel(model);



}


MainWindow::~MainWindow()
{
    delete ui;
}

//the exit button in the toolbar
void MainWindow::on_actionExit_triggered()
{
    exit(EXIT_SUCCESS);
}

//the export button on the toolbar
void MainWindow::on_actionExport_triggered()
{
    //get the name of the csv file you want to dump the data to
    QString fname = QFileDialog::getSaveFileName();
    QFile file(fname);
    //verify if the file is successfulled opened or not
    if(file.open(QFile::Append | QFile::Text)){

        QTextStream fstr(&file);
        DbManager db;
        //method used for dumping the data to a text stream
        if(db.listExport(fstr,key)){
            statusBar()->showMessage("Dumped data to "+fname,5000);
        }

        fstr.flush();


    file.close();
    }

}


void MainWindow::on_actionMake_new_entry_triggered()
{
    makeEntryDialog ob(this,key);
    ob.setModal(true);
    ob.exec();
    fillTable();
}

