#-------------------------------------------------
#
# Project created by QtCreator 2017-11-02T12:29:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = manager
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
        mainwindow.cpp \
    buy.cpp \
    addbuy.cpp \
    donation.cpp \
    fees.cpp \
    donate.cpp \
    buyediting.cpp \
    codeeditor.cpp \
    donateedite.cpp \
    instructions.cpp \
    statistic.cpp \
    popbuy.cpp \
    othforwhile.cpp

HEADERS += \
        mainwindow.h \
    buy.h \
    addbuy.h \
    donation.h \
    fees.h \
    donate.h \
    buyediting.h \
    codeeditor.h \
    donateedite.h \
    instructions.h \
    statistic.h \
    popbuy.h \
    othforwhile.h

FORMS += \
        mainwindow.ui \
    addbuy.ui \
    fees.ui \
    donate.ui \
    buyediting.ui \
    donateedite.ui \
    instructions.ui \
    statistic.ui \
    othforwhile.ui
