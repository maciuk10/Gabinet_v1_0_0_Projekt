#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QMainWindow>
#include <QObject>
#include <QLabel>
#include <QWidget>
#include <Qt>
#include <QDebug>
#include <QApplication>
#include "logowanie.h"
#include "glowneokno.h"

namespace Ui {
class GlowneOkno;
}

class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClickableLabel(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());  //konstruktor dziedziczący po QLabel
    ~ClickableLabel();

signals:
    void clicked(int value); //emituje sygnał kliknięcia podczas mousePressEvent
public slots:
    void closeProgram(int flag);    //zamyka program
    void toggleTab(int tabIndex);   //przełącza pomiędzy zakładkami programu
protected:
    void mousePressEvent(QMouseEvent* event);   //zdarzenie kliknięcia na obiekt
private:
    Logowanie *login;
};

#endif // CLICKABLELABEL_H
