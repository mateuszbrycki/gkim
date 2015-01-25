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

# Mateusz: zostawiłem sobie ścieżki w razie jakby konfiguracja na wzglednych przestała działać
#LIBS  +=  -L H:/c++/gkim/dreamTeam-beta/SDL-1.2.14/lib -lSDL
#INCLUDEPATH += H:/c++/gkim/dreamTeam-beta/SDL-1.2.14/include
#*/

LIBS  +=  -L SDL-1.2.14/lib -lSDL
INCLUDEPATH += SDL-1.2.14/include


