#include "pracownik.h"

Pracownik::Pracownik(QString imie, QString nazwisko, QString identyfikator): Osoba(imie, nazwisko), identyfikator(identyfikator) {}

QString Pracownik::getImie() const {
    return imie;
}

QString Pracownik::getNazwisko() const {
    return nazwisko;
}

QString Pracownik::getIdentyfikator() const {
    return identyfikator;
}

void Pracownik::setImie(QString imie) {
    this->imie = imie;
}

void Pracownik::setNazwisko(QString nazwisko) {
    this->nazwisko = nazwisko;
}

void Pracownik::setIdentyfikator(QString identyfikator) {
    this->identyfikator = identyfikator;
}

void Pracownik::wypiszDane(QWidget *widget) {
    widget->setWindowTitle("Aplikacja Gabinet v1.0.0 @ Zalogowano: "+this->getImie()+" "+this->getNazwisko());
}

QStringList Pracownik::pokazInfo(int user) {
    SqlConnect *conn = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    conn->OpenConnection();
    TableFiller *tf = new TableFiller(conn->getSqlDatabaseObject(), QString("SELECT uzytkownik_imie, uzytkownik_nazwisko, uzytkownik_nazwa FROM uzytkownik WHERE uzytkownik_id="+QString::number(user)));
    QStringList userData = tf->executeSelect();
    conn->CloseConnection();
    if(userData.length() == 0){
        for(int i = 0; i < 4; i++){
            userData.append(" ");
        }
    }
    return userData;
}

int Pracownik::dodaj() {
    SqlConnect* conn = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    conn->OpenConnection();
    TableFiller *addWorker = new TableFiller(conn->getSqlDatabaseObject(), QString("INSERT INTO uzytkownik(uzytkownik_nazwa, uzytkownik_imie, uzytkownik_nazwisko, haslo, pracownik) VALUES ('"+this->getIdentyfikator()+"', '"+this->getImie()+"', '"+this->getNazwisko()+"', PASSWORD('"+this->getIdentyfikator()+"'), '1')"));
    addWorker->executeInsertUpdateDelete();
    TableFiller *retNewId = new TableFiller(conn->getSqlDatabaseObject(), QString("SELECT uzytkownik_id FROM uzytkownik ORDER BY uzytkownik_id DESC LIMIT 1"));
    QStringList newid = retNewId->executeSelect();
    conn->CloseConnection();
    return newid[0].toInt();
}

void Pracownik::usun(int id) {
    SqlConnect* conn = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    conn->OpenConnection();
    TableFiller *removeWorker = new TableFiller(conn->getSqlDatabaseObject(), QString("DELETE FROM uzytkownik WHERE uzytkownik_id='"+QString::number(id)+"'"));
    removeWorker->executeInsertUpdateDelete();
    conn->CloseConnection();
}

void Pracownik::modyfikuj(int identify) {
    SqlConnect* conn = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    conn->OpenConnection();
    TableFiller *modifyWorker = new TableFiller(conn->getSqlDatabaseObject(), QString("UPDATE uzytkownik SET uzytkownik_nazwa='"+this->getIdentyfikator()+"', uzytkownik_imie='"+this->getImie()+"', uzytkownik_nazwisko='"+this->getNazwisko()+"' WHERE uzytkownik_id='"+QString::number(identify)+"'"));
    modifyWorker->executeInsertUpdateDelete();
    conn->CloseConnection();
}

void Pracownik::wyszukiwanie(QString nazwa, QTableView* tabela) {
    SqlConnect* conn = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    conn->OpenConnection();
    tabela->setStyleSheet("border-image: none");
    TableFiller* fillWorker = new TableFiller(conn->getSqlDatabaseObject(), tabela, QString("SELECT uzytkownik_id, uzytkownik_nazwa AS ID, uzytkownik_imie AS Imię, uzytkownik_nazwisko AS Nazwisko FROM uzytkownik WHERE CONCAT(uzytkownik_nazwa, uzytkownik_imie, uzytkownik_nazwisko) LIKE '%"+nazwa+"%'"));
    fillWorker->fillTheTable();
    tabela->hideColumn(0);
    conn->CloseConnection();
}

void Pracownik::mojeUslugi() {

}

void Pracownik::pokazGodzinyPracy(QGroupBox *gb) {
    SqlConnect* conn = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    conn->OpenConnection();
    TableFiller *showHours = new TableFiller(conn->getSqlDatabaseObject(), QString("SELECT po_od, po_do, wt_od, wt_do, sr_od, sr_do, cz_od, cz_do, pi_od, pi_do, so_od, so_do FROM godziny, uzytkownik WHERE godziny.uzytkownik_id = uzytkownik.uzytkownik_id AND uzytkownik.uzytkownik_nazwa='"+this->getIdentyfikator()+"'"));
    QStringList results = showHours->executeSelect();
    QList<QLineEdit*> hours = gb->findChildren<QLineEdit*>();
    for(int i = 0; i < hours.length(); i++){
        hours[i]->setText(results[i]);
    }
    conn->CloseConnection();
}
