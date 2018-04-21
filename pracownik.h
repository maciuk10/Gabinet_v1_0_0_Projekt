#ifndef PRACOWNIK_H
#define PRACOWNIK_H

#include "osoba.h"
#include <QString>

class Pracownik : public Osoba
{
public:
    explicit Pracownik(QString imie, QString nazwisko, QString identyfikator, QString haslo_MD5);

    QString getImie() const;
    QString getNazwisko() const;

    void setImie(QString imie);
    void setNazwisko(QString nazwisko);

    void wypiszDane();

    void dodaj();
    void usun(int id);
    void modyfikuj();
    void wyszukiwanie(QString nazwa);

private:
    QString identyfikator;
    QString haslo_MD5;
};

#endif // PRACOWNIK_H
