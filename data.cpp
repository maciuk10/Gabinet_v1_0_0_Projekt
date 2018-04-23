#include "data.h"

Data::Data() {}

int Data::getDzien() const {
    return dzien;
}

int Data::getMiesiac() const {
    return miesiac;
}

int Data::getRok() const {
    return rok;
}

int Data::getGodz() const {
    return godz;
}

int Data::getMin() const {
    return min;
}

int Data::getSek() const {
    return sek;
}

void Data::setDzien(int dzien) {
    this->dzien = dzien;
}

void Data::setMiesiac(int miesiac) {
    this->miesiac = miesiac;
}

void Data::setRok(int rok) {
    this->rok = rok;
}

void Data::setGodz(int godz) {
    this->godz = godz;
}

void Data::setMin(int min) {
    this->min = min;
}

void Data::setSek(int sek) {
    this->sek = sek;
}

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

void Data::setData(QDate data) {
    this->rok = data.year();
    this->miesiac = data.month();
    this->dzien = data.day();
    this->godz = 0;
    this->min = 0;
    this->sek = 0;
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

int Data::operator -(const Data &d1) {
    if(this->getRok() != d1.getRok() || this->getMiesiac() != d1.getMiesiac() || this->getDzien() != d1.getDzien()){
        return -1;
    }else {
        int sumaDlaD1 = (this->getSek()*1)+(this->getMin()*60)+(this->getGodz()*3600);
        unsigned int sumaDlaD2 = (d1.getSek()*1)+(d1.getMin()*60)+(d1.getGodz()*3600);
        if(sumaDlaD1 >= sumaDlaD2){
            return sumaDlaD1 - sumaDlaD2;
        }else {
            return sumaDlaD2 - sumaDlaD1;
        }
    }
}
