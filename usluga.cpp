#include "usluga.h"

Usluga::Usluga(QString nazwa, double cena, QString opis, QString czas): nazwa(nazwa), cena(cena), opis(opis), czas(czas) {

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

QString Usluga::getCzas() const {
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

void Usluga::setCzas(QString czas) {
    this->czas = czas;
}

void Usluga::dodaj() {
    SqlConnect *conn = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    conn->OpenConnection();
    TableFiller *addService = new TableFiller(conn->getSqlDatabaseObject(), QString("INSERT INTO uslugi(nazwa, cena, czas, opis) VALUES ('"+this->getNazwa()+"','"+this->getCena()+"','"+this->getCzas()+"','"+this->getOpis()+"')"));
    addService->executeInsertUpdateDelete();
    conn->CloseConnection();
}

void Usluga::usun(int id) {
    SqlConnect *conn = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    conn->OpenConnection();
    TableFiller *removeService = new TableFiller(conn->getSqlDatabaseObject(), QString("DELETE FROM uslugi WHERE uslugi_id='"+QString::number(id)+"'"));
    removeService->executeInsertUpdateDelete();
    conn->CloseConnection();
}

void Usluga::modyfikuj(int id) {
    SqlConnect* conn = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    conn->OpenConnection();
    qDebug() << this->getCena();
    TableFiller *modifyService = new TableFiller(conn->getSqlDatabaseObject(), QString("UPDATE uslugi SET nazwa='"+this->getNazwa()+"', cena='"+QString::number(this->getCena())+"', czas='"+this->getCzas()+"', opis='"+this->getOpis()+"' WHERE uslugi_id='"+QString::number(id)+"'"));
    modifyService->executeInsertUpdateDelete();
    conn->CloseConnection();
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

void Usluga::pracownicyDlaUslugi(QTableView *table, int usluga) {
    SqlConnect* conn = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    conn->OpenConnection();
    table->setStyleSheet("border-image: none");
    TableFiller* workersForService = new TableFiller(conn->getSqlDatabaseObject(), table, QString("SELECT u.uzytkownik_id, u.uzytkownik_nazwa AS ID, u.uzytkownik_imie AS Imię, u.uzytkownik_nazwisko AS Nazwisko FROM uzytkownik AS u, uzytkownik_usluga AS uu WHERE u.uzytkownik_id=uu.uzytkownik_id AND uu.uslugi_id="+QString::number(usluga)));
    workersForService->fillTheTable();
    table->hideColumn(0);
    table->hideColumn(1);
    conn->CloseConnection();
}
