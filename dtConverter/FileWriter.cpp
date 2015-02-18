#include <SDL/SDL.h>
#include <string>
#include <fstream>
#include <bitset>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <QDebug>

#include "FileWriter.h"

/** Konstruktor klasy FileWriter
@param savePath miejsce, gdzie ma zostać zapisany plik wynikowy
@param saveName nazwa pliku wynikowego
*/
FileWriter::FileWriter(const string& savePath, const string& saveName)
{
    this->savePath = savePath;
    this->saveName = saveName;
}

/** Funkcja odpowiedzialna za prawidłowy zapis do pliku
@param picture obiekt klasy Picture bądący reprezentacją obrazka wejściowego (DI)
@param pixelListAfterCompression lista indeksów słownika LZW po kompresji (lista pikseli)
@param colorsList lista kolorów obrazu wejściowego
@param maxIndex maksymalny indeks słownika LZW użyty przy kompresji LZW
*/
void FileWriter::saveFile(Picture *picture, const vector<int>& pixelListAfterCompression, const vector<SDL_Color>& colorsList, const int& maxIndex)
{

    string temp;
    temp = saveName.substr(saveName.length()-3,3);
    if(temp == ".dt")
    {
        savePath = savePath + "/" + saveName; //sciezka dostepu + nazwa pliku
    }
    else
    {
        savePath = savePath + "/" + saveName + ".dt"; //sciezka dostepu + nazwa pliku + .dt
    }

    ofstream file(savePath.c_str());

    //zapis nagłówka do pliku
    file<<std::setfill('0')<<std::setw(6)<<std::hex<<picture->getPictureWidth();
    qDebug()<<"Width: "<<picture->getPictureWidth();
    file<<std::setfill('0')<<std::setw(6)<<std::hex<<picture->getPictureHeight();
    qDebug()<<"Height: "<<picture->getPictureHeight();
    int pixelWidth = (log(maxIndex) / log(16)) + 1; //tyle bitów potrzeba do zapisania każdego z użytych indeksów słownika;
    file<<std::setfill('0')<<std::setw(6)<<std::hex<<pixelWidth;
    qDebug()<<"pixelWidth: "<<pixelWidth;
    file<<std::setfill('0')<<std::setw(4)<<std::hex<<27;
    int pictureStart = 27 + colorsList.size()*6;
    file<<std::setfill('0')<<std::setw(4)<<std::hex<<pictureStart;
    qDebug()<<"pictureStart "<<pictureStart;

    //zapis kolorów obrazka do pliku - słownik
    for(vector<SDL_Color>::const_iterator it = colorsList.begin(); it != colorsList.end(); ++it) {
        qDebug()<<(int)(*it).r<<" "<<(int)(*it).g<<" "<<(int)(*it).r;
        file<<std::setfill('0')<<std::setw(2)<<std::hex<<((int)(*it).r);
        file<<std::setfill('0')<<std::setw(2)<<std::hex<<((int)(*it).g);
        file<<std::setfill('0')<<std::setw(2)<<std::hex<<((int)(*it).b);
    }
    //zapis pikseli do pliku
    for(vector<int>::const_iterator it = pixelListAfterCompression.begin(); it != pixelListAfterCompression.end(); it++) {
        file<<std::setfill('0')<<std::setw(pixelWidth)<<std::hex<<(*it);
    }

    file.close();
}

/** Konwersja liczby w systemie dziesiętnym na system binarny
@param value wartość, która zostanie zamieniona na system binarny
@param precision długość ciągu wynikowego
@return bitowy zapis value o długości precision
*/
string FileWriter::convertValueToBinary(int value, const int& precision) {

    string stringResult;
    while(value != 0) {
            stringResult = (value % 2 == 0 ? "0" : "1") + stringResult;
            value /= 2;
    }

    while(stringResult.length() != precision) {
        stringResult = "0" + stringResult;
    }

    return stringResult;
}
