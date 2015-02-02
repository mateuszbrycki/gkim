#ifndef PICTURE_H
#define PICTURE_H

#include <SDL/SDL.h>
#include <vector>
#include <string>

using namespace std;
/*
** Klasa obrazka
** funkcja: getPixelColor pobiera kolor jednego piksela
** list<SDL_Color> - tam są zapisywane wszystkie kolory obrazka
*/
class Picture {
public:
    Picture(const string& openPath, const int& colorType);

    vector<SDL_Color> getPictureColors();
    SDL_Color getPixelColor(const int& x, const int& y);
    int getPictureWidth();
    int getPictureHeight();
    bool checkBMPFile();

private:
    bool isInList(const vector<SDL_Color>& ListOfColors, const SDL_Color& color);
    SDL_Surface *BMP = NULL;
    int colorType;
};

#endif
