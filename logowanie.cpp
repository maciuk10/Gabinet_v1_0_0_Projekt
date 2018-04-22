#include "logowanie.h"
#include "ui_logowanie.h"

Logowanie::Logowanie(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Logowanie)
{
    login = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    login->OpenConnection();
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    this->setFixedSize(size());
}

void Logowanie::on_zalogujBTN_clicked() {
    executeQuery = new TableFiller(login->getSqlDatabaseObject(), QString("SELECT uzytkownik_id FROM uzytkownik WHERE uzytkownik_nazwa='"+ui->workerID->text()+"' AND haslo=PASSWORD('"+ui->workerPassword->text()+"')"));
    QStringList user = executeQuery->executeSelect();
    int rows = executeQuery->getcountOfRows();
    int userID;
    if(rows == 1){
        userID = user[0].toInt();
    }else {
        userID = 0;
    }

    if(rows == 1){
        mainW = new GlowneOkno(this, userID, login);
        this->hide();
        mainW->show();
    }else {
        ui->wrongPasswordLabel->setText("Błąd logowania: Nieprawidłowy login lub hasło");
    }
}

void Logowanie::on_anulujBTN_clicked() {
    qApp->exit();
}

Logowanie::~Logowanie()
{
    delete ui;
}
