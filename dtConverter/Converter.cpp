#include "Converter.h"
#include <QDebug>
#include <QProgressDialog>
#include <QCoreApplication>
#include <QThread>

#include <SDL.h>
#include <vector>
#include <iostream>
#include <QMutex>
#include <QObject>

#include "Picture.h"
#include "FileWriter.h"
#include "Compressor.h"

Converter::Converter(const string& openPath, const string& savePath, const string& saveName, const int& colorType) :
    openPath(openPath), savePath(savePath), saveName(saveName), colorType(colorType)
{
}

void Converter::run() {
    emit conversionStart();
    emit conversionProgress(5);

    QCoreApplication::processEvents();
    QMutex mutex;
    mutex.lock();

    Picture *picture = new Picture(openPath, colorType);
    if(!picture->checkBMPFile()) {
        emit conversionFailed();
        emit finished();
        mutex.unlock();
        emit conversionEnd();

        return;
    }

    FileWriter *writer = new FileWriter(savePath, saveName); //obiekt klasy służącej do zapisu obrazu do pliku

    emit conversionProgress(20);

    vector<SDL_Color> colorsList = picture->getPictureColors(); //pobranie kolorow z obrazka - 32 kolory
    qDebug()<<"Pobrano kolory obrazka!";

    emit conversionProgress(40);

    Compressor *compressor = new Compressor(colorsList, picture);
    vector<int> pixelListAfterCompression = compressor->getPixels();
    qDebug()<<"Skompresowano!";

    emit conversionProgress(90);

    writer->saveFile(picture, pixelListAfterCompression, colorsList, compressor->getMaxIndex());
    qDebug()<<"Koniec";

    delete picture;
    delete compressor;
    delete writer;

    mutex.unlock();
    emit conversionSuccess();
    emit conversionEnd();
}

