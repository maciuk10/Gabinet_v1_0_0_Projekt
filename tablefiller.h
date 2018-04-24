#ifndef TABLEFILLER_H
#define TABLEFILLER_H

#include <QtSql>
#include <QTableView>
#include <QSqlQuery>
#include <QSqlQueryModel>

class TableFiller
{
public:
    explicit TableFiller(QSqlDatabase db, QTableView* tableView, QString sqlCommand); // konstruktor który inicjalizuje obiekty potrzebna do wykonania operacji na danych
    explicit TableFiller(QSqlDatabase db, QString sqlCommand); //przeciążony konstruktor służący do wykonywania zapytań o dane
    void fillTheTable(); //metoda służąca do wypełnienia tabeli przekazanej w konstruktorze
    int getcountOfRows(); // zwraca ilość wierszy zbioru danych
    void setcountOfRows(int value); // ustawia ilość wierszy zbioru danych
    bool executeInsertUpdateDelete(); // modyfikuje dane i zwraca status poprawności operacji
    QStringList executeSelect(); // zwraca zbiór danych dla konkretnych warunków
    QSqlQueryModel* getSqlQueryModelObject() const; // zwraa model dla tabeli

private:
    QSqlDatabase db;
    QTableView *table;
    QString sqlCommand;
    QSqlQuery *query;
    QSqlQueryModel *model;
    int countOfRows;
};

#endif // TABLEFILLER_H
