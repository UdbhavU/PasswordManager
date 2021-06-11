#include "dbmanager.h"
#include "registerdialog.h"

#include <QFile>
#include <QMessageBox>
#include <QSqlQuery>
#include <QVariant>
DbManager::DbManager(const QString& path)
{
    db.setDatabaseName(path);
}

int DbManager::createNewUser(const int& id, const QString& uname, const QString& pass)
{
    QSqlQuery query(db);
    int qstat = 0;
    if(!qstat){

     if(!qstat){
         QMessageBox mg;
         mg.setText("Failed to create new user");
         mg.setWindowTitle("ERROR");
         mg.exec();
     }
 }
// query.finish();
 return qstat;
}
