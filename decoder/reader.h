#ifndef READER_H_INCLUDED
#define READER_H_INCLUDED
#include "decoder.h"

class Reader :protected Decoder
{
    private:
    fstream plik;

public:
void readIndexesFromPixels();
void readDictionary();
void open();
};


#endif // READER_H_INCLUDED
