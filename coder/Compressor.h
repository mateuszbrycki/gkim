#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include "Picture.h"
#include <vector>
#include <map>

using namespace std;

class Compressor {
public:
    Compressor(const vector<SDL_Color>& startColors, Picture* picture);
    vector<int> getPixels();
    int getMaxIndex();

private:
    SDL_Color getPixel(const int& x, const int& y);
    int getDictionaryIndex(const vector<SDL_Color>& c);

    map<int, vector<SDL_Color> > dictionary; //tzw. slownik LZW
    Picture *picture;

    int dictionarySize;
    int maxIndex;
};


#endif
