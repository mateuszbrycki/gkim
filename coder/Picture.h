#ifndef PICTURE_H
#define PICTURE_H

#include <SDL/SDL.h>
#include <list>
#include <string>

using namespace std;
/*
** Klasa obrazka
** funkcja: getPixelColor pobiera kolor jednego piksela
** list<SDL_Color> - tam s� zapisywane wszystkie kolory obrazka
*/
class Picture {
public:
    Picture(const string& openPath, const int& colorType);
    list<SDL_Color> getPictureColors();
    SDL_Color getPixelColor(const int& x, const int& y);
    int getPictureWidth();
    int getPictureHeight();

private:
    bool isInList(const list<SDL_Color>& ListOfColors, const SDL_Color& color);
    SDL_Surface *BMP;
    int colorType;
};


#endif
