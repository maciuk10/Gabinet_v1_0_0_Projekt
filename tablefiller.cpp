#include "tablefiller.h"

TableFiller::TableFiller(QSqlDatabase db, QTableView *tableView, QString sqlCommand) : db(db), sqlCommand(sqlCommand), countOfRows(0) {
    this->table = tableView;
    this->query = new QSqlQuery(db);
}

TableFiller::TableFiller(QSqlDatabase db, QString sqlCommand): db(db), sqlCommand(sqlCommand), countOfRows(0) {
    this->table = nullptr;
    this->query = new QSqlQuery(db);
}

void TableFiller::fillTheTable() {
    model = new QSqlQueryModel();
    query->prepare(sqlCommand);
    query->exec();
    this->countOfRows = query->size();
    model->setQuery(*query);
    table->setModel(model);
    delete query;
}

bool TableFiller::executeInsertUpdateDelete(){
    if(db.open()){
        query->prepare(sqlCommand);
        if(!query->exec()){
            qDebug() << query->lastError().text();
            qDebug() << query->lastError().driverText();
            qDebug() << query->lastError().databaseText();
            return false;
        }else {
            return true;
        }
    }
}

void TableFiller::executeSelect(){

}

void TableFiller::setcountOfRows(int value) {
    countOfRows = value;
}

QSqlQueryModel* TableFiller::getSqlQueryModelObject() const
{
    return this->model;
}

int TableFiller::getcountOfRows() {
    query->prepare(sqlCommand);
    query->exec();
    setcountOfRows(query->size());
    return this->countOfRows;
}
