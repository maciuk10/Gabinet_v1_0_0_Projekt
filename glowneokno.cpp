#include "glowneokno.h"
#include "ui_glowneokno.h"


GlowneOkno::GlowneOkno(QWidget *parent, int userID, SqlConnect *conn) :
    QMainWindow(parent),
    ui(new Ui::GlowneOkno)
{
    ui->setupUi(this);

    this->connection = conn;
    this->userID = userID;
    this->setDefaultWidgetFormatting();
    this->prepareCharts();

    QStringList userInfo = Pracownik::pokazInfo(userID);
    pracownik = new Pracownik(userInfo[0], userInfo[1], userInfo[2]);

    if(userID != 0){
        pracownik->wypiszDane(this);
        ui->usernameProfile->setText("Witaj, "+pracownik->getImie());
    }else {
        qApp->exit();
    }

    QStringList daneFirmy = Firma::podajInfo();
    firma = new Firma(daneFirmy[0], daneFirmy[1], daneFirmy[2], daneFirmy[3], daneFirmy[4], daneFirmy[5], daneFirmy[6], daneFirmy[7], daneFirmy[8]);
    firma->pokazInfo(ui->changeCompanyData, daneFirmy);
}

void GlowneOkno::on_reservationServiceSearch_clicked() {
    Usluga::wyszukiwanie(ui->serviceReservationType->text(), ui->serviceTable);
    ui->serviceTable->hideColumn(4);
}

void GlowneOkno::on_reservationClientSearch_clicked()
{
    Klient::wyszukiwanie(ui->clientReservationType->text(), ui->clientTable);
    for(int i = 3; i < 9; i++){
        ui->clientTable->hideColumn(i);
    }
}

void GlowneOkno::on_workerReservationSearch_clicked()
{
    Pracownik::wyszukiwanie(ui->workerReservationType->text(), ui->workerReservationTable);
}

void GlowneOkno::on_clientSearch_Client_clicked() {
    ui->ClientsTable_Client->clearSelection();
    this->clearControlsFromCertainGroup(ui->clientData);
    Klient::wyszukiwanie(ui->clientsClientType->text(), ui->ClientsTable_Client);
}

void GlowneOkno::on_workerWorkSearch_clicked() {
    ui->addServiceWorkTable->setStyleSheet("border-image: none");
    ui->servicesWorkTable->setStyleSheet("border-image: none");
    Pracownik::wyszukiwanie(ui->workersWorkType->text(), ui->workersWorkTable);
}

void GlowneOkno::on_servicesServiceSearch_clicked() {
    Usluga::wyszukiwanie(ui->servicesServiceType->text(), ui->servicesServiceTable);
}

void GlowneOkno::on_workersWorkersSearch_clicked() {
    Pracownik::wyszukiwanie(ui->workersWorkersType->text(), ui->workersWorkersTable);
}

void GlowneOkno::on_userDataLink_clicked() {
    this->dataLinkSwitch(0, ui->setDataIndicator);
}

void GlowneOkno::on_companyDataLink_clicked() {
    this->dataLinkSwitch(1, ui->companyIndicator);
}

void GlowneOkno::on_showStatsLink_clicked() {
    this->dataLinkSwitch(2, ui->showStatsIndicator);
}

void GlowneOkno::on_setLeaveLink_clicked() {
    this->dataLinkSwitch(3, ui->leaveIndicator);
}

void GlowneOkno::on_changePasswordLink_clicked() {
    this->dataLinkSwitch(4, ui->changePasswordIndicator);
}

void GlowneOkno::on_workersWorkTable_clicked(const QModelIndex &index) {
    QStringList workersData;
    for(int i = 0; i < index.model()->columnCount(); i++){
        workersData << index.model()->data(index.model()->index(index.row(), i), Qt::DisplayRole).toString();
    }

    ui->workidEdit->setText(workersData[1]);
    ui->workNameEdit->setText(workersData[2]);
    ui->workSurnameEdit->setText(workersData[3]);

    pracownik = new Pracownik(ui->workNameEdit->text(), ui->workSurnameEdit->text(), ui->workidEdit->text());
    pracownik->dodaj();

    ui->servicesWorkTable->setStyleSheet("border-image: none");
    SqlConnect *conn = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    conn->OpenConnection();
    tableCreator = new TableFiller(conn->getSqlDatabaseObject(), ui->servicesWorkTable, QString("SELECT uslugi.uslugi_id AS ID, uslugi.nazwa AS Nazwa, uslugi.cena AS Cena, uslugi.czas AS 'Czas wykonania', uslugi.opis AS Opis FROM uslugi, uzytkownik_usluga WHERE uslugi.uslugi_id = uzytkownik_usluga.uslugi_id AND uzytkownik_usluga.uzytkownik_id ='"+workersData[0]+"'"));
    currentServices = tableCreator->executeSelect();
    tableCreator->fillTheTable();
    ui->servicesWorkTable->hideColumn(0);
    conn->CloseConnection();
    /*if(!alreadyActivated){
        ui->addServiceWorkTable->setStyleSheet("border-image: none");
        tableCreator = new TableFiller(connection->getSqlDatabaseObject(), ui->addServiceWorkTable, QString("SELECT uslugi_id AS ID, nazwa AS Nazwa, cena AS Cena, czas AS 'Czas wykonania', opis AS Opis FROM uslugi WHERE CONCAT(nazwa, cena, czas) LIKE '%"+ui->servicesServiceType->text()+"%'"));
        tableCreator->fillTheTable();
        ui->addServiceWorkTable->setColumnHidden(0,true);
        alreadyActivated = true;
    }*/
}

