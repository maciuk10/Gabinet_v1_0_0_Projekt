#ifndef KLIENT_H
#define KLIENT_H

#include "osoba.h"
#include <QString>

class Klient : public Osoba
{
public:
    explicit Klient(QString imie, QString nazwisko, QString email, QString telefon, QString ulica, QString numerUlicy, QString kodPocztowy, QString miasto);

    QString getImie() const override;
    QString getNazwisko() const override;
    QString getEmail() const;
    QString getTelefon() const;
    QString getUlica() const;
    QString getNumerUlicy() const;
    QString getKodPocztowy() const;
    QString getMiasto() const;

    void setImie(QString imie);
    void setNazwisko(QString nazwisko);
    void setEmail(QString email);
    void setTelefon(QString telefon);
    void setUlica(QString ulica);
    void setNumerUlicy(QString numerUlicy);
    void setKodPocztowy(QString kodPocztowy);
    void setMiasto(QString miasto);

    void dodaj();
    void usun(int id);
    void modyfikuj();
    void wyszukiwanie(QString nazwa);

private:
    QString email;
    QString telefon;
    QString ulica;
    QString numerUlicy;
    QString kodPocztowy;
    QString miasto;
};

#endif // KLIENT_H
