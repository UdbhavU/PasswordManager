#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QtSql/QSqlDatabase>



class DbManager
{
public:
    DbManager(const QString& path);
    int createNewUser(const int &id, const QString &uname, const QString &pass);


private:
    QSqlDatabase db;

};

#endif // DBMANAGER_H
