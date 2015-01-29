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

    //zapis nagłówka do pliku
    file << bitset<24>(picture->getPictureWidth());
    //file<<endl;
    file << bitset<24>(picture->getPictureHeight());
    //file<<endl;
    int pixelWidth = (log(maxIndex) / log(2)) + 1; //tyle bitów potrzeba do zapisania każdego z użytych indeksów słownika;
    file << bitset<24>(pixelWidth);
    //file<<endl;
    file << bitset<16>(105); //start słownika jest stały
    //file<<endl;
    int pictureStart = 105 + colorsList.size();
    file << bitset<16>(pictureStart);
    //file<<endl;

    //zapis kolorów obrazka do pliku
    for(vector<SDL_Color>::const_iterator it = colorsList.begin(); it != colorsList.end(); ++it) {
        file<<bitset<8>((*it).r) ;
        //file<<" ";
        file<<bitset<8>((*it).g);
        //file<<" ";
        file<<bitset<8>((*it).b);
       // file<<endl;
    }
    //file<<endl<<endl;
    //zapis pikseli do pliku
    for(vector<int>::const_iterator it = pixelListAfterCompression.begin(); it != pixelListAfterCompression.end(); it++) {
        //tutaj nie można użyć bitset
       // file<<endl;
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