void GlowneOkno::on_ClientsTable_Client_clicked(const QModelIndex &index) {
    QList<QLineEdit*> clientData = ui->clientData->findChildren<QLineEdit*>();
    for(int i = 0; i < clientData.length(); i++){
        clientData[i]->setText(index.model()->data(index.model()->index(index.row(), i+1), Qt::DisplayRole).toString());
    }
    ClientID = index.model()->data(index.model()->index(index.row(), 0), Qt::DisplayRole).toInt();
}

void GlowneOkno::on_clearClients_clicked() {
    ui->ClientsTable_Client->clearSelection();
    this->clearControlsFromCertainGroup(ui->clientData);
}

void GlowneOkno::on_addClientBtn_clicked() {
    bool valid = areLineEditsValid(ui->clientData);
    if(valid && ui->clientNameEdit->text().length() > 3 && ui->clientSurnameEdit->text().length() > 4){
        klient = new Klient(ui->clientNameEdit->text(), ui->clientSurnameEdit->text(), ui->clientEmailEdit->text(), ui->clientPhoneEdit->text(), ui->clientStreetLine->text(), ui->clientStrNoLine->text(), ui->clientCodeLine->text(), ui->clientCityLine->text());
        klient->dodaj();
        QMessageBox::information(this, "Dodanie klienta", "Pomyślnie dodano klienta do bazy danych", QMessageBox::Ok);
        clearControlsFromCertainGroup(ui->clientData);
        ui->ClientsTable_Client->clearSelection();
        Klient::wyszukiwanie(ui->clientsClientType->text(), ui->ClientsTable_Client);
    }else {
        QMessageBox::warning(this, "Wypełnij pola formularza", "Wymagania walidacyjne formularza nie zostały spełnione", QMessageBox::Ok);
    }
}

void GlowneOkno::on_clientModifyBtn_clicked() {
    bool valid = areLineEditsValid(ui->clientData);
    if(valid && ClientID > 0){
        klient = new Klient(ui->clientNameEdit->text(), ui->clientSurnameEdit->text(), ui->clientEmailEdit->text(), ui->clientPhoneEdit->text(), ui->clientStreetLine->text(), ui->clientStrNoLine->text(), ui->clientCodeLine->text(), ui->clientCityLine->text());
        klient->modyfikuj(ClientID);
        QMessageBox::information(this, "Modyfikacja klienta", "Pomyślnie zmodyfikowano dane klienta z bazy danych", QMessageBox::Ok);
        clearControlsFromCertainGroup(ui->clientData);
        ui->ClientsTable_Client->clearSelection();
        Klient::wyszukiwanie(ui->clientsClientType->text(), ui->ClientsTable_Client);
    }else {
        QMessageBox::warning(this, "Wypełnij pola formularza", "Wymagania walidacyjne formularza nie zostały spełnione", QMessageBox::Ok);
    }
}

void GlowneOkno::on_clientRemoveBtn_clicked() {
    if(ClientID > 0){
        klient = new Klient(ui->clientNameEdit->text(), ui->clientSurnameEdit->text(), ui->clientEmailEdit->text(), ui->clientPhoneEdit->text(), ui->clientStreetLine->text(), ui->clientStrNoLine->text(), ui->clientCodeLine->text(), ui->clientCityLine->text());
        klient->usun(ClientID);
        Klient::wyszukiwanie(ui->clientsClientType->text(), ui->ClientsTable_Client);
        QMessageBox::information(this, "Usunięcie klienta", "Pomyślnie usunięto dane klienta z bazy danych", QMessageBox::Ok);
        clearControlsFromCertainGroup(ui->clientData);
        ui->ClientsTable_Client->clearSelection();
    }
    ClientID = 0;
}


void GlowneOkno::on_workersWorkersTable_clicked(const QModelIndex &index) {
    QList<QLineEdit*> clientData = ui->workersEditFields->findChildren<QLineEdit*>();
    for(int i = 0; i < clientData.length(); i++){
        clientData[i]->setText(index.model()->data(index.model()->index(index.row(), clientData.length() - i), Qt::DisplayRole).toString());
    }
    WorkerID = index.model()->data(index.model()->index(index.row(), 0), Qt::DisplayRole).toInt();
    if(WorkerID != 0){
        pracownik = new Pracownik(ui->workerNameEdit->text(),ui->workerSurnameEdit->text(), ui->workerIDEdit->text());
        pracownik->pokazGodzinyPracy(ui->workerHours);
        this->clearControlsFromCertainGroup(ui->hoursSchema);
    }
}

