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
    explicit ClickableLabel(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~ClickableLabel();

signals:
    void clicked(int value);
public slots:
    void closeProgram(int flag);
    void toggleTab(int tabIndex);
protected:
    void mousePressEvent(QMouseEvent* event);
private:
    Logowanie *login;
};

#endif // CLICKABLELABEL_H
