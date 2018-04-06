#ifndef LOGOWANIE_H
#define LOGOWANIE_H

#include <QMainWindow>
#include <QString>
#include <QtSql>
#include "sqlconnect.h"
#include "glowneokno.h"

namespace Ui {
class Logowanie;
}

class Logowanie : public QMainWindow
{
    Q_OBJECT
public:
    explicit Logowanie(QWidget *parent = 0);
    ~Logowanie();

private slots:
    void on_zalogujBTN_clicked();
    void on_anulujBTN_clicked();
private:
    Ui::Logowanie *ui;
    GlowneOkno *mainW;
    SqlConnect *login;
};

#endif // LOGOWANIE_H
