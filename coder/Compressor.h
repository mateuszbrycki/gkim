#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "DT_Color.h"
#include "Picture.h"
#include <list>

using namespace std;

class Compressor {
public:
    Compressor(List<DT_Color&> startColors, Picture* picture, const int& colorType);
    list<int> getPixels(int colorType);


private:
    DT_Color& getPixel(int x, int y);
    int getDictionaryIndex(list<DT_Color&> c);

    map<int, List<DT_Color&>> dictionary; //tzw. s�ownik LZW
    Picture *picture;

    int colorType;
    int dictionarySize = 0;
};


#endif
