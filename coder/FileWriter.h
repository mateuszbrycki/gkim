#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <SDL/SDL.h>
#include "Picture.h"

using namespace std;

class FileWriter
{
public:
    FileWriter(string savePath);
    void saveFile(Picture *picture,list<int> pixelListAfterCompression, list<SDL_Color> colorsList);

private:
    int getMaxUsedIndexBinaryLength(list<int> pixelListAfterCompression);
    string convertValueToBinary(int value, const int& precision);
    string savePath;
};

#endif
