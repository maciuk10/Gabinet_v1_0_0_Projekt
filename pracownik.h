#ifndef PRACOWNIK_H
#define PRACOWNIK_H

#include "osoba.h"
#include <QString>

class Pracownik : public Osoba
{
public:
    explicit Pracownik(QString imie, QString nazwisko, QString identyfikator, QString haslo_MD5);

    //akcesory składowych prywatnych klasy
    QString getImie() const;
    QString getNazwisko() const;

    void setImie(QString imie);
    void setNazwisko(QString nazwisko);

    void wypiszDane();

    //metody zarządzające stanem danych
    void dodaj();
    void usun(int id);
    void modyfikuj();
    void wyszukiwanie(QString nazwa);

private:
    QString identyfikator;
    QString haslo_MD5;
};

#endif // PRACOWNIK_H
