#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QString>
#include <QTextStream>


class DbManager
{
public:
    DbManager();

    ~DbManager();

    int createMaster(const QString &pass);
    int validate(const QString &hashPass);
    QSqlQueryModel *getModel(const QString& key);
    int makeAnEntry(QString &website, QString &uname, QString &password, QString &comment, QString &key);
    int importEntry(QString &website, QString &uname, QString &password, QString &comment, QString &key);
    int updateEntry(int id, QString &website, QString &uname, QString &password, QString &comment, QString &key);
    int listExport(QTextStream& stream, QString &key);
    int listImport(QString &website, QString &uname, QString &password, QString &comment, QString &key);
    int getEntryDetail(QString &website, QString *uname, QString *password, QString *comment, int *id, QString &key);
    int deleteEntry(QString &website,int &id,QString &key);
private:
    QString path;
    QSqlDatabase db;
    };

#endif // DBMANAGER_H
