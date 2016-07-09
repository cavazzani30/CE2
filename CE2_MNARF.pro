#-------------------------------------------------
#
# Project created by QtCreator 2014-04-26T15:59:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CE2_MNARF
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gerarArquivo.cpp \
    gaussJordan.cpp \
    montarEstampas.cpp \
    resolver.cpp

HEADERS  += mainwindow.h \
    defines.h \
    constantes.h

FORMS    += mainwindow.ui

RC_FILE = myapp.rc