void GlowneOkno::on_modifyWorkerBtn_clicked() {
    bool valid = areLineEditsValid(ui->workersEditFields) && areLineEditsValid(ui->workerHours);
    if(valid && WorkerID != 0){
        pracownik = new Pracownik(ui->workerNameEdit->text(),ui->workerSurnameEdit->text(), ui->workerIDEdit->text());
        pracownik->modyfikuj(WorkerID);

        SqlConnect *connec = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
        connec->OpenConnection();
        TableFiller *updateHours = new TableFiller(connec->getSqlDatabaseObject(), QString("UPDATE godziny SET po_od='"+ui->ponod->text()+"', po_do='"+ui->pondo->text()+"', wt_od='"+ui->wtod->text()+"', wt_do='"+ui->wtdo->text()+"', sr_od='"+ui->srod->text()+"', sr_do='"+ui->srdo->text()+"', cz_od='"+ui->czod->text()+"', cz_do='"+ui->czdo->text()+"', pi_od='"+ui->ptod->text()+"', pi_do='"+ui->ptdo->text()+"', so_od='"+ui->sood->text()+"', so_do='"+ui->sodo->text()+"' WHERE uzytkownik_id='"+QString::number(WorkerID)+"'"));
        updateHours->executeInsertUpdateDelete();
        QMessageBox::information(this, "Modyfikacja pracownika", "Pomyślnie zmodyfikowano dane pracownika z bazy danych", QMessageBox::Ok);
        clearControlsFromCertainGroup(ui->clientData);
        ui->ClientsTable_Client->clearSelection();
        connec->CloseConnection();

        Pracownik::wyszukiwanie(ui->workersWorkersType->text(), ui->workersWorkersTable);
        connec = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
        connec->OpenConnection();
        TableFiller *showHours = new TableFiller(connec->getSqlDatabaseObject(), QString("SELECT po_od, po_do, wt_od, wt_do, sr_od, sr_do, cz_od, cz_do, pi_od, pi_do, so_od, so_do FROM godziny, uzytkownik WHERE godziny.uzytkownik_id = uzytkownik.uzytkownik_id AND uzytkownik.uzytkownik_id='"+QString::number(WorkerID)+"'"));

        QStringList results = showHours->executeSelect();
        QList<QLineEdit*> hours = ui->workerHours->findChildren<QLineEdit*>();
        for(int i = 0; i < hours.length(); i++){
            hours[i]->setText(results[i]);
        }

        ui->workersWorkersTable->clearSelection();
        this->clearControlsFromCertainGroup(ui->workersEditFields);
        this->clearControlsFromCertainGroup(ui->workHoursFields);
        connec->CloseConnection();
        WorkerID = 0;
    }else {
        QMessageBox::warning(this, "Wypełnij pola formularza", "Wymagania walidacyjne formularza nie zostały spełnione", QMessageBox::Ok);
    }
}

void GlowneOkno::on_removeWorkerBtn_clicked() {
    if(WorkerID != 0){
        pracownik = new Pracownik(ui->workerNameEdit->text(),ui->workerSurnameEdit->text(), ui->workerIDEdit->text());
        pracownik->usun(WorkerID);

        QMessageBox::information(this, "Usunięcie pracownika", "Pomyślnie usunięto dane pracownika z bazy danych", QMessageBox::Ok);
        clearControlsFromCertainGroup(ui->clientData);
        ui->ClientsTable_Client->clearSelection();
        Pracownik::wyszukiwanie(ui->workersWorkersType->text(), ui->workersWorkersTable);
        ui->workersWorkersTable->clearSelection();
        this->clearControlsFromCertainGroup(ui->workersEditFields);
        this->clearControlsFromCertainGroup(ui->workHoursFields);
    }
    WorkerID = 0;
}

void GlowneOkno::on_clearFieldsWorkerBtn_clicked() {
    ui->workersWorkersTable->clearSelection();
    this->clearControlsFromCertainGroup(ui->workersEditFields);
    this->clearControlsFromCertainGroup(ui->workHoursFields);
    WorkerID = 0;
}

void GlowneOkno::on_toolButton_clicked() {
    QString from = ui->hour_from->text();
    QString to = ui->hour_to->text();
    if(from.length() == 5 && to.length() == 5){
        if(validHourRange(from, to)){
            QList<QLineEdit*> hours = ui->workerHours->findChildren<QLineEdit*>();
            for(int i = 0; i < hours.length(); i++){
                if(i%2==0){
                    hours[i]->setText(from+":00");
                }else {
                    hours[i]->setText(to+":00");
                }
            }
        }else {
            QMessageBox::warning(this, "Ustalenie godzin pracy", "Niepoprawnie ustawiono godziny pracy dla pracownika", QMessageBox::Ok);
        }
    }else {
        QMessageBox::warning(this, "Ustalenie godzin pracy", "Podano niepoprawne wartości dla pola godzin. Pamiętaj o schemacie 00:00", QMessageBox::Ok);
    }
}

