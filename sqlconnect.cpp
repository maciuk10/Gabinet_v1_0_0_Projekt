#include "sqlconnect.h"

SqlConnect::SqlConnect(QString host, QString db, QString user, QString pass, int port): hostname(host), databaseName(db), username(user), password(pass), port(port)
{}

SqlConnect::SqlConnect(QString host, QString db, QString user, QString pass): hostname(host), databaseName(db), username(user), password(pass)
{}

SqlConnect::SqlConnect(QString db, QString user, QString pass): databaseName(db), username(user), password(pass)
{}


void SqlConnect::OpenConnection() {
    QStringList initializedDrivers = QSqlDatabase::connectionNames();
    bool isDefault = initializedDrivers.contains("DefaultConnection");
    if(isDefault){
        db = QSqlDatabase::database("DefaultConnection");
    }else {
        db = QSqlDatabase::addDatabase("QMYSQL","DefaultConnection");
        db.setHostName(hostname);
        db.setDatabaseName(databaseName);
        db.setUserName(username);
        db.setPassword(password);
        db.setPort(port);
    }
    if(!db.open()){
        QMessageBox::warning(nullptr, "Błąd połączenia", "Nie połączono z bazą danych", QMessageBox::Ok);
    }
}

void SqlConnect::CloseConnection() {
    if(db.open()){
        db.close();
    }
}

QSqlDatabase SqlConnect::getSqlDatabaseObject() const
{
    return db;
}

QString SqlConnect::getHostname() const {
    return hostname;
}

QString SqlConnect::getDatabaseName() const {
    return databaseName;
}

QString SqlConnect::getPassword() const {
    return password;
}

int SqlConnect::getPort() const {
    return port;
}

QString SqlConnect::getUsername() const {
    return username;
}

void SqlConnect::setSqlDatabaseObject(QSqlDatabase db) {
    this->db = db;
}

void SqlConnect::setHostname(QString hostname) {
    this->hostname = hostname;
}

void SqlConnect::setUsername(QString username) {
    this->username = username;
}

void SqlConnect::setPassword(QString password) {
    this->password = password;
}

void SqlConnect::setPort(int port) {
    this->port = port;
}

SqlConnect::~SqlConnect(){
}
