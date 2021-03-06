#include "dbmanager.h"
#include "logindialog.h"
#include "mainwindow.h"
#include "registerdialog.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMap>
#include <QPair>
#include <QDebug>
#include <QLabel>
#include <QTableView>
#include <QTextStream>
#include <QMessageBox>
#include "makeentrydialog.h"
#include "viewentrydialog.h"

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
           //the below loop will persist the login window till the the correct password is entered; exit can be done only through the close button in the dialog
        while(sessionId !=1){

            loginDialog ld(this,&key);
            ld.setModal(true);
            ld.exec();
            sessionId = ld.getLoginStatus();


    }
    QLabel *status = new QLabel;
    if(sessionId == 1) status->setText("Logged");
    statusBar()->addPermanentWidget(status);
    //fill the table with the passList content
    fillTable();

}
//method that fills the table with the password list from the database
void MainWindow::fillTable()
{
    DbManager db;
    auto model = db.getModel(key);
    ui->tblView->setModel(model);
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


void MainWindow::on_actionImport_triggered()
{
    QString fname = QFileDialog::getOpenFileName();
    QFile file(fname);
    QString website ;
    QString pass;
    QString username;
    QString comment;
    DbManager db;
    QMap<QString,QPair<QString,QString>> entry;
    QFile tmp("tmp.csv");
    //verify if the file is successfulled opened or not
    if(file.open(QFile::ReadOnly | QFile::Text)){
        //---------------------------
        if(tmp.open(QFile::Append | QFile::Text)){
            QTextStream fstr(&tmp);
            //method used for dumping the data to a text stream
            if(db.listExport(fstr,key)){
                statusBar()->showMessage("Importing "+fname+" .............",5000);
            }
            fstr.flush();
            tmp.close();
        }
        if(tmp.open(QFile::Append | QFile::Text)){
            while (!tmp.atEnd()) {
                QByteArray line = tmp.readLine();
                website = line.split(',').at(0);
                username = line.split(',').at(1);
                pass = line.split(',').at(2);
                entry[website]=qMakePair(username,pass);
            }
            tmp.close();
            QFile::remove("tmp.csv");
        }
        while (!file.atEnd()) {
               QByteArray line = file.readLine();
               website = line.split(',').at(0);
               username = line.split(',').at(1);
               pass = line.split(',').at(2);
               comment = line.split(',').at(3);
               if(entry[website].first==username){
                   continue;
               }
               else{
                   db.listImport(website,username,pass,comment,key);
                   statusBar()->showMessage("Imported "+website, 1000);
               }
        }
           statusBar()->showMessage("Imported successfully", 5000);
           fillTable();

    }
    else{
        statusBar()->showMessage("Failed to import", 5000);
    }
}

//method to handle clicks on table content
void MainWindow::on_tblView_clicked(const QModelIndex &index)
{
    QString val = ui->tblView->model()->index(index.row(),0,QModelIndex()).data().toString();// get the website
    QString uname,password,comment;
    int id;
    DbManager db;
    db.getEntryDetail(val,&uname,&password,&comment,&id,key);
    viewEntryDialog vd(this,id,val,uname,password,comment,key);
    vd.setModal(true);
    vd.exec();
    fillTable();
}
void MainWindow::on_actionRefresh_triggered()
{
    fillTable();
}

//help tab actions
void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}
void MainWindow::on_actionAbout_Password_Manager_triggered()
{
    QMessageBox::about(this,"About Password Manager","Developed by\nUdbhav U\nThushar Kulal");
}


MainWindow::~MainWindow()
{
    delete ui;
}
