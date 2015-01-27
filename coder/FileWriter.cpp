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
FileWriter::FileWriter(const string& savePath)
{
    this->savePath = savePath;
}

/*
** funkcja zapisujaca wynik dzialania kompresora do pliku dt
*/
void FileWriter::saveFile(Picture *picture, const vector<int>& pixelListAfterCompression, const vector<SDL_Color>& colorsList, const int& maxIndex)
{

    string fileName = "Compressed.dt";
    savePath = savePath + fileName; //sciezka dostepu + nazwa pliku
    ofstream file(savePath.c_str());

    //file.open(savePath.c_str(),  ofstream::out | ofstream::app);

    //zapis nagłówka do pliku
    file << bitset<24>(picture->getPictureWidth());
    file<<std::endl;
    file << bitset<24>(picture->getPictureHeight());
    file<<std::endl;

    int pixelWidth = (log(maxIndex) / log(2)) + 1; //tyle bitów potrzeba do zapisania każdego z użytych indeksów słownika;
    file << bitset<24>(pixelWidth);
    file<<std::endl;
    file << bitset<16>(73);
    file<<std::endl;
    file << bitset<16>(89);
    file<<std::endl;

    //zapis kolorów obrazka do pliku
    for(vector<SDL_Color>::const_iterator it = colorsList.begin(); it != colorsList.end(); ++it) {
        file<<std::endl;
        file<<bitset<8>((*it).r) ;
        file<<" ";
         file<<std::endl;
        file<<bitset<8>((*it).g);
        file<<" ";
         file<<std::endl;
        file<<bitset<8>((*it).b);
        file<<" ";
        file<<std::endl;
         file<<std::endl;
    }

    //zapis pikseli do pliku
    for(vector<int>::const_iterator it = pixelListAfterCompression.begin(); it != pixelListAfterCompression.end(); it++) {
        //tutaj nie można użyć bitset
        file<<(*it)<<" ";
        file<<this->convertValueToBinary(*it, pixelWidth);
        file<<endl;

    }

    file.close();
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
