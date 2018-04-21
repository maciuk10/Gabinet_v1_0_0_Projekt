#ifndef OSOBA_H
#define OSOBA_H

#include <QString>

class Osoba
{
public:
    explicit Osoba(QString imie, QString nazwisko);

    //akcesory składowych prywatnych klasy
    virtual QString getImie() = 0;
    virtual QString getNazwisko() = 0;

    virtual void setImie(QString imie) = 0;
    virtual void setNazwisko(QString nazwisko) = 0;

    //metody przesłaniane przez metody klas pochodnych (wirtualne)
    virtual void wypiszDane() = 0;
protected:
    QString imie;
    QString nazwisko;
};

#endif // OSOBA_H
