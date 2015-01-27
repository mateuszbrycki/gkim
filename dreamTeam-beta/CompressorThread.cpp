#include "CompressorThread.h"
#include <QDebug>

#include <SDL.h>
#include <vector>
#include <iostream>
#include <QMutex>

#include "Picture.h"
#include "FileWriter.h"
#include "Compressor.h"

CompressorThread::CompressorThread(QObject *parent) :
    QThread(parent)
{
}

void CompressorThread::run(const string& openPath, const string& savePath, const string& saveName, const int& colorType) {
    QMutex mutex;
    mutex.lock();

    Picture *picture = new Picture(openPath, colorType);
    FileWriter *writer = new FileWriter(savePath, saveName); //obiekt klasy służącej do zapisu obrazu do pliku

    vector<SDL_Color> colorsList = picture->getPictureColors(); //pobranie kolorow z obrazka - 32 kolory
    qDebug()<<"Pobrano kolory obrazka!";

    Compressor *compressor = new Compressor(colorsList, picture);
    vector<int> pixelListAfterCompression = compressor->getPixels();
    qDebug()<<"Skompresowano!";

    writer->saveFile(picture, pixelListAfterCompression, colorsList, compressor->getMaxIndex());
    qDebug()<<"Koniec";

    delete picture;
    delete compressor;
    delete writer;

    mutex.unlock();
    emit compressionSuccess();
}
