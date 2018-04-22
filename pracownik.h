#ifndef PRACOWNIK_H
#define PRACOWNIK_H

#include <Qt>
#include <QApplication>
#include <QString>
#include <QGroupBox>
#include <QLineEdit>

#include "osoba.h"
#include "sqlconnect.h"
#include "tablefiller.h"

class Pracownik : public Osoba
{
public:
    explicit Pracownik(QString imie, QString nazwisko, QString identyfikator);

    //akcesory składowych prywatnych klasy
    QString getImie() const override;
    QString getNazwisko() const override;
    QString getIdentyfikator() const;

    void setImie(QString imie) override;
    void setNazwisko(QString nazwisko) override;
    void setIdentyfikator(QString identyfikator);

    void wypiszDane(QWidget *widget) override;
    static QStringList pokazInfo(int user);

    //metody zarządzające stanem danych
    int dodaj() override;
    void usun(int id) override;
    void modyfikuj(int identify) override;
    static void wyszukiwanie(QString nazwa, QTableView *tabela);

    void mojeUslugi();
    void pokazGodzinyPracy(QGroupBox *gb);

private:
    QString identyfikator;
};

#endif // PRACOWNIK_H
