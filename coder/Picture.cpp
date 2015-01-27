#include <SDL/SDL.h>
#include "Compressor.h"
#include "Picture.h"
#include <vector>
#include <iostream>

using namespace std;
/*
** konstruktor: wczytywanie obrazka .bmp
**
*/
Picture::Picture(const string& openPath, const int& colorType)
{
    this->colorType = colorType;

    BMP = SDL_LoadBMP(openPath.c_str());
    if(!BMP) //sprawdzamy czy obrazek taki w ogóle istnieje
    {
        cout<<"Unable to load bitmap: "<<SDL_GetError();
    }
}
/*
** funkcja zwracajaca szerokosc obrazka
*/
int Picture::getPictureWidth()
{
    if(BMP) {
        return (BMP->w);
    }
    return 0;
}
/*
** funkcja zwracajaca wysokosc obrazka
*/
int Picture::getPictureHeight()
{
    if(BMP) {
        return (BMP->h);
    }
    return 0;
}
/*
** Funkcja pobierajaca kolor danego piksela
** źródło: pliki z laboratorium z GKiM
*/
SDL_Color Picture::getPixelColor(const int& x,const int& y)
{

    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x >= 0) && (x < this->getPictureWidth()) && (y >= 0) && (y < this->getPictureHeight())) {
        //determine position
        char* pPosition=(char*)BMP->pixels ;
        //offset by y
        pPosition+=(BMP->pitch*y) ;
        //offset by x
        pPosition+=(BMP->format->BytesPerPixel*x);
        //copy pixel data
        memcpy(&col, pPosition, BMP->format->BytesPerPixel);
        //convert color
        SDL_GetRGB(col, BMP->format, &color.r, &color.g, &color.b);
    }

    if(colorType == 1)
    {
        color.r = 0.299*color.r + 0.587*color.g + 0.114*color.b;
        color.g = 0.299*color.r + 0.587*color.g + 0.114*color.b;
        color.b = 0.299*color.r + 0.587*color.g + 0.114*color.b;
    }

    return ( color ) ;
}
/*
** Funkcja zwracajaca liste wszystkich kolorow obrazka
*/
vector<SDL_Color> Picture::getPictureColors()
{
    vector<SDL_Color> ListOfColors;

    int x = this->getPictureWidth(),
        y = this->getPictureHeight();

    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
        {
            SDL_Color color = getPixelColor(i, j);
            if(!this->isInList(ListOfColors, color)) {
                ListOfColors.push_back(color);
            }
        }
    }

    return ListOfColors;
}
/*
** funkcja: sprawdza czy kolor został już wyszukany / czy znajduje sie w liście
*/
bool Picture::isInList(const vector<SDL_Color>& ListOfColors, const SDL_Color& color) {
    for(vector<SDL_Color>::const_iterator it = ListOfColors.begin(); it != ListOfColors.end(); ++it)
    {
        if(((*it).r == color.r) && ((*it).b == color.b) && ((*it).g == color.g)) {
            return true;
        }
    }
    return false;
}
