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
            return false;
        }else {
            return true;
        }
    }
}

QStringList TableFiller::executeSelect(){
    QStringList elements;
    if(!query->exec(sqlCommand)){
    }else {
        while(query->next()){
            for(int i = 0; i < query->record().count(); i++){
                elements.append(query->value(i).toString());
            }
        }
    }
    return elements;
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
