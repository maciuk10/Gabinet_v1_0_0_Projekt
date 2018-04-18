#ifndef DATA_H
#define DATA_H

#include <QDateTime>
#include <QString>

class Data
{
private:
    int dzien;
    int miesiac;
    int rok;
public:
    explicit Data(int dzien, int miesiac, int rok);
    QDateTime getData() const;
    void setData();
};

#endif // DATA_H
