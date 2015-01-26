#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "Picture.h"
#include <list>
#include <map>

using namespace std;

class Compressor {
public:
    Compressor(list<SDL_Color> startColors, Picture* picture);
    list<int> getPixels();


private:
    SDL_Color getPixel(int x, int y);
    int getDictionaryIndex(list<SDL_Color> c);

    map<int, list<SDL_Color> > dictionary; //tzw. slownik LZW
    Picture *picture;

    int dictionarySize = 0;
};


#endif
