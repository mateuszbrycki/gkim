#include "reader.h"
#include <QDebug>

/**
Funkcja otwierajaca plik z rozszerzeniem dt
@param name nazwa otwieranego pliku
@param name_save nazwa pliku wynikowego
 */
void Reader::open(string name,string name_save){



    size_t found = name.find(".dt");

    if(found==-1)
    {
        name = name + ".dt";
    }

    char *nazwa= new char[name.length()+1];
    strcpy( nazwa, name.c_str() );

    plik.open( nazwa, ios::in|ios::binary);
    if( plik.good() == true )
    {
        plik.seekg( 0,ios::beg );
        int length =6;
        char * buffer = new char [length];
        plik.read(buffer,length);
        string helpReader;
        helpReader =charToString(buffer,length);

        width=hex2dec(helpReader);
        plik.read(buffer,length);
        helpReader =charToString(buffer,length);
        qDebug()<<"Width "<<width;
        height=hex2dec(helpReader);
        qDebug()<<"Height "<<height;
        plik.read(buffer,length);
        helpReader =charToString(buffer,length);
        pixelWidth=hex2dec(helpReader);
        qDebug()<<"Pixel width "<<pixelWidth;
        length =4;
        buffer = new char [length];
        plik.read(buffer,length);
        helpReader =charToString(buffer,length);
        dictionaryStart=hex2dec(helpReader);
        qDebug()<<"dictionaryStart "<< dictionaryStart;
        plik.read(buffer,length);
        helpReader =charToString(buffer,length);
        pictureStart=hex2dec(helpReader);
        qDebug()<<"pictureStart "<< pictureStart;
        screen = SDL_SetVideoMode(width, height,32,SDL_RESIZABLE|SDL_DOUBLEBUF);

        readDictionary(name_save);

    }

    plik.close();


}


/** Funkcja czytajaca słownik z pliku
@param name_save nazwa pliku DT
 */
void Reader::readDictionary(string name_save)
{
    maxColors = (pictureStart-dictionaryStart)/6;
    int bitCounter = 0;
    int pixLength = 6;
    int dictionaryIndex = 1;
    string helpReader;
    string transformedColor;
    char * buffer = new char [pixLength];

    plik.seekg(dictionaryStart - 1,ios::beg);
    int decimal;
    while(bitCounter<pictureStart-dictionaryStart){
        plik.read(buffer,pixLength);
        helpReader = charToString(buffer,pixLength);
        transformedColor=helpReader;
        decimal = hex2dec(transformedColor);
        dictionaryColors[dictionaryIndex] = transformedColor;
        bitCounter = bitCounter +6;
        dictionaryIndex++;
    }


    readIndexesFromPixels(name_save);
}


/** Funkcja dekodujaca plik dt alorytmem LZW
@param name_save nazwa pliku DT
 */
void Reader::readIndexesFromPixels(string name_save){
    maxColors = maxColors + 1;
    int length = pixelWidth;
    qDebug()<<"pixelWidth"<<pixelWidth<<endl;
    int dictionaryIndex;
    char * buffer = new char [length];
    string helpReader;
    string characters;
    string word;

    plik.seekg(pictureStart-1,ios::beg);
    plik.read(buffer,length);
    helpReader = charToString(buffer,length);
    int firstIndex = hex2dec(helpReader);
    characters = dictionaryColors[firstIndex];

    while(!plik.fail()){
        plik.read(buffer,length);
        qDebug()<<"buffer "<<buffer<<endl;
        helpReader = charToString(buffer,length);
        dictionaryIndex = hex2dec(helpReader);
        qDebug()<<"dictionaryIndex "<<dictionaryIndex<<endl;

        if (dictionaryColors.count(dictionaryIndex)){
          word = dictionaryColors[dictionaryIndex];
        }
        else if (dictionaryIndex == maxColors){
            word = characters + characters.substr(0,6);
        }
        else{
          throw "Decoding problem!";
        }

        binaryPixelToRGB(word);
        dictionaryColors[maxColors++] = characters + word.substr(0,6);
        characters = word;
  }


        drawPicture(name_save);
}


