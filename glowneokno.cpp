#include "glowneokno.h"
#include "ui_glowneokno.h"


GlowneOkno::GlowneOkno(QWidget *parent, int userID) :
    QMainWindow(parent),
    ui(new Ui::GlowneOkno)
{
    this->userID = userID;
    ui->setupUi(this);
    ui->userDataSettingTab->setCurrentIndex(0);
    ui->userDataSettingTab->tabBar()->hide();
    ui->tabWidget->setCurrentIndex(0);
    ui->tabWidget->tabBar()->hide();

    this->setDefaultTableFormatting();

    this->prepareCharts();

    connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    connection->OpenConnection();

    TableFiller *clientFiller = new TableFiller(connection->getSqlDatabaseObject(), QString("SELECT nazwa, branza, email, adres, kod_pocztowy, miasto, wojewodztwo, kraj, nip  FROM info_o_firmie WHERE firma_id = 1"));
    QStringList companyData = clientFiller->executeSelect();
    QList<QLineEdit*> compData = ui->changeCompanyData->findChildren<QLineEdit*>();
    for(int i = 0; i < compData.length(); i++){
        compData[i]->setText(companyData[i]);
    }

    connection->CloseConnection();

    connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    connection->OpenConnection();

    TableFiller *changeSimpleData = new TableFiller(connection->getSqlDatabaseObject(), QString("SELECT uzytkownik_nazwa, uzytkownik_imie, uzytkownik_nazwisko FROM uzytkownik WHERE uzytkownik_id = "+QString::number(userID)));
    QStringList simpleData = changeSimpleData->executeSelect();
    QList<QLineEdit*> sData = ui->simpleDataGB->findChildren<QLineEdit*>();
    for(int i = 0; i < sData.length(); i++){
        sData[i]->setText(simpleData[i]);
    }
    connection->CloseConnection();

    connect(ui->logout, SIGNAL(clicked(int)), ui->logout, SLOT(closeProgram(int)));

    QList<QWidget*> icons;
    icons << ui->reservationIcon << ui->clientIcon << ui->workIcon << ui->serviceIcon << ui->workersIcon << ui->settingsIcon;
    for(int i = 0; i < ui->tabWidget->count(); i++){
        connect(icons[i], SIGNAL(clicked(int)), icons[i], SLOT(toggleTab(int)));
    }

    if(userID != 0){
        insertNames = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
        insertNames->OpenConnection();

        QSqlQuery *user = new QSqlQuery(insertNames->getSqlDatabaseObject());
        user->prepare("SELECT uzytkownik_imie AS imie, uzytkownik_nazwisko AS nazwisko FROM uzytkownik WHERE uzytkownik_id=:userid");
        user->bindValue(":userid", QString::number(userID));
        user->exec();

        QString workerName;
        QString workerPassword;
        while(user->next()){
            workerName = user->value(0).toString();
            workerPassword = user->value(1).toString();
        }

        this->setWindowTitle("Aplikacja Gabinet v1.0.0 @ Zalogowano: "+workerName+" "+workerPassword+"");
        ui->usernameProfile->setText("Witaj, "+workerName);
        insertNames->CloseConnection();
    }else {
        qApp->exit();
    }
}

GlowneOkno::~GlowneOkno()
{
    delete ui;
}

void GlowneOkno::on_reservationServiceSearch_clicked() {
    ui->serviceTable->setStyleSheet("border-image: none");
    connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    connection->OpenConnection();

    tableCreator = new TableFiller(connection->getSqlDatabaseObject(), ui->serviceTable, QString("SELECT nazwa AS Nazwa, cena AS Cena, czas AS 'Czas wykonania' FROM uslugi WHERE CONCAT(nazwa, cena, czas) LIKE '%"+ui->serviceReservationType->text()+"%'"));
    tableCreator->fillTheTable();
    delete tableCreator;

    connection->CloseConnection();
    delete connection;
}

void GlowneOkno::on_reservationClientSearch_clicked()
{
    ui->clientTable->setStyleSheet("border-image: none");
    connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    connection->OpenConnection();

    tableCreator = new TableFiller(connection->getSqlDatabaseObject(), ui->clientTable, QString("SELECT imie AS Imię, nazwisko AS Nazwisko FROM klienci WHERE CONCAT(imie, nazwisko) LIKE '%"+ui->clientReservationType->text()+"%'"));
    tableCreator->fillTheTable();
    delete tableCreator;
    connection->CloseConnection();
    delete connection;
}

