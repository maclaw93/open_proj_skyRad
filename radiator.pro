#-------------------------------------------------
#
# Project created by QtCreator 2017-05-22T11:05:34
#
#-------------------------------------------------

QT       += core gui\
            network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = radiator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    httprequestworker.cpp

HEADERS  += mainwindow.h \
    httprequestworker.h

FORMS    += mainwindow.ui