void GlowneOkno::on_addWorkerBtn_clicked() {
    bool valid = areLineEditsValid(ui->workersEditFields) && areLineEditsValid(ui->workerHours);

    if(valid && WorkerID == 0){
        pracownik = new Pracownik(ui->workerNameEdit->text(),ui->workerSurnameEdit->text(), ui->workerIDEdit->text());
        WorkerID = pracownik->dodaj();

        SqlConnect* connec = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
        connec->OpenConnection();
        TableFiller *updateHours = new TableFiller(connec->getSqlDatabaseObject(), QString("INSERT INTO godziny(uzytkownik_id, po_od, po_do, wt_od, wt_do, sr_od, sr_do, cz_od, cz_do, pi_od, pi_do, so_od, so_do) VALUES ('"+QString::number(WorkerID)+"','"+ui->ponod->text()+"','"+ui->pondo->text()+"','"+ui->wtod->text()+"','"+ui->wtdo->text()+"','"+ui->srod->text()+"','"+ui->srdo->text()+"','"+ui->czod->text()+"','"+ui->czdo->text()+"','"+ui->ptod->text()+"','"+ui->ptdo->text()+"','"+ui->sood->text()+"','"+ui->sodo->text()+"')"));
        updateHours->executeInsertUpdateDelete();
        QMessageBox::information(this, "Dodanie pracownika", "Pomyślnie dodano dane pracownika do bazy danych", QMessageBox::Ok);
        clearControlsFromCertainGroup(ui->clientData);
        ui->ClientsTable_Client->clearSelection();
        connec->CloseConnection();

        Pracownik::wyszukiwanie(ui->workersWorkersType->text(), ui->workersWorkersTable);
        connec = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
        connec->OpenConnection();

        TableFiller *showHours = new TableFiller(connection->getSqlDatabaseObject(), QString("SELECT po_od, po_do, wt_od, wt_do, sr_od, sr_do, cz_od, cz_do, pi_od, pi_do, so_od, so_do FROM godziny, uzytkownik WHERE godziny.uzytkownik_id = uzytkownik.uzytkownik_id AND uzytkownik.uzytkownik_nazwa='"+ui->workerIDEdit->text()+"'"));
        QStringList results = showHours->executeSelect();
        QList<QLineEdit*> hours = ui->workerHours->findChildren<QLineEdit*>();
        for(int i = 0; i < hours.length(); i++){
            hours[i]->setText(results[i]);
        }
        ui->workersWorkersTable->clearSelection();
        this->clearControlsFromCertainGroup(ui->workersEditFields);
        this->clearControlsFromCertainGroup(ui->workHoursFields);
        connec->CloseConnection();
        WorkerID = 0;
    }else {
        QMessageBox::warning(this, "Wypełnij pola formularza", "Wymagania walidacyjne formularza nie zostały spełnione", QMessageBox::Ok);
    }
}

void GlowneOkno::on_schemaOne_clicked() {
    setHourSchema("07:00", "15:00", ui->workerHours);
}

void GlowneOkno::on_schemaTwo_clicked() {
    setHourSchema("08:00", "16:00", ui->workerHours);
}

void GlowneOkno::on_schemaThree_clicked() {
    setHourSchema("09:00", "17:00", ui->workerHours);
}

void GlowneOkno::on_schemaFour_clicked() {
    setHourSchema("10:00", "18:00", ui->workerHours);
}

void GlowneOkno::on_servicesServiceTable_clicked(const QModelIndex &index) {
    QList<QLineEdit*> serviceData = ui->serviceData->findChildren<QLineEdit*>();
    for(int i = 0; i < serviceData.length(); i++){
        serviceData[i]->setText(index.model()->data(index.model()->index(index.row(), i+1), Qt::DisplayRole).toString());
    }
    ServiceID = index.model()->data(index.model()->index(index.row(), 0), Qt::DisplayRole).toInt();
    ui->serviceDesc->setText(index.model()->data(index.model()->index(index.row(), 4), Qt::DisplayRole).toString());
}

void GlowneOkno::on_serviceClearBtn_clicked() {
    clearControlsFromCertainGroup(ui->serviceData);
    ui->servicesServiceTable->clearSelection();
    ui->servicesServiceType->setText("");
    ServiceID = 0;
}

void GlowneOkno::on_serviceRemoveBtn_clicked() {
    bool valid = areLineEditsValid(ui->serviceData) && areTextEditsValid(ui->serviceData);
    if(valid && ServiceID > 0){
        usluga = new Usluga(ui->serviceName->text(),ui->servicePrice->text().toDouble(),ui->serviceDesc->toPlainText(), ui->serviceTime->text());
        usluga->usun(ServiceID);

        QMessageBox::information(this, "Usunięcie usługi", "Pomyślnie usunięto dane usługi z bazy danych", QMessageBox::Ok);

        Usluga::wyszukiwanie(ui->servicesServiceType->text(), ui->servicesServiceTable);

        ui->servicesServiceTable->clearSelection();
        ui->servicesServiceTable->clearSelection();
        this->clearControlsFromCertainGroup(ui->serviceData);
    }
    ServiceID = 0;
}

void GlowneOkno::on_serviceModifyBtn_clicked() {
    bool valid = areLineEditsValid(ui->serviceData) && areTextEditsValid(ui->serviceData);
    if(valid && ServiceID > 0){
        ui->servicePrice->setText(priceFormatter(ui->servicePrice->text()));
        double price = ui->servicePrice->text().toDouble();

        usluga = new Usluga(ui->serviceName->text(), price,ui->serviceDesc->toPlainText(), ui->serviceTime->text());
        usluga->modyfikuj(ServiceID);

        QMessageBox::information(this, "Modyfikacja usługi", "Pomyślnie zmodyfikowano dane usługi z bazy danych", QMessageBox::Ok);

        Usluga::wyszukiwanie(ui->servicesServiceType->text(), ui->servicesServiceTable);

        ui->servicesServiceTable->clearSelection();
        this->clearControlsFromCertainGroup(ui->serviceData);
    }
    ServiceID = 0;
}

