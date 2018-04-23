#include "data.h"

Data::Data() {}

QDateTime Data::getData() const {
    return QDateTime(QDate(rok, miesiac, dzien), QTime(godz, min, sek));
}

QString Data::getDataTekstowa(QString formatDaty) const {
    QDateTime data = this->getData();
    return data.toString(formatDaty);
}

void Data::setData(QDateTime data) {
    this->rok = data.date().year();
    this->miesiac = data.date().month();
    this->dzien = data.date().day();
    this->godz = data.time().hour();
    this->min = data.time().minute();
    this->sek = data.time().second();
}

void Data::setData(int dzien, int miesiac, int rok, int godz, int min, int sek) {
    this->dzien = dzien;
    this->miesiac = miesiac;
    this->rok = rok;
    this->godz = godz;
    this->min = min;
    this->sek = sek;
}

QDateTime Data::dodajCzas(int s) {
    QDateTime data = this->getData();
    return data.addSecs(s);
}

int operator -(const Data &d1, const Data &d2){

}
