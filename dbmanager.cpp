#include "dbmanager.h"
#include "registerdialog.h"
#include <QFile>
#include <QMessageBox>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
DbManager::DbManager()
{

    if(QSqlDatabase::contains("PMGR")){
        db = QSqlDatabase::database("PMGR");
    }else{
        db = QSqlDatabase::addDatabase("QSQLCIPHER","PMGR");
    }

}

int DbManager::createMaster(const QString& pass)
{
    QFile dbFile("passList.db");
    qDebug()<<QSqlDatabase::drivers();

    if(!dbFile.exists()){
        db.setDatabaseName("passList.db");
        if(!db.open())


            QMessageBox::critical(0,"ERROR","Failed to open passList.db");

        else{
            QSqlQuery *qry = new QSqlQuery(db);
            qry->exec("PRAGMA key='"+pass+"';"); // this encrypts the database with user specified password
            qry->exec("CREATE TABLE accounts (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
                     "website TEXT, username varchar(30), password TEXT, comment varchar(50));");

            db.close();

            return 1;
        }

}
//}

    return 0;
}

int DbManager::validate(const QString &hashPass)
{
    QFile dbFile("passList.db");
    qDebug()<<QSqlDatabase::drivers();

    if(dbFile.exists()){
    db.setDatabaseName("passList.db");
    if(db.open()){
        qDebug()<<"ioio";
            QSqlQuery *qry = new QSqlQuery(db);
            qry->exec("PRAGMA key='"+hashPass+"';");
            qry->exec("SELECT count(*) FROM sqlite_master WHERE type='table' AND name='accounts';");
            qry->first();
            if(qry->value(0).toInt()==1){
                qDebug()<<"Logged in";
                db.close();
                return 1;
            }else{
            QMessageBox::warning(0,"ERROR","Wrong Password");
    }}
}else{
        QMessageBox::warning(0,"ERROR","Register First");

}
    return 0;
}

QSqlQueryModel* DbManager::getModel(const QString& key)
{
    db.setDatabaseName("passList.db");
    if(db.open()){


    QSqlQuery *qry = new QSqlQuery(db);
    qry->exec("pragma key='"+key+"';");
    qry->prepare("select website,username,password,comment from accounts");
    QSqlQueryModel *model = new QSqlQueryModel();

    if(qry->exec()) {
        model->setQuery(*qry);
        return model;


    } else {
        qDebug() << qry->lastError().text();
        QMessageBox::critical(0,"No Records Found",
                              "There are no records in the database.\n"
                                 "Please save an account into the manager "
                                 "before loading the accounts.",
                              QMessageBox::Ok);
        return 0;
    }

    return model;

    }
}

int DbManager::makeAnEntry(QString& website, QString& uname, QString& password,QString& comment,QString& key)
{
    db.setDatabaseName("passList.db");
    if(db.open()){

    QSqlQuery *qry = new QSqlQuery(db);
    qry->exec("pragma key='"+key+"';");
    qry->prepare("insert into accounts (website,username,password,comment)"
                " values('"+website+"','"+uname+"','"+password+"','"+comment+"');");


    if(qry->exec())
    {
        QMessageBox::information(0,"Save","saved entry to passList.db");
        db.commit();
        return 1;

    }
    else {
        QMessageBox::critical(0,"Save Failed","Duplicate data entered");
        qDebug() << qry->lastError().text();
    }
}
else{
QMessageBox::warning(0,"ERROR","passList.db not found.\nRegister First");
}
}
DbManager::~DbManager()
{
    db.close();
    db.removeDatabase("PMGR");
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}
