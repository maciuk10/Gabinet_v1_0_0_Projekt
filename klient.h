#ifndef KLIENT_H
#define KLIENT_H

#include "osoba.h"
#include "sqlconnect.h"
#include "tablefiller.h"
#include <QString>
#include <QTableView>
#include <QLineEdit>

class Klient : public Osoba
{
public:
    explicit Klient(QString imie, QString nazwisko, QString email, QString telefon, QString ulica, QString numerUlicy, QString kodPocztowy, QString miasto);

    //akcesory składowych prywatnych klasy
    QString getImie() const override;
    QString getNazwisko() const override;
    QString getEmail() const;
    QString getTelefon() const;
    QString getUlica() const;
    QString getNumerUlicy() const;
    QString getKodPocztowy() const;
    QString getMiasto() const;

    void setImie(QString imie) override;
    void setNazwisko(QString nazwisko) override;
    void setEmail(QString email);
    void setTelefon(QString telefon);
    void setUlica(QString ulica);
    void setNumerUlicy(QString numerUlicy);
    void setKodPocztowy(QString kodPocztowy);
    void setMiasto(QString miasto);

    //metody zarządzające stanem danych
    void wypiszDane(QWidget *widget, QStringList dodatkoweInfo) override;
    int dodaj() override;
    void usun(int id) override;
    void modyfikuj(int identify) override;
    static void wyszukiwanie(QString nazwa, QTableView *tabela);

private:
    QString email;
    QString telefon;
    QString ulica;
    QString numerUlicy;
    QString kodPocztowy;
    QString miasto;
};

#endif // KLIENT_H
