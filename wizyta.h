#ifndef WIZYTA_H
#define WIZYTA_H

#include "klient.h"
#include "usluga.h"
#include "pracownik.h"
#include "data.h"
#include <QString>

class Wizyta
{
public:
    explicit Wizyta(Klient *klient, Usluga *usluga, Pracownik *pracownik, Data *rezerwacjaOd, Data *rezerwacjaDo, QString status);

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
