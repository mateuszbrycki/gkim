#include <SDL/SDL.h>
#include <string>
#include <fstream>
#include <bitset>
#include <math.h>
#include <iostream>

#include "FileWriter.h"

/*
** konstruktor klasy FileWriter
*/
FileWriter::FileWriter(const string& savePath, const string& saveName)
{
    this->savePath = savePath;
    this->saveName = saveName;
}

/*
** funkcja zapisujaca wynik dzialania kompresora do pliku dt
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

    //file.open(savePath.c_str(),  ofstream::out | ofstream::app);

    //zapis nagłówka do pliku
    file << bitset<24>(picture->getPictureWidth());
    file << bitset<24>(picture->getPictureHeight());

    int pixelWidth = (log(maxIndex) / log(2)) + 1; //tyle bitów potrzeba do zapisania każdego z użytych indeksów słownika;
    file << bitset<24>(pixelWidth);
    file << bitset<16>(73);
    file << bitset<16>(89);

    //zapis kolorów obrazka do pliku
    for(vector<SDL_Color>::const_iterator it = colorsList.begin(); it != colorsList.end(); ++it) {
        file<<bitset<8>((*it).r) ;
        file<<bitset<8>((*it).g);
        file<<bitset<8>((*it).b);
    }

    //zapis pikseli do pliku
    for(vector<int>::const_iterator it = pixelListAfterCompression.begin(); it != pixelListAfterCompression.end(); it++) {
        //tutaj nie można użyć bitset
        file<<this->convertValueToBinary(*it, pixelWidth);
    }

    file.close();
}

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
