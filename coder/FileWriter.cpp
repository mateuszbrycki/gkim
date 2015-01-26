/*Dekorator do SDL_COLOR - przeładowanie operatora != */

#include "FileWriter.h"
#include <SDL/SDL.h>
#include <string>
#include <fstream>

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
void FileWriter::saveFile(Picture *picture, list <DT_Color> pixelListAfterCompression)
{
    ofstream File;
    string FileName = "/Compressed.dt";

    savePath = savePath + FileName; //sciezka dostepu + nazwa pliku

    File.open(savePath);

    while(!pixelListAfterCompression.empty())
    {
            File<<pixelListAfterCompression.pop();
    }

    File.close();
}
