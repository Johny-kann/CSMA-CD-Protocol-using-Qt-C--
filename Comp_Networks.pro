#-------------------------------------------------
#
# Project created by QtCreator 2015-11-17T00:12:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Comp_Networks
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    models.cpp \
    controller.cpp \
    testers.cpp \
    logics.cpp \
    status.cpp

HEADERS  += mainwindow.h \
    models.h \
    controller.h \
    logics.h \
    status.h

FORMS    += mainwindow.ui
