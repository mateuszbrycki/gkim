#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <SDL/SDL.h>
#include "Picture.h"

using namespace std;

class FileWriter
{
public:
    FileWriter(const string& savePath);
    void saveFile(const Picture& *picture, const list<int>& pixelListAfterCompression, const list<SDL_Color&>& colorsList));
    int getMaxUsedIndexBinaryLength(const list<int>& pixelListAfterCompression);
private:
    string savePath;
};

#endif
