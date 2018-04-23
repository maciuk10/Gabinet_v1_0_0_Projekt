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
    QString getMD5() const;

    void setImie(QString imie) override;
    void setNazwisko(QString nazwisko) override;
    void setIdentyfikator(QString identyfikator);
    void setMD5(QString md5);

    void wypiszDane(QWidget *widget) override;
    static QStringList pokazInfo(int user);
    void wypiszDoFormularza(QGroupBox *gb, QStringList data);

    //metody zarządzające stanem danych
    int dodaj() override;
    void usun(int id) override;
    void modyfikuj(int identify) override;
    static void wyszukiwanie(QString nazwa, QTableView *tabela);

    QStringList mojeUslugi(int user);
    void mojeUslugi(QTableView *table, int user);
    void pokazGodzinyPracy(QGroupBox *gb);
    void poszerzKompetencje(int user, int usluga);
    void redukujKompetencje(int user, int usluga);
    QStringList mojeGodzinyPracyWDanymDniu(QString dzien, int user);

    void aktualizujHaslo(QString noweHaslo, int user);

private:
    QString identyfikator;
    QString md5;
};

#endif // PRACOWNIK_H
