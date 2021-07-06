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
            qry->exec(" PRAGMA key='"+pass+"';"); // this encrypts the database with user specified password
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
    qry->prepare("select website,username,\"**********\",comment from accounts");
    QSqlQueryModel *model = new QSqlQueryModel();

    if(qry->exec()) {
        model->setQuery(*qry);
        model->setHeaderData(2,Qt::Horizontal,"Password");
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
    return 0;
}

int DbManager::makeAnEntry(QString& website,
                           QString& uname,
                           QString& password,
                           QString& comment,
                           QString& key)
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
        return 0;
    }
}
else{
QMessageBox::warning(0,"ERROR","passList.db not found.\nRegister First");
return 0;
    }
}

int DbManager::importEntry(QString &website,
                           QString &uname,
                           QString &password,
                           QString &comment,
                           QString &key)
{
    db.setDatabaseName("passList.db");
    if(db.open()){

    QSqlQuery *qry = new QSqlQuery(db);
   qry->exec("pragma key='"+key+"';");
   qry->exec("select count(*) from accounts where website='"+website+"';");
   qry->next();
   if(qry->value(0).toInt() == 0){


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
        return 0;
    }
}
    }
else{
QMessageBox::warning(0,"ERROR","passList.db not found.\nRegister First");
return 0;
    }
}

int DbManager::updateEntry(int id,
                           QString &website,
                           QString &uname,
                           QString &password,
                           QString &comment,
                           QString &key)
{
    db.setDatabaseName("passList.db");
    if(db.open()){
        qDebug()<<key;
        QSqlQuery *qry = new QSqlQuery(db);
        qry->exec("pragma key='"+key+"';");
        qry->prepare("update accounts set website='"+website+"',username='"+uname+"',password='"+password+"',comment='"+comment+"' where website='"+website+"';");
//        qry->addBindValue(website);
//        qry->addBindValue(uname);
//        qry->addBindValue(password);
//        qry->addBindValue(comment);
//        qry->addBindValue(id);
//        // update
        if(qry->exec())
        {
            QMessageBox::information(0,"Update","Updated Entry");
            db.commit();
            db.close();
            return 1;

        }
        else {
            QMessageBox::critical(0,"Update Failed","Please make sure the data you have entered is correct.\n"
                                                              "Duplicate accounts are not allowed.");
            qDebug() << qry->lastError().text();
        }
}
else{
QMessageBox::warning(0,"ERROR","passList.db not found.\nRegister First");
return 0;
    }
}

int DbManager::listExport(QTextStream &stream,
                          QString& key)
{
    db.setDatabaseName("passList.db");
    if(db.open()){


    QSqlQuery *qry = new QSqlQuery(db);
    qry->exec("pragma key='"+key+"';");
    qry->prepare("select website,username,password,comment from accounts");


    if(qry->exec()) {
        while(qry->next()){
            stream<< qry->value(0).toString()<<",";
            stream<< qry->value(1).toString()<<",";
            stream<< qry->value(2).toString()<<",";
            stream<< qry->value(2).toString()<<"\n";

        }
        return 1;


    } else {
        qDebug() << qry->lastError().text();
        QMessageBox::critical(0,"No Records Found",
                              "There are no records in the database.\n"
                                 "Please save an account into the manager "
                                 "before loading the accounts.",
                              QMessageBox::Ok);
        return 0;
    }



    }else{
        QMessageBox::critical(0,"Missing passList.db",
                              "Try registering first",
                              QMessageBox::Ok);
        return 0;
    }

}

int DbManager::listImport(QString &website,
                          QString &uname,
                          QString &password,
                          QString &comment,
                          QString &key)
{
    QFile dbFile("passList.db");
    if(dbFile.exists())
    {

        importEntry(website,uname,password,comment,key);
    }

}

int DbManager::getEntryDetail(QString &website,
                              QString *uname,
                              QString *password,
                              QString *comment,
                              int *id,
                              QString &key)
{
    db.setDatabaseName("passList.db");
    if(db.open()){


    QSqlQuery *qry = new QSqlQuery(db);
    qry->exec("pragma key='"+key+"';");
    qry->prepare("select * from accounts where website='"+website+"';");


    if(qry->exec()) {
        while(qry->next()){
            qDebug()<<qry->value(4).toString();
            *uname= qry->value(2).toString();
            *password=  qry->value(3).toString();
            *comment =  qry->value(4).toString();
            *id = qry->value(0).toInt();


        }
        return 1;


    } else {
//        qDebug() << qry->lastError().text();
        QMessageBox::critical(0,"No Records Found",qry->lastError().text()
                              ,
                              QMessageBox::Ok);
        return 0;
    }



    }else{
        QMessageBox::critical(0,"Missing passList.db",
                              "Try registering first",
                              QMessageBox::Ok);
        return 0;
    }

}

int DbManager::deleteEntry(QString &website,
                           int &id,
                           QString &key)
{
    db.setDatabaseName("passList.db");
    if(db.open()){


    QSqlQuery *qry = new QSqlQuery(db);
    qry->exec("pragma key='"+key+"';");
    qry->prepare("DELETE from accounts where website='"+website+"';");


    if(qry->exec()) {

    return 1;

    } else {

        QMessageBox::critical(0,"No Records Found",qry->lastError().text()
                              ,
                              QMessageBox::Ok);
        return 0;
    }



    }else{
        QMessageBox::critical(0,"Missing passList.db",
                              "Try registering first",
                              QMessageBox::Ok);
        return 0;
    }
}

DbManager::~DbManager()
{
    db.close();
    db.removeDatabase("PMGR");
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}