void GlowneOkno::on_workerReservationSearch_clicked()
{
    ui->workerReservationTable->setStyleSheet("border-image: none");
    connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    connection->OpenConnection();

    tableCreator = new TableFiller(connection->getSqlDatabaseObject(), ui->workerReservationTable, QString("SELECT uzytkownik_nazwa AS ID, uzytkownik_imie AS Imię, uzytkownik_nazwisko AS Nazwisko FROM uzytkownik WHERE CONCAT(uzytkownik_nazwa, uzytkownik_imie, uzytkownik_nazwisko) LIKE '%"+ui->workerReservationType->text()+"%'"));
    tableCreator->fillTheTable();
    delete tableCreator;
    connection->CloseConnection();
    delete connection;
}

void GlowneOkno::on_clientSearch_Client_clicked() {
    ui->ClientsTable_Client->clearSelection();
    this->clearControlsFromCertainGroup(ui->clientData);
    ui->ClientsTable_Client->setStyleSheet("border-image: none");
    connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    connection->OpenConnection();

    tableCreator = new TableFiller(connection->getSqlDatabaseObject(), ui->ClientsTable_Client, QString("SELECT klienci_id AS ID, imie AS Imię, nazwisko AS Nazwisko, email AS 'E-mail', telefon AS Telefon, ulica AS Ulica, numer AS Numer, poczta AS Kod, miejscowosc AS Miejscowosc FROM klienci WHERE CONCAT(imie, nazwisko, email, telefon, ulica, miejscowosc, numer, poczta) LIKE '%"+ui->clientsClientType->text()+"%'"));
    if(tableCreator->getcountOfRows() != -1){
        tableCreator->fillTheTable();
    }else {
        qDebug() << "informacja o braku rekordów spełniających dane kryteria";
    }
    delete tableCreator;
    connection->CloseConnection();
    delete connection;
}

void GlowneOkno::on_workerWorkSearch_clicked() {
    ui->workersWorkTable->setStyleSheet("border-image: none");
    ui->addServiceWorkTable->setStyleSheet("border-image: none");
    ui->servicesWorkTable->setStyleSheet("border-image: none");
    connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    connection->OpenConnection();

    tableCreator = new TableFiller(connection->getSqlDatabaseObject(), ui->workersWorkTable, QString("SELECT uzytkownik_nazwa AS ID, uzytkownik_imie AS Imię, uzytkownik_nazwisko AS Nazwisko FROM uzytkownik WHERE CONCAT(uzytkownik_nazwa, uzytkownik_imie, uzytkownik_nazwisko) LIKE '%"+ui->workersWorkType->text()+"%'"));

    if(tableCreator->getcountOfRows() != -1){
        tableCreator->fillTheTable();
    }else {
        qDebug() << "informacja o braku rekordów spełniających dane kryteria";
    }
    delete tableCreator;
    connection->CloseConnection();
    delete connection;
}

void GlowneOkno::on_servicesServiceSearch_clicked() {
    ui->servicesServiceTable->setStyleSheet("border-image: none");
    connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    connection->OpenConnection();

    tableCreator = new TableFiller(connection->getSqlDatabaseObject(), ui->servicesServiceTable, QString("SELECT uslugi_id AS ID, nazwa AS Nazwa, cena AS Cena, czas AS 'Czas wykonania', opis AS Opis FROM uslugi WHERE CONCAT(nazwa, cena, czas) LIKE '%"+ui->servicesServiceType->text()+"%'"));

    if(tableCreator->getcountOfRows() != -1){
        tableCreator->fillTheTable();
        ui->servicesServiceTable->setColumnHidden(0,true);
    }else {
        qDebug() << "informacja o braku rekordów spełniających dane kryteria";
    }
    delete tableCreator;
    connection->CloseConnection();
    delete connection;
}

