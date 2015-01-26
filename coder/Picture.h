#ifndef PICTURE_H
#define PICTURE_H

#include "DT_Color.h"
#include <SDL/SDL.h>
#include <list>

using namespace std;
/*
** Klasa obrazka
** funkcja: getPixelColor pobiera kolor jednego piksela
** list<SDL_Color> - tam s¹ zapisywane wszystkie kolory obrazka
*/
class Picture {
public:
    Picture(string openPath, int colorType);
    list<SDL_Color> getPictureColors();
    SDL_Color getPixelColor(int x, int y, int colorType);
    int getPictureWidth();
    int getPictureHeight();

private:
    SDL_Surface *BMP;
    int colorType;
};


#endif
