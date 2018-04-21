#include "pracownik.h"

Pracownik::Pracownik(QString imie, QString nazwisko, QString identyfikator, QString haslo_MD5): Osoba(imie, nazwisko), identyfikator(identyfikator), haslo_MD5(haslo_MD5) {}

QString Pracownik::getImie() const {
    return imie;
}

QString Pracownik::getNazwisko() const {
    return nazwisko;
}

void Pracownik::setImie(QString imie) {
    this->imie = imie;
}

void Pracownik::setNazwisko(QString nazwisko) {
    this->nazwisko = nazwisko;
}

void Pracownik::wypiszDane() {

}

void Pracownik::dodaj() {

}

void Pracownik::usun(int id) {

}

void Pracownik::modyfikuj() {

}

void Pracownik::wyszukiwanie(QString nazwa) {

}
