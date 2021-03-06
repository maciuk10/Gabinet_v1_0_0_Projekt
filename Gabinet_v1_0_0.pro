#-------------------------------------------------
#
# Project created by QtCreator 2018-03-09T11:08:46
#
#-------------------------------------------------

QT       += core gui sql charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Gabinet_v1_0_0
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        logowanie.cpp \
    glowneokno.cpp \
    sqlconnect.cpp \
    tablefiller.cpp \
    clickablelabel.cpp \
    usluga.cpp \
    osoba.cpp \
    pracownik.cpp \
    klient.cpp \
    data.cpp \
    wizyta.cpp \
    firma.cpp

HEADERS += \
        logowanie.h \
    glowneokno.h \
    sqlconnect.h \
    tablefiller.h \
    clickablelabel.h \
    usluga.h \
    osoba.h \
    pracownik.h \
    klient.h \
    data.h \
    wizyta.h \
    firma.h

FORMS += \
        logowanie.ui \
    glowneokno.ui

RESOURCES += \
    img.qrc
