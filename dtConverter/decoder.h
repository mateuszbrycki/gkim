#ifndef DECODER_H_INCLUDED
#define DECODER_H_INCLUDED

#include <iostream>
#include <string>
#include <cstddef>
#include <fstream>
#include <vector>
#include <map>
#include<iostream>
#include<SDL/SDL.h>

using namespace std;

class Decoder
{
    ///zmienne


    /*
    @param *screen ekran SDL
    @param height - wysokosc okna SDL
    @param width - szerokosc okna SDL
    @param tytul - tytul okna SDL
    @param maxColors - wielkosc podstawowego slownika
    @param pixelWidth - Informacja o ilości bitów potrzebnych do zapisu jednego pixela
    @param dictionaryStart - Numer bitu od którego rozpoczyna się zapis słownika LZW względem początku pliku
    @param pictureStart - Numer bitu od którego rozpoczyna się zestaw danych względem początku pliku
    @param pixels - wektor w ktorym przechowywane sa skladowe RGB pixela
    @param dictonaryColors - mapa w ktorej przechowywany jest slownik
     */
public:
SDL_Surface *screen;
int height;
int width;
char const* tytul = "BitMapPreview";
protected:
int maxColors;
int pixelWidth;
int dictionaryStart;
int pictureStart;
vector<SDL_Color> pixels;
map<int,string> dictionaryColors;


///metody
public:
int power(int liczba, int dopotegi);
int bin2dec(string input);
string charToString(char *buffer,int lenght);
void binaryPixelToRGB(string binaryPixel);

void drawPicture(string name_save);
void saveBMP(string name_save);
void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B);


Decoder()
{
    height=300;
    width=300;
}

};


#endif // DECODER_H_INCLUDED
