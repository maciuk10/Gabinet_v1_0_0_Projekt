#include "usluga.h"

Usluga::Usluga(QString nazwa, double cena, QString opis, QDateTime czas) {

}

QString Usluga::getNazwa() const {
    return nazwa;
}

double Usluga::getCena() const {
    return cena;
}

QString Usluga::getOpis() const {
    return opis;
}

QDateTime Usluga::getCzas() const {
    return czas;
}

void Usluga::setNazwa(QString nazwa) {
    this->nazwa = nazwa;
}

void Usluga::setCena(double cena) {
    this->cena = cena;
}

void Usluga::setOpis(QString opis) {
    this->opis = opis;
}

void Usluga::setCzas(QDateTime czas) {
    this->czas = czas;
}

void Usluga::dodaj() {

}

void Usluga::usun(int id) {

}

void Usluga::modyfikuj() {

}

void Usluga::wyszukiwanie(QString nazwa, QTableView *tabela) {
    SqlConnect* conn = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    conn->OpenConnection();
    tabela->setStyleSheet("border-image: none");
    TableFiller* fillService = new TableFiller(conn->getSqlDatabaseObject(), tabela, QString("SELECT uslugi_id AS ID, nazwa AS Nazwa, cena AS Cena, czas AS 'Czas wykonania', opis AS 'Opis' FROM uslugi WHERE CONCAT(nazwa, cena, czas) LIKE '%"+nazwa+"%'"));
    fillService->fillTheTable();
    tabela->hideColumn(0);
    conn->CloseConnection();
}
