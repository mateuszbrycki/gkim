#include <SDL/SDL.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <QDebug>

#include "Compressor.h"
#include "Picture.h"

using namespace std;
/*
@param openPath ścieżka do pliku wejściowego BMP
@param colorType konwersja w kolorze lub skali szarości
*/
Picture::Picture(const string& openPath, const int& colorType)
{
    this->colorType = colorType;

    BMP = SDL_LoadBMP(openPath.c_str());
}
/*
** funkcja zwracajaca szerokosc obrazka
*/
int Picture::getPictureWidth()
{
    if(this->checkBMPFile()) {
        return (BMP->w);
    }
    return 0;
}
/*
@return wysokość wejściowego obrazu BMP
*/
int Picture::getPictureHeight()
{
    if(this->checkBMPFile()) {
        return (BMP->h);
    }
    return 0;
}

/*
@param x współrzędna x piksela
@param y współrzędna y piksela
@return referencja do obiektu klasy SDL_Color będącego reprezentacją piksela obrazu o współrzędnych (x,y)
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
    if(this->colorType == 1)
    {
        //zamiana na skalę szarości
        Uint8 temp = 0.299*(color.r) + 0.587*(color.g) + 0.114*(color.b);

        color.r = color.g = color.b = temp;
    }

    return ( color ) ;
}
/*
@return lista wszystkich kolorow obrazka
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
            //jeżeli lista elementów ma już 32 kolory to możemy przerwać przeszukiwanie
            if(ListOfColors.size() == 32) {
                return ListOfColors;
            }
            SDL_Color color = this->getPixelColor(i, j);

            auto iter = find_if(ListOfColors.begin(), ListOfColors.end(), [&color] (SDL_Color const& colorInList) -> bool{
                       return ((colorInList.r == color.r) && (colorInList.b == color.b) && (colorInList.g == color.g));
            });
            //jeżeli iterator doszedł do końca to znaczy, że elementu nie ma w kontenerze
            if(iter == ListOfColors.end()) {
                 ListOfColors.push_back(color);
            }
        }
    }

    return ListOfColors;
}

/*
@return informacja o tym, czy plik wejściowy BMP został poprawnie otworzony
*/
bool Picture::checkBMPFile() {
    if(this->BMP) {
        return true;
    }
    return false;
}

