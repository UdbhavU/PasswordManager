#include "dbmanager.h"
#include "registerdialog.h"

#include <QFile>
#include <QMessageBox>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
DbManager::DbManager(const QString& path)
{
    this->path = path;

}

int DbManager::createNewUser(const int& id, const QString& uname, const QString& pass)
{
    QFile dbFile(path);
    qDebug()<<QSqlDatabase::drivers();
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","PMGR");
    if(!dbFile.exists()){


        db.setDatabaseName("_"+path);
        db.setUserName(uname);
        db.setPassword(pass);
        if(db.open()){
            db.exec("CREATE TABLE passList(website TEXT,username TEXT,password TEXT)");
            db.commit();
            db.close();
            return 1;


        }

}

    return 0;
}

int DbManager::validateUser(const QString &uname, const QString &hashPass)
{
    QSqlDatabase db;
    if(QSqlDatabase::contains("PMGR")){
        db = QSqlDatabase::database("PMGR");
    }else{
        db = QSqlDatabase::addDatabase("QSQLITE","PMGR");
    }
    db.setUserName(uname);
    db.setPassword(hashPass);
    if(db.open()){
        qDebug()<<"opened";
    }

    return 1;
}

DbManager::~DbManager()
{

}
