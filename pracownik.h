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

    void wypiszDane(QWidget *widget, QStringList dodatkoweInfo) override; //nadpisuje metodę wirtualną z klasy osoba po której dziedziczy
    static QStringList pokazInfo(int user); //zwraca wszystkie dane pracownika
    void wypiszDoFormularza(QGroupBox *gb, QStringList data); //wprowadza do formularza dane pracownika

    //metody zarządzające stanem danych
    int dodaj() override;
    void usun(int id) override;
    void modyfikuj(int identify) override;
    static void wyszukiwanie(QString nazwa, QTableView *tabela);

    QStringList mojeUslugi(int user);               //zwraca usługi wykonywane przez danego pracownika
    void mojeUslugi(QTableView *table, int user);   //wprowadza do formularza usługi pracownika
    void pokazGodzinyPracy(QGroupBox *gb);          //wyswietla godziny pracy w formularzu godzin
    void poszerzKompetencje(int user, int usluga);  //dodaje usługi które może wykonywać pracownik
    void redukujKompetencje(int user, int usluga);  //usuwa usługi z dozwolonych dla użytkownika
    QStringList mojeGodzinyPracyWDanymDniu(QString dzien, int user);    //zwraca godziny pracy pracownika dla konkretnego dnia

    void aktualizujHaslo(QString noweHaslo, int user); //aktualizuje haslo pracownika

private:
    QString identyfikator;
    QString md5;
};

#endif // PRACOWNIK_H
