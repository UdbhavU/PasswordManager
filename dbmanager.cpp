#include "dbmanager.h"
#include "registerdialog.h"

#include <QFile>
#include <QMessageBox>
#include <QtSql/QSqlQuery>

DbManager::DbManager(const QString& path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

}

int DbManager::createNewUser(const int& id, const QString& uname, const QString& pass)
{
 int qstat = 0;
 QSqlQuery query(db);
 QString createQ = "CREATE TABLE user(uid integer primary key,uname text,password text);";
 qstat = query.exec(createQ);
 if(qstat){

     query.prepare("INSERT into user(:uid,:uname,:password)");
     query.bindValue(":uid",id);
     query.bindValue(":uname",uname);
     query.bindValue(":password",pass);
     qstat = query.exec();
     if(!qstat){
         QMessageBox mg;
         mg.setText("Failed to create new user");
         mg.setWindowTitle("ERROR");
         mg.exec();
     }
 }
 query.finish();
 return qstat;
}
