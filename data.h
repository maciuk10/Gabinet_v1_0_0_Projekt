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
    QDateTime getData() const;
    QString getDataTekstowa(QString formatDaty) const;
    void setData(QDateTime data);
    void setData(int dzien, int miesiac, int rok, int godz, int min, int sek);
    QDateTime dodajCzas(int s);
};

#endif // DATA_H
