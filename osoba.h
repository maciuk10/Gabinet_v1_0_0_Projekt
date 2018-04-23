#ifndef OSOBA_H
#define OSOBA_H

#include <QString>
#include <QWidget>

class Osoba
{
public:
    explicit Osoba(QString imie, QString nazwisko);

    //akcesory składowych prywatnych klasy
    virtual QString getImie() const = 0;
    virtual QString getNazwisko() const = 0;

    virtual void setImie(QString imie) = 0;
    virtual void setNazwisko(QString nazwisko) = 0;

    //metody przesłaniane przez metody klas pochodnych (wirtualne)
    virtual void wypiszDane(QWidget* widget, QStringList dodatkoweInfo) = 0;
    virtual int dodaj() = 0;
    virtual void usun(int id) = 0;
    virtual void modyfikuj(int identify) = 0;

protected:
    QString imie;
    QString nazwisko;
};

#endif // OSOBA_H
