/*Dekorator do SDL_COLOR - przeładowanie operatora != */

#include "FileWriter.h"
#include <SDL/SDL.h>
#include <string>
#include <fstream>
#include <bitset>
#include <math.h>
#include <iostream>

/*
** konstruktor klasy FileWriter
*/
FileWriter::FileWriter(string savePath)
{
    this->savePath = savePath;
}

/*
** funkcja zapisujaca wynik dzialania kompresora do pliku dt
*/
void FileWriter::saveFile(Picture *picture, list<int> pixelListAfterCompression, list<SDL_Color> colorsList)
{

    string fileName = "Compressed.dt";
    savePath = savePath + fileName; //sciezka dostepu + nazwa pliku
    ofstream file(savePath.c_str());

    //file.open(savePath.c_str(),  ofstream::out | ofstream::app);

    //zapis nagłówka do pliku
    file << bitset<24>(picture->getPictureWidth());
    file << bitset<24>(picture->getPictureHeight());

    int pixelWidth = this->getMaxUsedIndexBinaryLength(pixelListAfterCompression);
    file << bitset<24>(pixelWidth);

    file << bitset<16>(73);
    file << bitset<16>(89);

    //zapis kolorów obrazka do pliku
    for(list<SDL_Color>::iterator it = colorsList.begin(); it != colorsList.end(); it++) {
        file<<bitset<8>((*it).r);
        file<<bitset<8>((*it).g);
        file<<bitset<8>((*it).b);
    }

    //zapis pikseli do pliku
    for(list<int>::iterator it = pixelListAfterCompression.begin(); it != pixelListAfterCompression.end(); it++) {
        //tutaj nie można użyć bitset
        file<<this->convertValueToBinary(*it, pixelWidth);
    }

    file.close();
}

//zwraca ile bitów jest potrzebne do zapisania makymalnego używanego indeksu w tablicy
int FileWriter::getMaxUsedIndexBinaryLength(list<int> pixelListAfterCompression) {
    int maxIndex = 0;

    for(list<int>::iterator it = pixelListAfterCompression.begin(); it != pixelListAfterCompression.end(); it++) {
        if((*it) > maxIndex) {
            maxIndex = (*it);
        }
    }

    //doDolu(log2(max))+1 => log2(max) = log10(max) / log10(2)
	int result = (log(maxIndex) / log(2)) + 1; //tyle bitów potrzeba do zapisania każdego z użytych indeksów słownika

	return result;
}

string FileWriter::convertValueToBinary(int value, const int& precision) {

    string stringResult;
    while(value != 0) {
            stringResult = (value %2==0 ?"0":"1") + stringResult;
            value /= 2;
    }

    while(stringResult.length() != precision) {
        stringResult = "0" + stringResult;
    }

    return stringResult;
}
