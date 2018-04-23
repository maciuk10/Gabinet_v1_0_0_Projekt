#include "wizyta.h"


Wizyta::Wizyta(Klient *klient, Usluga *usluga, Pracownik *pracownik, Data *rezerwacjaOd, Data *rezerwacjaDo, QString status): klient(klient), usluga(usluga), pracownik(pracownik), rezerwacjaOd(rezerwacjaOd), rezerwacjaDo(rezerwacjaDo), status(status) {

}

Klient *Wizyta::getKlient() const {
    return klient;
}

Usluga *Wizyta::getUsluga() const {
    return usluga;
}

Pracownik *Wizyta::getPracownik() const {
    return pracownik;
}

Data *Wizyta::getRezerwacjaOd() const {
    return rezerwacjaOd;
}

Data *Wizyta::getRezerwacjaDo() const {
    return rezerwacjaDo;
}

QString Wizyta::getStatus() const {
    return status;
}

void Wizyta::setKlient(Klient *klient) {
    this->klient = klient;
}

void Wizyta::setUsluga(Usluga *usluga) {
    this->usluga = usluga;
}

void Wizyta::setPracownik(Pracownik *pracownik) {
    this->pracownik = pracownik;
}

void Wizyta::setRezerwacjaOd(Data *rezerwacjaOd) {
    this->rezerwacjaOd = rezerwacjaOd;
}

void Wizyta::setRezerwacjaDo(Data *rezerwacjaDo) {
    this->rezerwacjaDo = rezerwacjaDo;
}

void Wizyta::setStatus(QString status) {
    this->status = status;
}

int Wizyta::dodaj(int klient, int usluga, int user) {
    SqlConnect* conn = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    conn->OpenConnection();
    TableFiller *addVisit = new TableFiller(conn->getSqlDatabaseObject(), QString("INSERT INTO wizyty(klienci_id, uslugi_id, uzytkownik_id, rezerwacja_od, rezerwacja_do, status) VALUES ('"+QString::number(klient)+"','"+QString::number(usluga)+"','"+QString::number(user)+"', '"+rezerwacjaOd->getDataTekstowa("yyyy-MM-dd hh:mm:ss")+"', '"+rezerwacjaDo->getDataTekstowa("yyyy-MM-dd hh:mm:ss")+"', 'oczekuje')"));
    addVisit->executeInsertUpdateDelete();
    addVisit = new TableFiller(conn->getSqlDatabaseObject(), QString("SELECT LAST_INSERT_ID()"));
    QStringList newid = addVisit->executeSelect();
    conn->CloseConnection();
    return newid[0].toInt();
}

void Wizyta::usun(int usluga)
{
    SqlConnect* conn = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    conn->OpenConnection();
    TableFiller *removeVisit = new TableFiller(conn->getSqlDatabaseObject(), QString("DELETE FROM wizyty WHERE wizyty_id="+QString::number(usluga)));
    removeVisit->executeInsertUpdateDelete();
    conn->CloseConnection();
}