void GlowneOkno::on_serviceAddBtn_clicked() {
    bool valid = areLineEditsValid(ui->serviceData) && areTextEditsValid(ui->serviceData);
    if(valid && ServiceID == 0){

        ui->servicePrice->setText(priceFormatter(ui->servicePrice->text()));
        usluga = new Usluga(ui->serviceName->text(),ui->servicePrice->text().toDouble(),ui->serviceDesc->toPlainText(), ui->serviceTime->text());
        usluga->dodaj();

        QMessageBox::information(this, "Dodanie usługi", "Pomyślnie dodano dane usługi do bazy danych", QMessageBox::Ok);

        Usluga::wyszukiwanie(ui->servicesServiceType->text(), ui->servicesServiceTable);

        ui->servicesServiceTable->clearSelection();
        this->clearControlsFromCertainGroup(ui->serviceData);
        ServiceID = 0;
    }else{
        QMessageBox::information(this, "Błąd walidacji", "Wprowadzone dane nie spełniają wymagań walidacyjnych. Popraw je i spróbuj ponownie", QMessageBox::Ok);
    }
}

void GlowneOkno::on_changeCompanyInfo_clicked() {
    bool valid = areLineEditsValid(ui->changeCompanyData);
    if(valid){
        firma = new Firma(ui->compName->text(), ui->compCat->text(), ui->comMail->text(), ui->compAdr->text(), ui->compCode->text(), ui->compCity->text(), ui->compVoivode->text(), ui->compCntry->text(), ui->nip->text());
        firma->modyfikuj();

        QMessageBox::information(this, "Zmiana danych firmy", "Pomyślnie zmodyfikowano dane firmy z bazy danych", QMessageBox::Ok);

        QStringList companyData = Firma::podajInfo();
        firma->pokazInfo(ui->changeCompanyData, companyData);
    }
}

void GlowneOkno::on_simpleDataChange_clicked() {
    bool valid = areLineEditsValid(ui->simpleDataGB);
    if(valid){
        tableCreator = new TableFiller(connection->getSqlDatabaseObject(), QString("UPDATE uzytkownik SET uzytkownik_nazwa='"+ui->simpID->text()+"', uzytkownik_imie='"+ui->simpName->text()+"', uzytkownik_nazwisko='"+ui->simpSurname->text()+"' WHERE uzytkownik_nazwa='"+ui->simpID->text()+"'"));
        tableCreator->executeInsertUpdateDelete();
        QMessageBox::information(this, "Zmiana danych osobowych", "Pomyślnie zmodyfikowano dane osobowe w bazy danych. Aby zobaczyć zmiany należy sie ponownie zalogować", QMessageBox::Ok);
        TableFiller *company = new TableFiller(connection->getSqlDatabaseObject(), QString("SELECT uzytkownik_nazwa, uzytkownik_imie, uzytkownik_nazwisko FROM uzytkownik WHERE uzytkownik_id="+QString::number(userID)));
        QStringList companyData = company->executeSelect();
        QList<QLineEdit*> companyList = ui->simpleDataGB->findChildren<QLineEdit*>();
        for(int i = 0; i < companyList.length(); i++){
            companyList[i]->setText(companyData[i]);
        }
    }
}

void GlowneOkno::on_changePasswordBtn_clicked() {
    bool valid = areLineEditsValid(ui->changePasswordGB) && (ui->newPass->text() == ui->oldPass->text());
    if(valid){
        tableCreator = new TableFiller(connection->getSqlDatabaseObject(), QString("UPDATE uzytkownik SET haslo=PASSWORD('"+ui->newPass->text()+"') WHERE uzytkownik_id="+QString::number(userID)));
        tableCreator->executeInsertUpdateDelete();
        if (tableCreator->getcountOfRows() <= 0){
            QMessageBox::warning(this, "Zmiana hasła użytkownika", "Pomyślnie zmodyfikowano hasło użytkownika w bazie danych. Aby zobaczyć zmiany należy sie ponownie zalogować", QMessageBox::Ok);
            clearControlsFromCertainGroup(ui->changePasswordGB);
        }
    }
}

