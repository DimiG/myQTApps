#-------------------------------------------------
#
# Project created by DimiG QtCreator 2015-02-13
# Copyright 2015 Dmitri G. <dimi615@pisem.net>
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmallVC
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RC_FILE = SmallVC.rc

RESOURCES += \
    pictures.qrc
