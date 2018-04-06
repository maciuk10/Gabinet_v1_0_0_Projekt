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

    tableCreator = new TableFiller(connection->getSqlDatabaseObject(), ui->servicesServiceTable, QString("SELECT nazwa AS Nazwa, cena AS Cena, czas AS 'Czas wykonania', opis AS Opis FROM uslugi WHERE CONCAT(nazwa, cena, czas) LIKE '%"+ui->servicesServiceType->text()+"%'"));

    if(tableCreator->getcountOfRows() != -1){
        tableCreator->fillTheTable();
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
    QList<QLineEdit*> data = gb->findChildren<QLineEdit*>();
    for(int i = 0; i < data.length(); i++){
        data[i]->setText("");
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

bool GlowneOkno::areLineEditsValid(QGroupBox *gb) {
    bool empty = true;
    QList<QLineEdit*> fields = gb->findChildren<QLineEdit*>();
    foreach (QLineEdit* line, fields) {
        if(line->text() == ""){
            empty = false;
            return empty;
        }
    }
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
    WorkerID = index.model()->data(index.model()->index(index.row(), 0), Qt::DisplayRole).toInt();
    qDebug() << WorkerID;
    if(WorkerID > 0){
        connection = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
        connection->OpenConnection();
        tableCreator = new TableFiller(connection->getSqlDatabaseObject(), QString("SELECT pon_od, pon_do, wt_od, wt_do, sr_od, sr_do, cz_od, cz_do, pt_od, pt_do, so_od, so_do FROM godziny WHERE uzytkownik_id="+QString::number(WorkerID)));
        QStringList results = tableCreator->executeSelect();
        QList<QLineEdit*> hours = ui->workHoursFields->findChildren<QLineEdit*>();
        for(int i = 0; i < hours.length(); i++){
            hours[i]->setText(results[i]);
        }
        connection->CloseConnection();
        delete connection;
    }
}

void GlowneOkno::on_modifyWorkerBtn_clicked() {

}

void GlowneOkno::on_removeWorkerBtn_clicked() {

}

void GlowneOkno::on_clearFieldsWorkerBtn_clicked() {

}
