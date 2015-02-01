#-------------------------------------------------
#
# Project created by QtCreator 2014-10-27T10:56:21
#
#-------------------------------------------------

QT       += core gui
QT += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = arduinoQt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    settingsdialog.cpp \
    aboutdialog.cpp \
    validateexp.cpp

HEADERS  += mainwindow.h \
    settingsdialog.h \
    aboutdialog.h \
    validateexp.h

FORMS    += mainwindow.ui \
    settingsdialog.ui \
    aboutdialog.ui

RESOURCES += \
    Icons.qrc
