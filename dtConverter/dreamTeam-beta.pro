#-------------------------------------------------
#
# Project created by QtCreator 2014-12-17T17:22:51
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dtConverter
TEMPLATE = app
SOURCES += main.cpp\
        mainwindow.cpp \
    Compressor.cpp \
    FileWriter.cpp \
    Picture.cpp \
    CompressorThread.cpp

HEADERS  += mainwindow.h \
    Compressor.h \
    FileWriter.h \
    Picture.h \
    CompressorThread.h

FORMS    += mainwindow.ui

# Mateusz: zostawiłem sobie ścieżki w razie jakby konfiguracja na wzglednych przestała działać
LIBS  +=  -L H:/c++/gkim/dtConverter/SDL-1.2.14/lib -lSDL
INCLUDEPATH += H:/c++/gkim/dtConverter/SDL-1.2.14/include
#*/


