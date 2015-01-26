#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <SDL/SDL.h>
#include "Picture.h"

using namespace std;

class FileWriter
{
public:
    FileWriter(string savePath);
    void saveFile(Picture *picture, list <DT_Color> pixelListAfterCompression);
};

#endif