void GlowneOkno::on_workersWorkersSearch_clicked() {
    ui->workersWorkersTable->setStyleSheet("border-image: none");
    connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    connection->OpenConnection();

    tableCreator = new TableFiller(connection->getSqlDatabaseObject(), ui->workersWorkersTable, QString("SELECT uzytkownik_nazwa AS ID, uzytkownik_imie AS Imię, uzytkownik_nazwisko AS Nazwisko FROM uzytkownik WHERE CONCAT(uzytkownik_nazwa, uzytkownik_imie, uzytkownik_nazwisko) LIKE '%"+ui->workersWorkersType->text()+"%'"));

    if(tableCreator->getcountOfRows() != -1){
        tableCreator->fillTheTable();
    }else {
        qDebug() << "informacja o braku rekordów spełniających dane kryteria";
    }
    delete tableCreator;
    connection->CloseConnection();
    delete connection;
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

void GlowneOkno::setDefaultTableFormatting() {
    QList<QTableView*> tables = findChildren<QTableView*>();
    foreach (QTableView* t, tables) {
        t->horizontalHeader()->setStretchLastSection(true);
        t->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        t->setSelectionBehavior(QAbstractItemView::SelectRows);
        t->verticalHeader()->hide();
    }
}

void GlowneOkno::on_userDataLink_clicked() {
    ui->userDataSettingTab->setCurrentIndex(0);
    clearIndicators();
    ui->setDataIndicator->setStyleSheet("background-color: rgb(255,255,255)");
}

void GlowneOkno::on_companyDataLink_clicked() {
    ui->userDataSettingTab->setCurrentIndex(1);
    clearIndicators();
    ui->companyIndicator->setStyleSheet("background-color: rgb(255,255,255)");
}

void GlowneOkno::on_showStatsLink_clicked() {
    ui->userDataSettingTab->setCurrentIndex(2);
    clearIndicators();
    ui->showStatsIndicator->setStyleSheet("background-color: rgb(255,255,255)");
}

void GlowneOkno::on_setLeaveLink_clicked() {
    ui->userDataSettingTab->setCurrentIndex(3);
    clearIndicators();
    ui->leaveIndicator->setStyleSheet("background-color: rgb(255,255,255)");
}

void GlowneOkno::on_changePasswordLink_clicked() {
    ui->userDataSettingTab->setCurrentIndex(4);
    clearIndicators();
    ui->changePasswordIndicator->setStyleSheet("background-color: rgb(255,255,255)");
}

void GlowneOkno::on_workersWorkTable_clicked(const QModelIndex &index) {
    QStringList workersData;
    for(int i = 0; i < index.model()->columnCount(); i++){
        workersData << index.model()->data(index.model()->index(index.row(), i), Qt::DisplayRole).toString();
    }

    QString val = ui->workersWorkTable->model()->data(index).toString();
    qDebug() << val;
    ui->workidEdit->setText(workersData[0]);
    ui->workNameEdit->setText(workersData[1]);
    ui->workSurnameEdit->setText(workersData[2]);
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
        connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
        connection->OpenConnection();
        tableCreator = new TableFiller(connection->getSqlDatabaseObject(), QString("INSERT INTO klienci (imie, nazwisko, email, telefon, ulica, numer, miejscowosc, poczta) VALUES ('"+ui->clientNameEdit->text()+"','"+ui->clientSurnameEdit->text()+"','"+ui->clientEmailEdit->text()+"','"+ui->clientPhoneEdit->text()+"','"+ui->clientStreetLine->text()+"','"+ui->clientStrNoLine->text()+"','"+ui->clientCityLine->text()+"','"+ui->clientCodeLine->text()+"')"));
        if(tableCreator->executeInsertUpdateDelete()) {
            QMessageBox::information(this, "Dodanie klienta", "Pomyślnie dodano klienta do bazy danych", QMessageBox::Ok);
            clearControlsFromCertainGroup(ui->clientData);
            ui->ClientsTable_Client->clearSelection();
            TableFiller *clientFiller = new TableFiller(connection->getSqlDatabaseObject(), ui->ClientsTable_Client, QString("SELECT klienci_id AS ID, imie AS Imię, nazwisko AS Nazwisko, email AS 'E-mail', telefon AS Telefon, ulica AS Ulica, numer AS Numer, poczta AS Kod, miejscowosc AS Miejscowosc FROM klienci WHERE CONCAT(imie, nazwisko, email, telefon, ulica, miejscowosc, numer, poczta) LIKE '%"+ui->clientsClientType->text()+"%'"));
            clientFiller->fillTheTable();
            delete clientFiller;
        }else {
            QMessageBox::warning(this, "Błąd wewnętrzny", "Nie udało się dodać klienta do bazy. W celu uzyskania informacji skontaktuj się z twórcą oprogramowania. Kod błędu: WEW001", QMessageBox::Ok);
        }
        delete tableCreator;
        connection->CloseConnection();
        delete connection;
    }else {
        QMessageBox::warning(this, "Wypełnij pola formularza", "Wymagania walidacyjne formularza nie zostały spełnione", QMessageBox::Ok);
    }
}

