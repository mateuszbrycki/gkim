#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED
#include "decoder.h"
#include <QString>
class Reader :protected Decoder
{


    private:
    fstream plik;

public:
void readIndexesFromPixels(string name_save);
void readDictionary(string name_save);
void open(string name,string name_save);
};


#endif // READER_H_INCLUDED
