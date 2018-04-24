#ifndef USLUGA_H
#define USLUGA_H

#include <QString>
#include <QDateTime>

#include "sqlconnect.h"
#include "tablefiller.h"

class Usluga
{
public:
    explicit Usluga(QString nazwa, double cena, QString opis, QString czas);

    //akcesory składowych prywatnych klasy
    QString getNazwa() const;
    double getCena() const;
    QString getOpis() const;
    QString getCzas() const;

    void setNazwa(QString nazwa);
    void setCena(double cena);
    void setOpis(QString opis);
    void setCzas(QString czas);

    //metody zarządzające stanem danych
    void dodaj();
    void usun(int id);
    void modyfikuj(int id);
    static void wyszukiwanie(QString nazwa, QTableView *tabela);
    void pracownicyDlaUslugi(QTableView *table, int usluga);    //wprowadza do formularza pracowników którzy mogą wykonywać daną usługę

private:
    QString nazwa;
    double cena;
    QString opis;
    QString czas;
};

#endif // USLUGA_H
