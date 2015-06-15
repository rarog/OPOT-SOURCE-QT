#-------------------------------------------------
#
# Project created by QtCreator 2015-05-24T21:30:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OPOT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fileoverview.cpp

HEADERS  += mainwindow.h \
    fileoverview.h

FORMS    += mainwindow.ui \
    fileoverview.ui

TRANSLATIONS += translations/OPOT_de_DE.ts

DISTFILES += \
    translations/OPOT_de_DE.ts

RESOURCES += \
    res.qrc

CONFIG += c++11
