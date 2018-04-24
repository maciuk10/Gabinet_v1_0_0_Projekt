#ifndef DATA_H
#define DATA_H

#include <QDateTime>
#include <QString>
#include <QDebug>

class Data
{
private:
    int dzien;
    int miesiac;
    int rok;
    int godz;
    int min;
    int sek;
public:
    explicit Data();

    //akcesory właściwości prywatnych (get/set)
    int getDzien() const;
    int getMiesiac() const;
    int getRok() const;
    int getGodz() const;
    int getMin() const;
    int getSek() const;

    void setDzien(int dzien);
    void setMiesiac(int miesiac);
    void setRok(int rok);
    void setGodz(int godz);
    void setMin(int min);
    void setSek(int sek);


    QDateTime getData() const;                              //zwraca datę jako typ QDateTime
    QString getDataTekstowa(QString formatDaty) const;      //zwraca datę w postaci tekstu zgodnego z formatowaniem
    void setData(QDateTime data);                           //ustawia datę przekazaną jako QDateTime
    void setData(QDate data);                               //ustawia datę przekazaną jako QDate
    void setData(int dzien, int miesiac, int rok, int godz, int min, int sek);  //ustawia datę przekazaną jako kolejne liczby
    QDateTime dodajCzas(int s);                             //zwiększa datę o określoną liczbę sekund
    int operator -(const Data &d1);                         //zwraca liczbę sekund pomiędzy datami z tego samego dnia
};

#endif // DATA_H
