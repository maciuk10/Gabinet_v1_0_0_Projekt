#ifndef GLOWNEOKNO_H
#define GLOWNEOKNO_H

#include <QMainWindow>
#include <QtSql>
#include <typeinfo>
#include <QGroupBox>
#include <QMessageBox>
#include <QtCharts>

#include "sqlconnect.h"
#include "tablefiller.h"
#include "data.h"
#include "osoba.h"
#include "usluga.h"
#include "wizyta.h"
#include "firma.h"

namespace Ui {
class GlowneOkno;
}

class GlowneOkno : public QMainWindow
{
    Q_OBJECT

public:
    explicit GlowneOkno(QWidget *parent = 0, int userID = 0, SqlConnect *conn = nullptr); // dostaje od okienka logowanie wartosc USERID dzięki której wie jaki użytkownik jest aktualnie zalogowany (inicjalizuje połączenie z bazą danych)
    ~GlowneOkno();                                                              //zamyka połączenie z bazą danych
    void setCurrentTab(int tabIndex);                                           //pozwala na przełączanie pomiędzy zakładkami głównego widgetu
    void clearIndicators();                                                     //odpowiada za wyczyszczenie formatowania zakładek w wybranym panelu (ustawienia)
    void setDefaultWidgetFormatting();                                          //globalne formatowanie wyglądu tabel oraz innych używanych widgetów
    void clearControlsFromCertainGroup(QGroupBox *gb);                          //wyczyszczenie zawartości pól tekstowych dla danej grupy pól
    bool areLineEditsValid(QGroupBox *gb);                                      //walidacja pól tekstowych z danej grupy pól
    bool areTextEditsValid(QGroupBox *gb);                                      //walidacja pól wieloliniowych z danej grupy pól
    void prepareCharts();                                                       //tworzenie wykresów dla "Pokaż statystyki" w zakładce ustawienia
    bool validHourRange(QString from, QString to);                              //sprawdzenie poprawności zakresu godzin pracownika
    void setHourSchema(QString from, QString to, QGroupBox *gb);                //ustawienie wybranego schematu godzin do pól tekstowych
    void generateDailySchedule(QString hourFrom, QString hourTo);               //generowanie interfejsu godzin dla danego pracownika
    void clearWidgets(QLayout *layout);                                         //usunięcie wszystkich kontrolek dla danego layoutu
    QString giveDays();                                                         //zwrócenie krótkiej nazwy dla aktualnej daty
    void dataLinkSwitch(int idx, QLabel *indicator);                            //przełączanie pomiędzy przyciskami na panelu ustawienia


private slots:
    //sloty - definicje funkcji typu eventListener tworzone według schematu on_kontrolka_sygnał dzięki macro Q_OBJECT
    void on_reservationServiceSearch_clicked();
    void on_reservationClientSearch_clicked();
    void on_workerReservationSearch_clicked();
    void on_clientSearch_Client_clicked();
    void on_workerWorkSearch_clicked();
    void on_servicesServiceSearch_clicked();
    void on_workersWorkersSearch_clicked();
    void on_userDataLink_clicked();
    void on_companyDataLink_clicked();
    void on_showStatsLink_clicked();
    void on_setLeaveLink_clicked();
    void on_changePasswordLink_clicked();
    void on_workersWorkTable_clicked(const QModelIndex &index);
    void on_ClientsTable_Client_clicked(const QModelIndex &index);
    void on_clearClients_clicked();
    void on_addClientBtn_clicked();
    void on_clientModifyBtn_clicked();
    void on_clientRemoveBtn_clicked();
    void on_workersWorkersTable_clicked(const QModelIndex &index);
    void on_modifyWorkerBtn_clicked();
    void on_removeWorkerBtn_clicked();
    void on_clearFieldsWorkerBtn_clicked();
    void on_toolButton_clicked();
    void on_addWorkerBtn_clicked();
    void on_schemaOne_clicked();
    void on_schemaTwo_clicked();
    void on_schemaThree_clicked();
    void on_schemaFour_clicked();
    void on_servicesServiceTable_clicked(const QModelIndex &index);
    void on_serviceClearBtn_clicked();
    void on_serviceRemoveBtn_clicked();
    void on_serviceModifyBtn_clicked();
    void on_serviceAddBtn_clicked();
    void on_changeCompanyInfo_clicked();
    void on_simpleDataChange_clicked();
    void on_changePasswordBtn_clicked();
    void on_addServiceWorkTable_doubleClicked(const QModelIndex &index);
    void on_workerReservationTable_clicked(const QModelIndex &index);
    void on_calendarWidget_clicked(const QDate &date);
    void on_servicesWorkTable_doubleClicked(const QModelIndex &index);
    void on_serviceTable_clicked(const QModelIndex &index);
    void on_clientTable_clicked(const QModelIndex &index);
    void chooseHourFromList(QPushButton* push);
    void on_tabWidget_currentChanged(int index);

private:
    //instancje obiektów klas biblioteki qt oraz typów wbudowanych
    Ui::GlowneOkno *ui;
    QSqlQuery *serviceTableQuery;
    QSqlQueryModel *model;
    int userID;
    int ClientID;
    int ServiceID;
    int WorkerID;
    QStringList currentid;
    QStringList currentServices;
    bool alreadyActivated = false;

    //instancje obiektów klas własnych
    TableFiller *tableCreator;
    SqlConnect *connection;
    SqlConnect *insertNames;
    Data *rezerwacjaOd;
    Data *rezerwacjaDo;
    Pracownik *pracownik;
    Klient *klient;
    Firma *firma;
    Usluga *usluga;
};
#endif // GLOWNEOKNO_H
