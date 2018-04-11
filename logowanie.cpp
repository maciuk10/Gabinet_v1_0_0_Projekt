#include "logowanie.h"
#include "ui_logowanie.h"

Logowanie::Logowanie(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Logowanie)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    this->setFixedSize(size());
}

Logowanie::~Logowanie()
{
    delete ui;
}

void Logowanie::on_zalogujBTN_clicked() {
    login = new SqlConnect("localhost", "gabinet", "root", "zaq1@WSX", 9999);
    login->OpenConnection();

    QSqlQuery *user = new QSqlQuery(login->getSqlDatabaseObject());
    user->prepare("SELECT uzytkownik_id FROM uzytkownik WHERE uzytkownik_nazwa=:workerID AND haslo=PASSWORD(:workerPassword)");
    user->bindValue(":workerID", ui->workerID->text());
    user->bindValue(":workerPassword", ui->workerPassword->text());
    user->exec();
    int rows = user->size();
    int userID;
    if(rows == 1){
        while(user->next()){
            userID = user->value(0).toInt();
        }
    }else {
        userID = 0;
    }
    login->CloseConnection();

    if(rows == 1){
        mainW = new GlowneOkno(nullptr, userID);
        mainW->show();
        this->hide();
    }else {
        ui->wrongPasswordLabel->setText("Błąd logowania: Nieprawidłowy login lub hasło");
    }
}

void Logowanie::on_anulujBTN_clicked() {
    qApp->exit();
}