void GlowneOkno::on_addServiceWorkTable_doubleClicked(const QModelIndex &index) {
    QString idxToAdd = index.model()->data(index.model()->index(index.row(), 0), Qt::DisplayRole).toString();
    QStringList currentServiceIds;
    for(int i = 0; i < currentServices.length(); i+=5){
        currentServiceIds.append(currentServices[i]);
    }
    if(currentServiceIds.contains(idxToAdd)){
        QMessageBox::information(this, "Pracownik posiada wybraną kompetencję", "Wybrana usługa znajduje się już w kompetencjach pracownika i nie ma potrzeby jej dodawać. W celu usunięcia kompetencji pracownika kliknij dwukrotnie na wybraną usługę na liście usług pracownika.", QMessageBox::Ok);
    }else {
        tableCreator = new TableFiller(connection->getSqlDatabaseObject(), QString("INSERT INTO uzytkownik_usluga(uzytkownik_id, uslugi_id) VALUES ('"+currentid[0]+"','"+idxToAdd+"')"));
        tableCreator->executeInsertUpdateDelete();
        QMessageBox::information(this, "Zmiana kompetencji pracownika", "Pomyślnie zmodyfikowano kompetencje pracownika w bazie danych.", QMessageBox::Ok);

        tableCreator = new TableFiller(connection->getSqlDatabaseObject(), ui->servicesWorkTable, QString("SELECT uslugi.uslugi_id AS ID, uslugi.nazwa AS Nazwa, uslugi.cena AS Cena, uslugi.czas AS 'Czas wykonania', uslugi.opis AS Opis FROM uslugi, uzytkownik_usluga WHERE uslugi.uslugi_id = uzytkownik_usluga.uslugi_id AND uzytkownik_usluga.uzytkownik_id ='"+currentid[0]+"'"));
        currentServices = tableCreator->executeSelect();
        tableCreator->fillTheTable();
        ui->servicesWorkTable->setColumnHidden(0,true);
    }
}

void GlowneOkno::on_workerReservationTable_clicked(const QModelIndex &index) {
    clearWidgets(ui->hoursLayout);
    QString currentUserID = index.model()->data(index.model()->index(index.row(), 0), Qt::DisplayRole).toString();

    tableCreator = new TableFiller(connection->getSqlDatabaseObject(), QString("SELECT uzytkownik_id FROM uzytkownik WHERE uzytkownik_nazwa='"+currentUserID+"'"));
    QStringList userIDList = tableCreator->executeSelect();
    userID = userIDList[0].toInt();

    QDate today = ui->calendarWidget->selectedDate();
    QString todayStr = today.toString("dd.MM.yyyy");
    ui->choosenDate->setText(todayStr);
    QString selectedDay = giveDays();
    if(selectedDay == "śr"){
        selectedDay = "sr";
    }
    tableCreator = new TableFiller(connection->getSqlDatabaseObject(), QString("SELECT "+selectedDay+"_od, "+selectedDay+"_do FROM godziny AS g, uzytkownik AS u WHERE u.uzytkownik_id=g.uzytkownik_id AND u.uzytkownik_nazwa='"+currentUserID+"'"));
    QStringList returnedHours = tableCreator->executeSelect();
    generateDailySchedule(returnedHours[0], returnedHours[1]);
    ui->hoursField->setLayout(ui->hoursLayout);
}

void GlowneOkno::on_calendarWidget_clicked(const QDate &date) {
    clearWidgets(ui->hoursLayout);
    ui->workerReservationTable->clearSelection();
    if(QDate::longDayName(date.dayOfWeek()) == "Niedziela"){
        QMessageBox::warning(this, "Wybrano niedzielę", "W wybrany dzień zakład nie oferuje swych usług. Zostanie wybrany pierwszy dzień tygodnia", QMessageBox::Ok);
    }
}

void GlowneOkno::on_servicesWorkTable_doubleClicked(const QModelIndex &index) {
    QString serviceIdx = index.model()->data(index.model()->index(index.row(), 0), Qt::DisplayRole).toString();

    tableCreator = new TableFiller(connection->getSqlDatabaseObject(), QString("DELETE FROM uzytkownik_usluga WHERE uzytkownik_id="+currentid[0]+" AND uslugi_id="+serviceIdx+""));
    tableCreator->executeInsertUpdateDelete();
    QMessageBox::information(this, "Zmiana kompetencji pracownika", "Pomyślnie zmodyfikowano kompetencje pracownika w bazie danych.", QMessageBox::Ok);

    tableCreator = new TableFiller(connection->getSqlDatabaseObject(), ui->servicesWorkTable, QString("SELECT uslugi.uslugi_id AS ID, uslugi.nazwa AS Nazwa, uslugi.cena AS Cena, uslugi.czas AS 'Czas wykonania', uslugi.opis AS Opis FROM uslugi, uzytkownik_usluga WHERE uslugi.uslugi_id = uzytkownik_usluga.uslugi_id AND uzytkownik_usluga.uzytkownik_id ='"+currentid[0]+"'"));
    currentServices = tableCreator->executeSelect();
    tableCreator->fillTheTable();
    ui->servicesWorkTable->setColumnHidden(0,true);
}

void GlowneOkno::on_serviceTable_clicked(const QModelIndex &index){
    clearWidgets(ui->hoursLayout);
    ServiceID = index.model()->data(index.model()->index(index.row(), 0), Qt::DisplayRole).toInt();
    ui->choosenService->setText(index.model()->data(index.model()->index(index.row(), 1), Qt::DisplayRole).toString());
    ui->workerReservationSearch->setEnabled(true);
    QString serviceIdx = index.model()->data(index.model()->index(index.row(), 0), Qt::DisplayRole).toString();

    tableCreator = new TableFiller(connection->getSqlDatabaseObject(), ui->workerReservationTable, QString("SELECT u.uzytkownik_nazwa AS ID, u.uzytkownik_imie AS Imię, u.uzytkownik_nazwisko AS Nazwisko FROM uzytkownik AS u, uzytkownik_usluga AS uu WHERE u.uzytkownik_id=uu.uzytkownik_id AND uu.uslugi_id="+serviceIdx+""));
    tableCreator->fillTheTable();
    ui->workerReservationTable->setStyleSheet("border-image: none");
}

