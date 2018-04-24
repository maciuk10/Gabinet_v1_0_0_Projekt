#include "klient.h"

Klient::Klient(QString imie, QString nazwisko, QString email, QString telefon,
QString ulica, QString numerUlicy, QString kodPocztowy, QString miasto):
    Osoba(imie, nazwisko), email(email), telefon(telefon), ulica(ulica),
    numerUlicy(numerUlicy), kodPocztowy(kodPocztowy), miasto(miasto) {}


QString Klient::getImie() const {
    return imie;
}

QString Klient::getNazwisko() const {
    return nazwisko;
}

QString Klient::getEmail() const {
    return email;
}

QString Klient::getTelefon() const {
    return telefon;
}

QString Klient::getUlica() const {
    return ulica;
}

QString Klient::getNumerUlicy() const {
    return numerUlicy;
}

QString Klient::getKodPocztowy() const {
    return kodPocztowy;
}

QString Klient::getMiasto() const {
    return miasto;
}

void Klient::setImie(QString imie) {
    this->imie = imie;
}

void Klient::setNazwisko(QString nazwisko) {
    this->nazwisko = nazwisko;
}

void Klient::setEmail(QString email) {
    this->email = email;
}

void Klient::setTelefon(QString telefon) {
    this->telefon = telefon;
}

void Klient::setUlica(QString ulica) {
    this->ulica = ulica;
}

void Klient::setNumerUlicy(QString numerUlicy) {
    this->numerUlicy = numerUlicy;
}

void Klient::setKodPocztowy(QString kodPocztowy) {
    this->kodPocztowy = kodPocztowy;
}

void Klient::setMiasto(QString miasto) {
    this->miasto = miasto;
}

void Klient::wypiszDane(QWidget *widget, QStringList dodatkoweInfo) {
    QList<QLineEdit*> clientData = widget->findChildren<QLineEdit*>();
    for(int i = 0; i < clientData.length(); i++){
        clientData[i]->setText(dodatkoweInfo[i+1]);
    }
}

int Klient::dodaj() {
    SqlConnect *conn = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    conn->OpenConnection();
    TableFiller *addClient = new TableFiller(conn->getSqlDatabaseObject(), QString("INSERT INTO klienci (imie, nazwisko, email, telefon, ulica, numer, poczta, miejscowosc) VALUES ('"+this->getImie()+"','"+this->getNazwisko()+"','"+this->getEmail()+"','"+this->getTelefon()+"','"+this->getUlica()+"','"+this->getNumerUlicy()+"','"+this->getKodPocztowy()+"','"+this->getMiasto()+"')"));
    addClient->executeInsertUpdateDelete();
    conn->CloseConnection();
}

void Klient::usun(int id) {
    SqlConnect *conn = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    conn->OpenConnection();
    TableFiller *removeClient = new TableFiller(conn->getSqlDatabaseObject(), QString("DELETE FROM klienci WHERE klienci_id ="+QString::number(id)));
    removeClient->executeInsertUpdateDelete();
    conn->CloseConnection();
}

void Klient::modyfikuj(int identify) {
    SqlConnect *conn = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    conn->OpenConnection();
    TableFiller *modifyClient = new TableFiller(conn->getSqlDatabaseObject(), QString("UPDATE klienci SET imie='"+this->getImie()+"', nazwisko='"+this->getNazwisko()+"', email='"+this->getEmail()+"', telefon='"+this->getTelefon()+"', ulica='"+this->getUlica()+"', numer='"+this->getNumerUlicy()+"', miejscowosc='"+this->getMiasto()+"', poczta='"+this->getKodPocztowy()+"' WHERE klienci_id="+QString::number(identify)));
    modifyClient->executeInsertUpdateDelete();
    conn->CloseConnection();
}

void Klient::wyszukiwanie(QString nazwa, QTableView *tabela) {
    SqlConnect* conn = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    conn->OpenConnection();
    tabela->setStyleSheet("border-image: none");
    TableFiller* fillClient = new TableFiller(conn->getSqlDatabaseObject(), tabela, QString("SELECT klienci_id AS ID, imie AS Imię, nazwisko AS Nazwisko, email AS 'E-mail', telefon AS Telefon, ulica AS Ulica, numer AS Numer, poczta AS Kod, miejscowosc AS Miejscowosc FROM klienci WHERE CONCAT(imie, nazwisko, email, telefon, ulica, miejscowosc, numer, poczta) LIKE '%"+nazwa+"%'"));
    fillClient->fillTheTable();
    tabela->hideColumn(0);
    conn->CloseConnection();
}
