#include "firma.h"

Firma::Firma(QString n, QString b, QString em, QString adr, QString kodp, QString mias, QString woje, QString kraj, QString nip): nazwa(n), branza(b), email(em), adres(adr), kodPocztowy(kodp), miasto(mias), wojewodztwo(woje), kraj(kraj), nip(nip) { }

QString Firma::getNazwa() const {
    return nazwa;
}

QString Firma::getBranza() const {
    return branza;
}

QString Firma::getEmail() const {
    return email;
}

QString Firma::getAdres() const {
    return adres;
}

QString Firma::getKodPocztowy() const {
    return kodPocztowy;
}

QString Firma::getMiasto() const {
    return miasto;
}

QString Firma::getWojewodztwo() const {
    return wojewodztwo;
}

QString Firma::getKraj() const {
    return kraj;
}

QString Firma::getNip() const {
    return nip;
}

void Firma::setNazwa(QString nazwa) {
    this->nazwa = nazwa;
}

void Firma::setBranza(QString branza) {
    this->branza = branza;
}

void Firma::setEmail(QString email) {
    this->email = email;
}

void Firma::setAdres(QString adres) {
    this->adres = adres;
}

void Firma::setKodPocztowy(QString kodPocztowy) {
    this->kodPocztowy = kodPocztowy;
}

void Firma::setMiasto(QString miasto) {
    this->miasto = miasto;
}

void Firma::setWojewodztwo(QString wojewodztwo) {
    this->wojewodztwo = wojewodztwo;
}

void Firma::setKraj(QString kraj) {
    this->kraj = kraj;
}

void Firma::setNip(QString nip) {
    this->nip = nip;
}

void Firma::modyfikuj() {
}

QStringList Firma::podajInfo() {
    SqlConnect *conn = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    conn->OpenConnection();
    TableFiller *tf = new TableFiller(conn->getSqlDatabaseObject(), QString("SELECT nazwa, branza, email, adres, kod_pocztowy, miasto, wojewodztwo, kraj, nip  FROM info_o_firmie WHERE firma_id = 1"));
    QStringList companyData = tf->executeSelect();
    conn->CloseConnection();
    if(companyData.length() == 0){
        for(int i = 0; i < 8; i++){
            companyData.append(" ");
        }
    }
    return companyData;
}

void Firma::pokazInfo(QGroupBox *gb, QStringList dane) {
    QList<QLineEdit*> compData = gb->findChildren<QLineEdit*>();
    for(int i = 0; i < compData.length(); i++){
        compData[i]->setText(dane[i]);
    }
}
