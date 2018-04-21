#ifndef WIZYTA_H
#define WIZYTA_H

#include <QString>

#include "klient.h"
#include "usluga.h"
#include "pracownik.h"
#include "data.h"

class Wizyta
{
public:
    explicit Wizyta(Klient *klient, Usluga *usluga, Pracownik *pracownik, Data *rezerwacjaOd, Data *rezerwacjaDo, QString status);

    //akcesory składowych prywatnych klasy
    Klient* getKlient() const;
    Usluga* getUsluga() const;
    Pracownik* getPracownik() const;
    Data* getRezerwacjaOd() const;
    Data* getRezerwacjaDo() const;
    QString getStatus() const;

    void setKlient(Klient *klient);
    void setUsluga(Usluga *usluga);
    void setPracownik(Pracownik *pracownik);
    void setRezerwacjaOd(Data *rezerwacjaOd);
    void setRezerwacjaDo(Data *rezerwacjaDo);
    void setStatus(QString status);

    //metody zarządzające stanem danych
    void dodaj();
    void usun(int id);
    void modyfikuj();
    void wyszukiwanie(QString nazwa);

private:
    Data *rezerwacjaOd;
    Data *rezerwacjaDo;
    Klient *klient;
    Usluga *usluga;
    Pracownik *pracownik;
    QString status;
};

#endif // WIZYTA_H