void GlowneOkno::on_clientModifyBtn_clicked() {
    bool valid = areLineEditsValid(ui->clientData);
    if(valid && ClientID > 0){
        connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
        connection->OpenConnection();
        tableCreator = new TableFiller(connection->getSqlDatabaseObject(), QString("UPDATE klienci SET imie='"+ui->clientNameEdit->text()+"', nazwisko='"+ui->clientSurnameEdit->text()+"', email='"+ui->clientEmailEdit->text()+"', telefon='"+ui->clientPhoneEdit->text()+"', ulica='"+ui->clientStreetLine->text()+"', numer='"+ui->clientStrNoLine->text()+"', miejscowosc='"+ui->clientCityLine->text()+"', poczta='"+ui->clientCodeLine->text()+"' WHERE klienci_id="+QString::number(ClientID)));
        tableCreator->executeInsertUpdateDelete();
        QMessageBox::information(this, "Modyfikacja klienta", "Pomyślnie zmodyfikowano dane klienta z bazy danych", QMessageBox::Ok);
        clearControlsFromCertainGroup(ui->clientData);
        ui->ClientsTable_Client->clearSelection();
        TableFiller *clientFiller = new TableFiller(connection->getSqlDatabaseObject(), ui->ClientsTable_Client, QString("SELECT klienci_id AS ID, imie AS Imię, nazwisko AS Nazwisko, email AS 'E-mail', telefon AS Telefon, ulica AS Ulica, numer AS Numer, poczta AS Kod, miejscowosc AS Miejscowosc FROM klienci WHERE CONCAT(imie, nazwisko, email, telefon, ulica, miejscowosc, numer, poczta) LIKE '%"+ui->clientsClientType->text()+"%'"));
        clientFiller->fillTheTable();
        delete clientFiller;
        connection->CloseConnection();
        delete connection;
    }else {
        QMessageBox::warning(this, "Wypełnij pola formularza", "Wymagania walidacyjne formularza nie zostały spełnione", QMessageBox::Ok);
    }
}

