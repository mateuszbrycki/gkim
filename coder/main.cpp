#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <vector>
#include <iostream>

#include "Picture.h" //do napisania
#include "FileWriter.h" //do napisania
#include "Compressor.h"

int main ( int argc, char** argv )
{
    string openPath = "H:/c++/gkim/coder/bin/Debug/obraz.bmp", //�cie�ka do otworzenia .bmp
            savePath = "H:/c++/gkim/coder/bin/Debug/"; //�cie�ka do zapisu .dt
    int colorType = 0; //0 - kolor, 1 - szary
    Picture *picture = new Picture(openPath, colorType);
    FileWriter *writer = new FileWriter(savePath); //obiekt klasy s�u��cej do zapisu obrazu do pliku

    vector<SDL_Color> colorsList = picture->getPictureColors(); //pobranie kolorow z obrazka - 32 kolory

    for(vector<SDL_Color>::iterator it = colorsList.begin(); it != colorsList.end(); ++it) {
        cout<<(int)(*it).r<<" "<<(int)(*it).g<<" "<<(int)(*it).b<<endl;
    }


    Compressor *compressor = new Compressor(colorsList, picture);
    vector<int> pixelListAfterCompression = compressor->getPixels();

    writer->saveFile(picture, pixelListAfterCompression, colorsList, compressor->getMaxIndex());

    return 0;
}
