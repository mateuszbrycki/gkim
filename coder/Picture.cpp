#include <SDL/SDL.h>
#include "Compressor.h"
#include "Picture.h"
#include <list>

using namespace std;
/*
** konstruktor: wczytywanie obrazka .bmp
**
*/
Picture::Picture(string openPath, int colorType)
{
    this->colorType = colorType;

    BMP = SDL_LoadBMP(openPath);

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
    return (BMP->w);
}
/*
** funkcja zwracajaca wysokosc obrazka
*/
int Picture::getPictureHeight()
{
    return (BMP->h);
}
/*
** Funkcja pobierajaca kolor danego piksela
** źródło: pliki z laboratorium z GKiM
*/
SDL_Color Picture::getPixelColor(int x, int y)
{
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x >= 0) && (x < Picture.getPictureWidth()) && (y >= 0) && (y < Picture.getPictureHeight())) {
        //determine position
        char* pPosition=(char*)screen->pixels ;
        //offset by y
        pPosition+=(screen->pitch*y) ;
        //offset by x
        pPosition+=(screen->format->BytesPerPixel*x);
        //copy pixel data
        memcpy(&col, pPosition, screen->format->BytesPerPixel);
        //convert color
        SDL_GetRGB(col, screen->format, &color.r, &color.g, &color.b);
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
list<SDL_Color> Picture::getPictureColors()
{
    list<SDL_Color> ListOfColors;

    SDL_Color color;

        int x = Picture.getPictureWidth(),
            y = Picture.getPictureHeight();

            for(int i = 0; i < x; i++)
            {
                for(int j = 0; j < y; j++)
                {
                    color = getPixelColor(x, y);
                    if(!isInList(ListOfColors, color)) {
                        ListOfColors.push_back(color);
                    }
                }
            }

      return ListOfColors;
}
/*
** funkcja: sprawdza czy kolor został już wyszukany / czy znajduje sie w liście
*/
bool Picture::isInList(list<SDL_Color&> ListOfColors, SDL_Color& color) {
    for(list<SDL_Color>::iterator it = ListOfColors.begin(); it != ListOfColors.end(); it++)
    {
        if(((*it).r == color.r) && ((*it).b == color.b) && ((*it).g == color.g) {
            return true;
        }
    }
    return false;
}