void GlowneOkno::on_clientRemoveBtn_clicked() {
    if(ClientID > 0){
        connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
        connection->OpenConnection();
        tableCreator = new TableFiller(connection->getSqlDatabaseObject(), QString("DELETE FROM klienci WHERE klienci_id ="+QString::number(ClientID)));
        tableCreator->executeInsertUpdateDelete();
        QMessageBox::information(this, "Usunięcie klienta", "Pomyślnie usunięto dane klienta z bazy danych", QMessageBox::Ok);
        clearControlsFromCertainGroup(ui->clientData);
        ui->ClientsTable_Client->clearSelection();
        TableFiller *clientFiller = new TableFiller(connection->getSqlDatabaseObject(), ui->ClientsTable_Client, QString("SELECT klienci_id AS ID, imie AS Imię, nazwisko AS Nazwisko, email AS 'E-mail', telefon AS Telefon, ulica AS Ulica, numer AS Numer, poczta AS Kod, miejscowosc AS Miejscowosc FROM klienci WHERE CONCAT(imie, nazwisko, email, telefon, ulica, miejscowosc, numer, poczta) LIKE '%"+ui->clientsClientType->text()+"%'"));
        clientFiller->fillTheTable();
        delete clientFiller;
        connection->CloseConnection();
        delete connection;
    }
    ClientID = 0;
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


void GlowneOkno::on_workersWorkersTable_clicked(const QModelIndex &index) {
    QList<QLineEdit*> clientData = ui->workersEditFields->findChildren<QLineEdit*>();
    for(int i = 0; i < clientData.length(); i++){
        clientData[i]->setText(index.model()->data(index.model()->index(index.row(), clientData.length() - i - 1), Qt::DisplayRole).toString());
    }
    WorkerID = index.model()->data(index.model()->index(index.row(), 0), Qt::DisplayRole).toString();
    if(WorkerID != ""){
        connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
        connection->OpenConnection();
        tableCreator = new TableFiller(connection->getSqlDatabaseObject(), QString("SELECT pon_od, pon_do, wt_od, wt_do, sr_od, sr_do, cz_od, cz_do, pt_od, pt_do, so_od, so_do FROM godziny, uzytkownik WHERE godziny.uzytkownik_id = uzytkownik.uzytkownik_id AND uzytkownik.uzytkownik_nazwa='"+WorkerID+"'"));
        QStringList results = tableCreator->executeSelect();
        QList<QLineEdit*> hours = ui->workerHours->findChildren<QLineEdit*>();
        for(int i = 0; i < hours.length(); i++){
            hours[i]->setText(results[i]);
        }
        connection->CloseConnection();
        delete connection;
        this->clearControlsFromCertainGroup(ui->hoursSchema);
    }
}

void GlowneOkno::on_modifyWorkerBtn_clicked() {
    bool valid = areLineEditsValid(ui->workersEditFields) && areLineEditsValid(ui->workerHours);

    if(valid && WorkerID != ""){
        connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
        connection->OpenConnection();
        tableCreator = new TableFiller(connection->getSqlDatabaseObject(), QString("UPDATE uzytkownik SET uzytkownik_nazwa='"+ui->workerIDEdit->text()+"', uzytkownik_imie='"+ui->workerNameEdit->text()+"', uzytkownik_nazwisko='"+ui->workerSurnameEdit->text()+"' WHERE uzytkownik_nazwa='"+WorkerID+"'"));
        tableCreator->executeInsertUpdateDelete();
        TableFiller *getID = new TableFiller(connection->getSqlDatabaseObject(), QString("SELECT uzytkownik_id FROM uzytkownik WHERE uzytkownik_nazwa='"+ui->workerIDEdit->text()+"'"));
        QStringList idvalue = getID->executeSelect();

        TableFiller *updateHours = new TableFiller(connection->getSqlDatabaseObject(), QString("UPDATE godziny SET pon_od='"+ui->ponod->text()+"', pon_do='"+ui->pondo->text()+"', wt_od='"+ui->wtod->text()+"', wt_do='"+ui->wtdo->text()+"', sr_od='"+ui->srod->text()+"', sr_do='"+ui->srdo->text()+"', cz_od='"+ui->czod->text()+"', cz_do='"+ui->czdo->text()+"', pt_od='"+ui->ptod->text()+"', pt_do='"+ui->ptdo->text()+"', so_od='"+ui->sood->text()+"', so_do='"+ui->sodo->text()+"' WHERE uzytkownik_id="+idvalue[0]));
        updateHours->executeInsertUpdateDelete();
        QMessageBox::information(this, "Modyfikacja pracownika", "Pomyślnie zmodyfikowano dane pracownika z bazy danych", QMessageBox::Ok);
        clearControlsFromCertainGroup(ui->clientData);
        ui->ClientsTable_Client->clearSelection();

        WorkerID = ui->workerIDEdit->text();

        TableFiller *clientFiller = new TableFiller(connection->getSqlDatabaseObject(), ui->workersWorkersTable, QString("SELECT uzytkownik_nazwa AS ID, uzytkownik_imie AS Imię, uzytkownik_nazwisko AS Nazwisko FROM uzytkownik WHERE CONCAT(uzytkownik_nazwa, uzytkownik_imie, uzytkownik_nazwisko) LIKE '%"+ui->workersWorkersType->text()+"%'"));
        clientFiller->fillTheTable();
        TableFiller *showHours = new TableFiller(connection->getSqlDatabaseObject(), QString("SELECT pon_od, pon_do, wt_od, wt_do, sr_od, sr_do, cz_od, cz_do, pt_od, pt_do, so_od, so_do FROM godziny, uzytkownik WHERE godziny.uzytkownik_id = uzytkownik.uzytkownik_id AND uzytkownik.uzytkownik_nazwa='"+WorkerID+"'"));

        QStringList results = showHours->executeSelect();
        QList<QLineEdit*> hours = ui->workerHours->findChildren<QLineEdit*>();
        for(int i = 0; i < hours.length(); i++){
            hours[i]->setText(results[i]);
        }

        //delete clientFiller;
        connection->CloseConnection();
        //delete connection;
        ui->workersWorkersTable->clearSelection();
        this->clearControlsFromCertainGroup(ui->workersEditFields);
        this->clearControlsFromCertainGroup(ui->workHoursFields);
    }else {
        QMessageBox::warning(this, "Wypełnij pola formularza", "Wymagania walidacyjne formularza nie zostały spełnione", QMessageBox::Ok);
    }
}

void GlowneOkno::on_removeWorkerBtn_clicked() {
    if(WorkerID != ""){
        connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
        connection->OpenConnection();
        tableCreator = new TableFiller(connection->getSqlDatabaseObject(), QString("DELETE FROM uzytkownik WHERE uzytkownik_nazwa='"+WorkerID+"'"));
        tableCreator->executeInsertUpdateDelete();
        QMessageBox::information(this, "Usunięcie pracownika", "Pomyślnie usunięto dane pracownika z bazy danych", QMessageBox::Ok);
        clearControlsFromCertainGroup(ui->clientData);
        ui->ClientsTable_Client->clearSelection();

        TableFiller *clientFiller = new TableFiller(connection->getSqlDatabaseObject(), ui->workersWorkersTable, QString("SELECT uzytkownik_nazwa AS ID, uzytkownik_imie AS Imię, uzytkownik_nazwisko AS Nazwisko FROM uzytkownik WHERE CONCAT(uzytkownik_nazwa, uzytkownik_imie, uzytkownik_nazwisko) LIKE '%"+ui->workersWorkersType->text()+"%'"));
        clientFiller->fillTheTable();
        delete clientFiller;
        connection->CloseConnection();
        delete connection;
        ui->workersWorkersTable->clearSelection();
        this->clearControlsFromCertainGroup(ui->workersEditFields);
        this->clearControlsFromCertainGroup(ui->workHoursFields);
    }
    WorkerID = "";
}

void GlowneOkno::on_clearFieldsWorkerBtn_clicked() {
    ui->workersWorkersTable->clearSelection();
    this->clearControlsFromCertainGroup(ui->workersEditFields);
    this->clearControlsFromCertainGroup(ui->workHoursFields);
    WorkerID = "";
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

    if(valid && WorkerID == ""){
        connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
        connection->OpenConnection();
        tableCreator = new TableFiller(connection->getSqlDatabaseObject(), QString("INSERT INTO uzytkownik(uzytkownik_nazwa, uzytkownik_imie, uzytkownik_nazwisko, haslo, pracownik) VALUES ('"+ui->workerIDEdit->text()+"', '"+ui->workerNameEdit->text()+"', '"+ui->workerSurnameEdit->text()+"', PASSWORD('"+ui->workerIDEdit->text()+"'), '1')"));
        tableCreator->executeInsertUpdateDelete();
        TableFiller *getID = new TableFiller(connection->getSqlDatabaseObject(), QString("SELECT uzytkownik_id FROM uzytkownik WHERE uzytkownik_nazwa='"+ui->workerIDEdit->text()+"'"));
        QStringList idvalue = getID->executeSelect();
        qDebug() << idvalue[0];
        qDebug() << "Jest OK";
        TableFiller *updateHours = new TableFiller(connection->getSqlDatabaseObject(), QString("INSERT INTO godziny(uzytkownik_id, pon_od, pon_do, wt_od, wt_do, sr_od, sr_do, cz_od, cz_do, pt_od, pt_do, so_od, so_do) VALUES ('"+idvalue[0]+"','"+ui->ponod->text()+"','"+ui->pondo->text()+"','"+ui->wtod->text()+"','"+ui->wtdo->text()+"','"+ui->srod->text()+"','"+ui->srdo->text()+"','"+ui->czod->text()+"','"+ui->czdo->text()+"','"+ui->ptod->text()+"','"+ui->ptdo->text()+"','"+ui->sood->text()+"','"+ui->sodo->text()+"')"));
        updateHours->executeInsertUpdateDelete();
        QMessageBox::information(this, "Dodanie pracownika", "Pomyślnie dodano dane pracownika do bazy danych", QMessageBox::Ok);
        clearControlsFromCertainGroup(ui->clientData);
        ui->ClientsTable_Client->clearSelection();


        TableFiller *clientFiller = new TableFiller(connection->getSqlDatabaseObject(), ui->workersWorkersTable, QString("SELECT uzytkownik_nazwa AS ID, uzytkownik_imie AS Imię, uzytkownik_nazwisko AS Nazwisko FROM uzytkownik WHERE CONCAT(uzytkownik_nazwa, uzytkownik_imie, uzytkownik_nazwisko) LIKE '%"+ui->workersWorkersType->text()+"%'"));
        clientFiller->fillTheTable();
        ui->workersWorkersTable->setStyleSheet("border-image: none");
        TableFiller *showHours = new TableFiller(connection->getSqlDatabaseObject(), QString("SELECT pon_od, pon_do, wt_od, wt_do, sr_od, sr_do, cz_od, cz_do, pt_od, pt_do, so_od, so_do FROM godziny, uzytkownik WHERE godziny.uzytkownik_id = uzytkownik.uzytkownik_id AND uzytkownik.uzytkownik_nazwa='"+ui->workerIDEdit->text()+"'"));

        QStringList results = showHours->executeSelect();
        QList<QLineEdit*> hours = ui->workerHours->findChildren<QLineEdit*>();
        for(int i = 0; i < hours.length(); i++){
            hours[i]->setText(results[i]);
        }

        //delete clientFiller;
        connection->CloseConnection();
        //delete connection;
        ui->workersWorkersTable->clearSelection();
        this->clearControlsFromCertainGroup(ui->workersEditFields);
        this->clearControlsFromCertainGroup(ui->workHoursFields);
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
    qDebug() << ServiceID;

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
        connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
        connection->OpenConnection();
        tableCreator = new TableFiller(connection->getSqlDatabaseObject(), QString("DELETE FROM uslugi WHERE uslugi_id='"+QString::number(ServiceID)+"'"));
        tableCreator->executeInsertUpdateDelete();
        QMessageBox::information(this, "Usunięcie usługi", "Pomyślnie usunięto dane usługi z bazy danych", QMessageBox::Ok);
        ui->servicesServiceTable->clearSelection();
        TableFiller *clientFiller = new TableFiller(connection->getSqlDatabaseObject(), ui->servicesServiceTable, QString("SELECT uslugi_id AS ID, nazwa AS Nazwa, cena AS Cena, czas AS 'Czas wykonania', opis AS Opis FROM uslugi WHERE CONCAT(nazwa, cena, czas) LIKE '%"+ui->servicesServiceType->text()+"%'"));
        clientFiller->fillTheTable();
        connection->CloseConnection();
        ui->servicesServiceTable->clearSelection();
        this->clearControlsFromCertainGroup(ui->serviceData);
    }
    ServiceID = 0;
}

void GlowneOkno::on_serviceModifyBtn_clicked() {
    bool valid = areLineEditsValid(ui->serviceData) && areTextEditsValid(ui->serviceData);
    if(valid && ServiceID > 0){
        connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
        connection->OpenConnection();
        if(ui->servicePrice->text().indexOf(",") != -1){
            QString price = ui->servicePrice->text();
            price.replace(",", ".");
            ui->servicePrice->setText(price);
        }
        tableCreator = new TableFiller(connection->getSqlDatabaseObject(), QString("UPDATE uslugi SET nazwa='"+ui->serviceName->text()+"', cena='"+ui->servicePrice->text()+"', czas='"+ui->serviceTime->text()+"', opis='"+ui->serviceDesc->toPlainText()+"' WHERE uslugi_id='"+QString::number(ServiceID)+"'"));
        tableCreator->executeInsertUpdateDelete();
        QMessageBox::information(this, "Modyfikacja usługi", "Pomyślnie zmodyfikowano dane usługi z bazy danych", QMessageBox::Ok);
        TableFiller *clientFiller = new TableFiller(connection->getSqlDatabaseObject(), ui->servicesServiceTable, QString("SELECT uslugi_id AS ID, nazwa AS Nazwa, cena AS Cena, czas AS 'Czas wykonania', opis AS Opis FROM uslugi WHERE CONCAT(nazwa, cena, czas) LIKE '%"+ui->servicesServiceType->text()+"%'"));
        clientFiller->fillTheTable();
        connection->CloseConnection();
        ui->servicesServiceTable->clearSelection();
        this->clearControlsFromCertainGroup(ui->serviceData);
    }
    ServiceID = 0;
}

void GlowneOkno::on_serviceAddBtn_clicked() {
    bool valid = areLineEditsValid(ui->serviceData) && areTextEditsValid(ui->serviceData);
    if(valid && ServiceID == 0){
        connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
        connection->OpenConnection();
        if(ui->servicePrice->text().indexOf(",") != -1){
            QString price = ui->servicePrice->text();
            price.replace(",", ".");
            ui->servicePrice->setText(price);
        }
        tableCreator = new TableFiller(connection->getSqlDatabaseObject(), QString("INSERT INTO uslugi(nazwa, cena, czas, opis) VALUES ('"+ui->serviceName->text()+"','"+ui->servicePrice->text()+"','"+ui->serviceTime->text()+"','"+ui->serviceDesc->toPlainText()+"')"));
        tableCreator->executeInsertUpdateDelete();
        QMessageBox::information(this, "Dodanie usługi", "Pomyślnie dodano dane usługi do bazy danych", QMessageBox::Ok);
        TableFiller *clientFiller = new TableFiller(connection->getSqlDatabaseObject(), ui->servicesServiceTable, QString("SELECT uslugi_id AS ID, nazwa AS Nazwa, cena AS Cena, czas AS 'Czas wykonania', opis AS Opis FROM uslugi WHERE CONCAT(nazwa, cena, czas) LIKE '%"+ui->servicesServiceType->text()+"%'"));
        clientFiller->fillTheTable();
        connection->CloseConnection();
        ui->servicesServiceTable->clearSelection();
        this->clearControlsFromCertainGroup(ui->serviceData);
    }
}

void GlowneOkno::on_changeCompanyInfo_clicked() {
    bool valid = areLineEditsValid(ui->changeCompanyData);
    if(valid){
        connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
        connection->OpenConnection();
        tableCreator = new TableFiller(connection->getSqlDatabaseObject(), QString("UPDATE info_o_firmie SET  nazwa='"+ui->compName->text()+"', branza='"+ui->compCat->text()+"', email='"+ui->comMail->text()+"', adres='"+ui->compAdr->text()+"', kod_pocztowy='"+ui->compCode->text()+"', miasto='"+ui->compCity->text()+"', wojewodztwo='"+ui->compVoivode->text()+"', kraj='"+ui->compCntry->text()+"', nip='"+ui->nip->text()+"' WHERE firma_id = 1"));
        tableCreator->executeInsertUpdateDelete();
        QMessageBox::information(this, "Zmiana danych firmy", "Pomyślnie zmodyfikowano dane firmy z bazy danych", QMessageBox::Ok);
        TableFiller *company = new TableFiller(connection->getSqlDatabaseObject(), QString("SELECT * FROM info_o_firmie"));
        QStringList companyData = company->executeSelect();
        QList<QLineEdit*> companyList = ui->changeCompanyData->findChildren<QLineEdit*>();
        for(int i = 0; i < companyList.length(); i++){
            companyList[i]->setText(companyData[i+1]);
        }
    }
}

void GlowneOkno::on_simpleDataChange_clicked() {
    bool valid = areLineEditsValid(ui->simpleDataGB);
    if(valid){
        connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
        connection->OpenConnection();
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
        connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
        connection->OpenConnection();
        tableCreator = new TableFiller(connection->getSqlDatabaseObject(), QString("UPDATE uzytkownik SET haslo=PASSWORD('"+ui->newPass->text()+"') WHERE uzytkownik_id="+QString::number(userID)));
        tableCreator->executeInsertUpdateDelete();
        if (tableCreator->getcountOfRows() <= 0){
            QMessageBox::warning(this, "Zmiana hasła użytkownika", "Pomyślnie zmodyfikowano hasło użytkownika w bazie danych. Aby zobaczyć zmiany należy sie ponownie zalogować", QMessageBox::Ok);
            clearControlsFromCertainGroup(ui->changePasswordGB);
        }
        connection->CloseConnection();
    }
}
