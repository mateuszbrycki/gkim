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
    SDL_Surface* BMP = SDL_LoadBMP(openPath);

    if(!BMP) //sprawdzamy czy obrazek taki w ogóle istnieje
    {
        cout<<"Unable to load bitmap: "<<SDL_GetError();
    }
}
/*
** Funkcja pobierajaca kolor danego piksela
** źródło: pliki z laboratorium z GKiM
*/
SDL_Color getPixelColor(int x, int y)
{
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x >= 0) && (x < BMP->getPictureWidth()) && (y >= 0) && (y < BMP->getPictureHeight())) {
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
    return ( color ) ;
}
/*
** Funkcja zwracajaca liste wszystkich kolorow obrazka
*/
list<SDL_Color> Picture::getPictureColors()
{
    list<SDL_Color> ListOfColors;
    bool IsIn = false;
    SDL_Color color;

        int x = BMP->getPictureWidth(),
            y = BMP->getPcitureHeight();

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

bool Picture::isInList(list<SDL_Color&> ListOfColors, SDL_Color& color) {
    for(list<SDL_Color>::iterator it = ListOfColors.begin(); it != ListOfColors.end(); it++)
    {
        if(((*it).r == color.r) && ((*it).b == color.b) && ((*it).g == color.g) {
            return true;
        }
    }
    return false;
}
