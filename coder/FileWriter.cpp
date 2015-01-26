/*Dekorator do SDL_COLOR - przeładowanie operatora != */

#include "FileWriter.h"
#include <SDL/SDL.h>
#include <string>
#include <fstream>
#include <bitset>
#include <math.h>

/*
** konstruktor klasy FileWriter
*/
FileWriter::FileWriter(const string savePath)
{
    this->savePath = savePath;
}

/*
** funkcja zapisujaca wynik dzialania kompresora do pliku dt
*/
void FileWriter::saveFile(const Picture& *picture, const list<int>& pixelListAfterCompression, const list<SDL_Color&>& colorsList)
{
    ofstream file;
    string fileName = "/Compressed.dt";
    savePath = savePath + fileName; //sciezka dostepu + nazwa pliku
    file.open(savePath);

    //zapis nagłówka do pliku
    file << bitset<24>(picture->getPictureWidth());
    file << bitset<24>(picture->getPictureHeight());

    int pixelWidth = this->getMaxUsedIndexBinaryLength(pixelListAfterCompression);
    file << bitset<24>(pixelWidth);

    file << bitset<16>(73);
    file << bitset<16>(89);

    //zapis kolorów obrazka do pliku
    for(list<SDL_Color&>::iterator it = colorsList.begin(); it != colorsList.end(); it++) {
        file<<bitset<8>(*it).r;
        file<<bitset<8>(*it).g;
        file<<bitset<8>(*it).b;
    }

    //zapis pikseli do pliku
    for(list<int>::iterator it = pixelListAfterCompression.begin(); it != pixelListAfterCompression.end(); it++) {
        file<<bitset<pixelWidth>(*it);
    }

    file.close();
}

//zwraca ile bitów jest potrzebne do zapisania makymalnego używanego indeksu w tablicy
int getMaxUsedIndexBinaryLength(const list<int>& pixelListAfterCompression) {
    int maxIndex = 0;

    for(list<int>::iterator it = pixelListAfterCompression.begin(); it != pixelListAfterCompression.end(); it++) {
        if(*it > maxIndex) {
            maxIndex = *it;
        }
    }

    //doDolu(log2(max))+1 => log2(max) = log10(max) / log10(2)
	int result = (log(maxIndex) / log(2)) + 1; //tyle bitów potrzeba do zapisania każdego z użytych indeksów słownika

	return result;
}
