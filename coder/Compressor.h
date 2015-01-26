#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "Picture.h"
#include <list>
#include <map>

using namespace std;

class Compressor {
public:
    Compressor(const list<SDL_Color>& startColors, Picture* picture);
    list<int> getPixels();
    int getMaxIndex();

private:
    SDL_Color getPixel(const int& x, const int& y);
    int getDictionaryIndex(const list<SDL_Color>& c);

    map<int, list<SDL_Color> > dictionary; //tzw. slownik LZW
    Picture *picture;

    int dictionarySize;
    int maxIndex;
};


#endif
