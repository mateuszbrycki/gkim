#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif


#include <SDL/SDL.h>
#include "Picture.h" //do napisania
#include "FileWriter.h" //do napisania
#include "Compressor.h"
#include <list>
#include <iostream>

int main ( int argc, char** argv )
{
    string openPath = "H:/c++/gkim/coder/bin/Debug/obraz.bmp", //œcie¿ka do otworzenia .bmp
            savePath = "H:/c++/gkim/coder/bin/Debug/"; //œcie¿ka do zapisu .dt
    int colorType = 0; //0 - kolor, 1 - szary
    Picture *picture = new Picture(openPath, colorType);
    FileWriter *writer = new FileWriter(savePath); //obiekt klasy s³u¿¹cej do zapisu obrazu do pliku

    list<SDL_Color> colorsList = picture->getPictureColors(); //pobranie kolorow z obrazka - 32 kolory

    for(list<SDL_Color>::iterator it = colorsList.begin(); it != colorsList.end(); ++it) {
        cout<<(int)(*it).r<<" "<<(int)(*it).g<<" "<<(int)(*it).b<<endl;
    }


    Compressor *compressor = new Compressor(colorsList, picture);
    list<int> pixelListAfterCompression = compressor->getPixels();

    writer->saveFile(picture, pixelListAfterCompression, colorsList, compressor->getMaxIndex());

    return 0;
}
