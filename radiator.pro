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
    httprequestworker.cpp \
    mainwindow.cpp \
    plane.cpp \
    CutdownTimer.cpp

HEADERS  += \
    httprequestworker.h \
    mainwindow.h \
    plane.h \
    CutdownTimer.h
