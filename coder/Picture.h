#ifndef PICTURE_H
#define PICTURE_H

#include <SDL/SDL.h>
#include <list>
#include <string>

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
    SDL_Color getPixelColor(int x, int y);
    int getPictureWidth();
    int getPictureHeight();

private:
    bool isInList(list<SDL_Color> ListOfColors, SDL_Color color);
    SDL_Surface *BMP;
    int colorType;
};


#endif
