#ifndef SQLCONNECT_H
#define SQLCONNECT_H

#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QString>
#include <Qt>
#include <QMessageBox>


class SqlConnect
{
private:
    QSqlDatabase db;
    QString hostname = "localhost";
    QString databaseName;
    QString username;
    QString password;
    int port = 3306;

public:
    explicit SqlConnect(QString host, QString db, QString user, QString password, int port);
    explicit SqlConnect(QString host, QString db, QString user, QString password);
    explicit SqlConnect(QString db, QString user, QString password);
    ~SqlConnect();

    void OpenConnection();
    void CloseConnection();

    QSqlDatabase getSqlDatabaseObject() const;
    QString getHostname() const;
    QString getDatabaseName() const;
    QString getUsername() const;
    QString getPassword() const;
    int getPort() const;

    void setSqlDatabaseObject(QSqlDatabase db);
    void setHostname(QString hostname);
    void setUsername(QString username);
    void setPassword(QString password);
    void setPort(int port);

};

#endif // SQLCONNECT_H
