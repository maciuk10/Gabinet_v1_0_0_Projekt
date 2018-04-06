#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {
}

ClickableLabel::~ClickableLabel() {}

void ClickableLabel::mousePressEvent(QMouseEvent *event){
    emit clicked(this->statusTip().toInt());
}

void ClickableLabel::closeProgram(int flag) {
    flag = 0;
    login = new Logowanie(nullptr);
    QWidget *activeWindow = QApplication::activeWindow();
    activeWindow->hide();
    login->show();
}

void ClickableLabel::toggleTab(int tabIndex) {
    GlowneOkno *okno = dynamic_cast<GlowneOkno*>(QApplication::activeWindow());
    okno->setCurrentTab(tabIndex);
}
