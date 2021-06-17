#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QString>


class DbManager
{
public:
    DbManager(const QString& path);
    int createNewUser(const int &id, const QString &uname, const QString &pass);
    int validateUser(const QString& uname, const QString& hashPass);
    ~DbManager();

private:
    QString path;
    };

#endif // DBMANAGER_H
