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
    database.cpp \
    graphwindow.cpp \
    graphics.cpp

HEADERS  += mainwindow.h\
         qcustomplot.h \
    core.h \
    database.h \
    graphwindow.h \
    graphics.h

FORMS    += mainwindow.ui \
    graphwindow.ui

OTHER_FILES += \
    logo.ico

win32: RC_ICONS = logo.ico

