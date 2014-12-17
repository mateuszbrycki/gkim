#-------------------------------------------------
#
# Project created by QtCreator 2014-12-17T17:22:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dreamTeam-beta
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH +=SDL-1.2.14\include
LIBS  +=  -LSDL-1.2.14\lib \
          -LSDL\
          -lSDLmain
LIBS  +=  -lSDL.dll