void GlowneOkno::on_clientTable_clicked(const QModelIndex &index) {
    ClientID = index.model()->data(index.model()->index(index.row(), 0), Qt::DisplayRole).toInt();
    ui->choosenClient->setText(index.model()->data(index.model()->index(index.row(), 1), Qt::DisplayRole).toString()+" "+index.model()->data(index.model()->index(index.row(), 2), Qt::DisplayRole).toString());
    clearWidgets(ui->hoursLayout);
}

void GlowneOkno::on_tabWidget_currentChanged(int index) {
    userID = 0;
    ServiceID = 0;
    ClientID = 0;
}

// funkcje pomocnicze

void GlowneOkno::chooseHourFromList(QPushButton* push) {
    ui->choosenDate->setText("");
    ui->choosenDate->setText(ui->calendarWidget->selectedDate().toString("dd-MM-yyyy")+" "+push->text());
    QString dbDate = ui->calendarWidget->selectedDate().toString("yyyy-MM-dd")+" "+push->text().mid(0,8);
    if(push->whatsThis() == "1"){
        push->setStyleSheet("color: #66023C; background-color: #E887B7; border: 2px solid #66023C; font-weight: 800");
        push->setWhatsThis("0");
        tableCreator = new TableFiller(connection->getSqlDatabaseObject(), QString("INSERT INTO wizyty(klienci_id, uslugi_id, uzytkownik_id, rezerwacja_od, rezerwacja_do, status) VALUES ('"+QString::number(ClientID)+"','"+QString::number(ServiceID)+"','"+QString::number(userID)+"', '"+dbDate+"', '"+dbDate+"', 'oczekuje')"));
        tableCreator->executeInsertUpdateDelete();
        push->setText(push->text()+" - "+ui->choosenClient->text()+" - "+ui->choosenService->text());
    }else {
        push->setWhatsThis("1");
        push->setStyleSheet("color: #0099CC; background-color: #D6F1F2; border: 2px solid #D6F1F2; font-weight: 800");
        tableCreator = new TableFiller(connection->getSqlDatabaseObject(), QString("DELETE FROM wizyty WHERE klienci_id='"+QString::number(ClientID)+"' AND uslugi_id='"+QString::number(ServiceID)+"' AND uzytkownik_id='"+QString::number(userID)+"' AND rezerwacja_od='"+dbDate+"'"));
        tableCreator->executeInsertUpdateDelete();
        push->setText(push->text().mid(0,8));
        ui->choosenDate->setText(push->text());
    }
}


bool GlowneOkno::validHourRange(QString from, QString to){
    int fromSum = (from.at(0).digitValue()*1000) + (from.at(1).digitValue()*100) + (from.at(3).digitValue()*10) + (from.at(4).digitValue()*1);
    int toSum = (to.at(0).digitValue()*1000) + (to.at(1).digitValue()*100) + (to.at(3).digitValue()*10) + (to.at(4).digitValue()*1);

    if (toSum > fromSum){
        return true;
    }else {
        return false;
    }
}

void GlowneOkno::setHourSchema(QString from, QString to, QGroupBox *gb) {
    QList<QLineEdit*> fields = gb->findChildren<QLineEdit*>();
    for(int i = 0; i < fields.length(); i++){
        if(i%2==0){
            fields[i]->setText(from+":00");
        }else{
            fields[i]->setText(to+":00");
        }
    }
}

void GlowneOkno::generateDailySchedule(QString hourFrom, QString hourTo) {
    QTime hFrom = QTime::fromString(hourFrom, "hh:mm:ss");
    QTime hTo = QTime::fromString(hourTo, "hh:mm:ss");
    int amountOfMinutes = hFrom.secsTo(hTo) / 60;
    int amountOfBlocks = amountOfMinutes / 30;
    for(int i = 0; i < amountOfBlocks; i++){
        QPushButton* hour = new QPushButton(hFrom.toString(), this);
        hour->setStyleSheet("color: #0099CC; background-color: #D6F1F2; border: 2px solid #D6F1F2; font-weight: 800");
        hour->setWhatsThis("1");
        ui->hoursLayout->addWidget(hour);
        hFrom = hFrom.addSecs(1800);
        connect(hour, &QPushButton::clicked, [=]{
            chooseHourFromList(hour);
        });
    }
}

void GlowneOkno::clearWidgets(QLayout *layout) {
    if (!layout){
        return;
    }
    while (auto item = layout->takeAt(0)) {
        delete item->widget();
        clearWidgets(item->layout());
    }
}

QString GlowneOkno::giveDays() {
     QString currentDay = QDate::longDayName(ui->calendarWidget->selectedDate().dayOfWeek());
     return currentDay.mid(0,2);
}

