#ifndef GLOWNEOKNO_H
#define GLOWNEOKNO_H

#include <QMainWindow>
#include <QtSql>
#include <typeinfo>
#include <QGroupBox>
#include "sqlconnect.h"
#include "tablefiller.h"
#include <QMessageBox>
#include <QtCharts>

namespace Ui {
class GlowneOkno;
}

class GlowneOkno : public QMainWindow
{
    Q_OBJECT

public:
    explicit GlowneOkno(QWidget *parent = 0, int userID = 0);
    ~GlowneOkno();
    void setCurrentTab(int tabIndex);
    void clearIndicators();
    void setDefaultTableFormatting();
    void clearControlsFromCertainGroup(QGroupBox *gb);
    bool areLineEditsValid(QGroupBox *gb);
    bool areTextEditsValid(QGroupBox *gb);
    void prepareCharts();
    bool validHourRange(QString from, QString to);
    void setHourSchema(QString from, QString to, QGroupBox *gb);
    void generateDailySchedule(QString hourFrom, QString hourTo);
    void clearWidgets(QLayout *layout);
    QString giveDays();



private slots:
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

private:
    Ui::GlowneOkno *ui;
    QSqlQuery *serviceTableQuery;
    SqlConnect *connection;
    SqlConnect *insertNames;
    TableFiller *tableCreator;
    QSqlQueryModel *model;
    int userID;
    int ClientID;
    int ServiceID;
    QString WorkerID;
    QStringList currentid;
    QStringList currentServices;
    bool alreadyActivated = false;

};

#endif // GLOWNEOKNO_H
