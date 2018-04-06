#ifndef TABLEFILLER_H
#define TABLEFILLER_H

#include <QtSql>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlQueryModel>

class TableFiller
{
public:
    explicit TableFiller(QSqlDatabase db, QTableView* tableView, QString sqlCommand);
    explicit TableFiller(QSqlDatabase db, QString sqlCommand);
    void fillTheTable();
    int getcountOfRows();
    void setcountOfRows(int value);
    bool executeInsertUpdateDelete();
    void executeSelect();
    QSqlQueryModel* getSqlQueryModelObject() const;

private:
    QSqlDatabase db;
    QTableView *table;
    QString sqlCommand;
    QSqlQuery *query;
    QSqlQueryModel *model;
    int countOfRows;
};

#endif // TABLEFILLER_H
