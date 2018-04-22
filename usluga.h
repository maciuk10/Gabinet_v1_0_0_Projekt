#ifndef USLUGA_H
#define USLUGA_H

#include <QString>
#include <QDateTime>

#include "sqlconnect.h"
#include "tablefiller.h"

class Usluga
{
public:
    explicit Usluga(QString nazwa, double cena, QString opis, QDateTime czas);

    //akcesory składowych prywatnych klasy
    QString getNazwa() const;
    double getCena() const;
    QString getOpis() const;
    QDateTime getCzas() const;

    void setNazwa(QString nazwa);
    void setCena(double cena);
    void setOpis(QString opis);
    void setCzas(QDateTime czas);

    //metody zarządzające stanem danych
    void dodaj();
    void usun(int id);
    void modyfikuj();
    static void wyszukiwanie(QString nazwa, QTableView *tabela);

private:
    QString nazwa;
    double cena;
    QString opis;
    QDateTime czas;
};

#endif // USLUGA_H