bool GlowneOkno::areLineEditsValid(QGroupBox *gb) {
    QList<QLineEdit*> fields = gb->findChildren<QLineEdit*>();
    foreach (QLineEdit* line, fields) {
        if(line->text() == ""){
            return false;
        }
    }
    return true;
}

bool GlowneOkno::areTextEditsValid(QGroupBox *gb) {
    QList<QTextEdit*> fields = gb->findChildren<QTextEdit*>();
    foreach (QTextEdit* line, fields) {
        if(line->toPlainText() == ""){
            return false;
        }
    }
    return true;
}

void GlowneOkno::prepareCharts() {
        QBarSet *set0 = new QBarSet("MIN");
        QBarSet *set1 = new QBarSet("ŚREDNIA");
        QBarSet *set2 = new QBarSet("MAX");

        *set0 << 15 << 21 << 27 << 19 << 23 << 27 << 16 << 23 << 17 << 15 << 19 << 31;
        *set1 << 9 << 16 << 23 << 17 << 24 << 31 << 9 << 16 << 23 << 27 << 19 << 23;
        *set2 << 18 << 23 << 28 << 21 << 28 << 35 << 23 << 28 << 21 << 17 << 13 << 25;
        QBarSeries *series = new QBarSeries();
        series->append(set0);
        series->append(set1);
        series->append(set2);
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Liczba odwiedzin gabinetu dla konkretnego miesiąca");
        chart->setAnimationOptions(QChart::SeriesAnimations);
        QStringList categories;
        categories << "Sty" << "Lut" << "Mar" << "Kwi" << "Maj" << "Cze" << "Lip" << "Sie" << "Wrz" << "Paź" << "Lis" << "Gru";
        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->append(categories);
        chart->createDefaultAxes();
        chart->setAxisX(axis, series);
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);



            QLineSeries *series2 = new QLineSeries();

            series2->append(1, 530);
            series2->append(2, 680);
            series2->append(3, 583);
            series2->append(4, 721);
            series2->append(5, 594);
            *series2 << QPointF(6, 647) << QPointF(7, 672) << QPointF(8, 697) << QPointF(9, 712) << QPointF(10, 681) << QPointF(11, 588) << QPointF(12, 614);

            QChart *chart2 = new QChart();
            chart2->legend()->hide();
            chart2->addSeries(series2);
            chart2->createDefaultAxes();
            chart2->setTitle("Zarobki gabinetu dla konkretnego miesiąca");
            QChartView *chartView2 = new QChartView(chart2);
            chartView2->setRenderHint(QPainter::Antialiasing);

            ui->gridLayoutCharts->addWidget(chartView);
            ui->gridLayoutCharts->addWidget(chartView2);
            ui->gridLayoutCharts->activate();
}

void GlowneOkno::clearControlsFromCertainGroup(QGroupBox *gb) {
    QList<QLineEdit*> dataLE = gb->findChildren<QLineEdit*>();
    for(int i = 0; i < dataLE.length(); i++){
        dataLE[i]->setText("");
    }
    QList<QTextEdit*> dataTE = gb->findChildren<QTextEdit*>();
    for(int i = 0; i < dataTE.length(); i++){
        dataTE[i]->setText("");
    }
}

void GlowneOkno::setCurrentTab(int tabIndex){
    ui->tabWidget->setCurrentIndex(tabIndex);
}

void GlowneOkno::clearIndicators() {
    QList<QLabel*> indicators;
    indicators << ui->setDataIndicator << ui->companyIndicator << ui->showStatsIndicator << ui->leaveIndicator << ui->changePasswordIndicator;
    for(int i = 0; i < indicators.count(); i++){
        indicators[i]->setStyleSheet("background-color: transparent");
    }
}


void GlowneOkno::setDefaultWidgetFormatting() {
    ui->userDataSettingTab->setCurrentIndex(0);
    ui->userDataSettingTab->tabBar()->hide();
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->tabBar()->hide();
    ui->calendarWidget->setFixedWidth(235);

    QList<QTableView*> tables = findChildren<QTableView*>();
    foreach (QTableView* t, tables) {
        t->horizontalHeader()->setStretchLastSection(true);
        t->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        t->setSelectionBehavior(QAbstractItemView::SelectRows);
        t->verticalHeader()->hide();
    }


    connect(ui->logout, SIGNAL(clicked(int)), ui->logout, SLOT(closeProgram(int)));

    QList<QWidget*> icons;
    icons << ui->reservationIcon << ui->clientIcon << ui->workIcon << ui->serviceIcon << ui->workersIcon << ui->settingsIcon;
    for(int i = 0; i < ui->tabWidget->count(); i++){
        connect(icons[i], SIGNAL(clicked(int)), icons[i], SLOT(toggleTab(int)));
    }
}

void GlowneOkno::dataLinkSwitch(int idx, QLabel *indicator) {
    ui->userDataSettingTab->setCurrentIndex(idx);
    this->clearIndicators();
    indicator->setStyleSheet("background-color: rgb(255,255,255)");
}

QString GlowneOkno::priceFormatter(QString price) {
    if(price.indexOf(",") != -1){
        price.replace(",",".");
    }
    return price;
}


GlowneOkno::~GlowneOkno()
{
    connection->CloseConnection();
    delete ui;
}
