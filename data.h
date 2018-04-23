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


    QDateTime getData() const;
    QString getDataTekstowa(QString formatDaty) const;
    void setData(QDateTime data);
    void setData(QDate data);
    void setData(int dzien, int miesiac, int rok, int godz, int min, int sek);
    QDateTime dodajCzas(int s);
    int operator -(const Data &d1);
};

#endif // DATA_H
