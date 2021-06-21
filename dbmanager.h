#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QString>


class DbManager
{
public:
    DbManager();

    ~DbManager();

    int createMaster(const QString &pass);
    int validate(const QString &hashPass);
private:
    QString path;
    QSqlDatabase db;
    };

#endif // DBMANAGER_H
