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
    void prepareCharts();

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

private:
    Ui::GlowneOkno *ui;
    QSqlQuery *serviceTableQuery;
    SqlConnect *connection;
    SqlConnect *insertNames;
    TableFiller *tableCreator;
    QSqlQueryModel *model;
    int userID;
    int ClientID;
    QString WorkerID;
};

#endif // GLOWNEOKNO_H
