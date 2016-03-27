#-------------------------------------------------
#
# Project created by QtCreator 2016-03-17T13:31:17
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        qcustomplot.cpp \
    core.cpp \
    database.cpp

HEADERS  += mainwindow.h\
         qcustomplot.h \
    core.h \
    database.h

FORMS    += mainwindow.ui
