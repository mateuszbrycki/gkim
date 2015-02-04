#include "reader.h"
#include <QDebug>


/*
Funkcja otwierajaca plik z rozszerzeniem dt
@param name - nazwa otwieranego pliku
 */
void Reader::open(string name,string name_save){

    //cout<<"Wprowadz nazwe pliku ktory ma byc wczytany ";

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
        /// wczytanie width
        plik.seekg( 0,ios::beg );
        int length =24;
        char * buffer = new char [length];
        plik.read(buffer,length);
        string helpReader;
        helpReader =charToString(buffer,length);
        width=bin2dec(helpReader);
        /// end of width
        ///wczytanie height
        plik.read(buffer,length);
        helpReader =charToString(buffer,length);
        cout<<helpReader<<endl;
        height=bin2dec(helpReader);
        ///end of height
        ///wczytanie pixelWidth
        plik.read(buffer,length);
        helpReader =charToString(buffer,length);
        pixelWidth=bin2dec(helpReader);
        cout<<"pixelWidth "<<pixelWidth<<endl;
        ///end of pixelWidth
        ///wczytaniey
        length =16;
        buffer = new char [length];
        plik.read(buffer,length);
        helpReader =charToString(buffer,length);
        dictionaryStart=bin2dec(helpReader);
        /// endo of dictionaryStart
        ///wczytanie pictureStart
        plik.read(buffer,length);
        helpReader =charToString(buffer,length);
        pictureStart=bin2dec(helpReader);
        ///end of pictureStart

        screen = SDL_SetVideoMode(width, height,32,SDL_RESIZABLE|SDL_DOUBLEBUF);

        readDictionary(name_save);

    }

    plik.close();


}


/*
Funkcja czytajaca słownik z pliku
@param bitCounter - flaga ktora chodzimy po pliku
@param pixLength - ilosc pobranych bitow
@param dictionaryIndex - zmienna inkrementowana indeks slownika
@param helpReader zmienna pomocnicza do zmiany z char na string
@param transformedColor - zmienna przypisywana do slownika
 */
void Reader::readDictionary(string name_save)
{


    maxColors = (pictureStart-dictionaryStart)/24;
    //cout<<maxColors<<endl;
    int bitCounter = 0;
    int pixLength = 24;
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
        decimal = bin2dec(transformedColor);
        qDebug() << decimal << endl;
        dictionaryColors[dictionaryIndex] = transformedColor;
        bitCounter = bitCounter +24;
        dictionaryIndex++;
    }

    readIndexesFromPixels(name_save);
}


/*
Funkcja dekodujaca plik dt alorytmem LZW
@param length - zmienna przechowujaca ilosc bitow na jeden pixel
@param dictionaryIndex - zmienna przechwytujaca pixelWidth bitow by porownac czy znajduja sie w slowniku
@param param helpReader - zmienna pomocnicza do zmiany z char na string
@param characters - zmienna przechowujaca znaki ktore przypisujemy do slownika
@param word - zmienna tworzaca nowe slowo w slowniku
 */
void Reader::readIndexesFromPixels(string name_save){
    maxColors = maxColors + 1;
    int length = pixelWidth;
    int dictionaryIndex;
    char * buffer = new char [length];
    string helpReader;
    string characters;
    string word;

    plik.seekg(pictureStart-1,ios::beg);
    plik.read(buffer,length);
    helpReader = charToString(buffer,length);
    int firstIndex = bin2dec(helpReader);
    characters = dictionaryColors[firstIndex];

    while(!plik.fail()){
        plik.read(buffer,length);
        helpReader = charToString(buffer,length);
        dictionaryIndex = bin2dec(helpReader);

        if (dictionaryColors.count(dictionaryIndex)){
          word = dictionaryColors[dictionaryIndex];
        }
        else if (dictionaryIndex == maxColors){
            word = characters + characters.substr(0,24);
        }
        else{
          throw "Decoding problem!";
        }

        binaryPixelToRGB(word);
        dictionaryColors[maxColors++] = characters + word.substr(0,24);
        characters = word;
  }

        drawPicture(name_save);
}


