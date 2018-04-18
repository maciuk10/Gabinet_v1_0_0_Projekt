#ifndef OSOBA_H
#define OSOBA_H

#include <QString>

class Osoba
{
public:
    explicit Osoba(QString imie, QString nazwisko);

    virtual QString getImie() = 0;
    virtual QString getNazwisko() = 0;

    virtual void setImie(QString imie);
    virtual void setNazwisko(QString nazwisko) = 0;

    virtual void wypiszDane() = 0;
protected:
    QString imie;
    QString nazwisko;
};

#endif // OSOBA_H
