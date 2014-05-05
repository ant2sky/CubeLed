#-------------------------------------------------
#
# Project created by QtCreator 2014-02-02T23:15:46
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CubeLedManager
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    DataFormat.h \
    Communication.h

FORMS    += mainwindow.ui
