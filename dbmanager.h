#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QString>


class DbManager
{
public:
    DbManager(const QString& path);
    int createNewUser(const int &id, const QString &uname, const QString &pass);


private:
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

};

#endif // DBMANAGER_H
