#include"decoder.h"


/// funkcja potrzebna do zamiany z bin na dec
int Decoder::power(int liczba, int dopotegi)
{
    int wynik = 1;
    for(int i = 0; i < dopotegi; ++i)
        wynik *= liczba;
    return wynik;
}
/// zamiana bin na dec
int Decoder::bin2dec(string input)
{
    int output = 0;
    for(int i=0; i<input.size(); i++)
        output+=(input[i]-'0')*power(2,input.size()-i-1);
    return output;
}
/// zrzutowanie z char na string
string Decoder::charToString(char *buffer,int lenght)
{
    string ciag="";
    for(int i=0; i<lenght; i++)
    {
        ciag = ciag+buffer[i];
    }
    return ciag;
}




/// zamiana binarnych odczytow na RGB

void Decoder::binaryPixelToRGB(string binaryPixel){
    int binaryPixelSize = binaryPixel.size();
    string binaryPixelsArray[binaryPixelSize];
    //cout<<binaryPixelSize<<endl;
    int j = 0;
    for(int i=0; i<binaryPixelSize/24 ; i++){
        binaryPixelsArray[i] = binaryPixel.substr(j,24);
        j = j+24;
    }

    SDL_Color kolor[binaryPixelSize];

    for(int i=0; i<binaryPixelSize/24; i++){

        int red = bin2dec(binaryPixelsArray[i].substr(0,8));
        int green = bin2dec(binaryPixelsArray[i].substr(8,8));
        int blue = bin2dec(binaryPixelsArray[i].substr(16,8));

        kolor[i].r = red;
        kolor[i].g = green;
        kolor[i].b = blue;

        pixels.push_back(kolor[i]);
    }
}

/// metoda dekodujaca
void Decoder::readIndexesFromPixels()
{
    int length = pixelWidth;
    char * buffer = new char [length];
    string helpReader;
    string w;
    string entry;
    plik.seekg(pictureStart-1,ios::beg);
    int index;

    while(!plik.fail()){
        plik.read(buffer,length);
        helpReader = charToString(buffer,length);
        index = bin2dec(helpReader);

        if(w.size()%24!=0){
        cout<<w.size()<<endl;
        }
        if (dictionaryColors.count(index)){
          entry = dictionaryColors[index];
        }
        else if (index == maxColors){
            entry = w + w.substr(0,24);
        }
        else{
          throw "Blad w decodowaniu!";
        }
        binaryPixelToRGB(entry);
        dictionaryColors[maxColors++] = w + entry.substr(0,24);
        w = entry;
  }

        drawPicture();
}

void Decoder::readSlownik()
{
    int help = 0;
    string transformedColor;
    plik.seekg(dictionaryStart - 1,ios::beg);
    int i = 1;
    while(help<pictureStart-dictionaryStart)
    {
        string helpReader;
        int length = 24;
        char * buffer = new char [length];
        plik.read(buffer,length);
        //cout << "Wczytano " << plik.gcount() << " bajtow do bufora" << endl;
        helpReader = charToString(buffer,length);
        transformedColor=helpReader;
        dictionaryColors[i] = transformedColor;
        cout<<i<<" "<<helpReader<<endl;
        help = help +24;
        i++;
    }
    readIndexesFromPixels();
}
///funkcja otwierajaca plik
void Decoder::open()
{
    string name;
    cout<<"Wprowadz nazwe pliku ktory ma byc wczytany ";
    cin>>name;

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
        cout << "Wczytano " << plik.gcount() << " bajtow do bufora" << endl;
        string helpReader;
        helpReader =charToString(buffer,length);
        cout<<helpReader<<endl;
        width=bin2dec(helpReader);
        cout<<"Width "<<width<<endl;
        /// end of width
        ///wczytanie height
        plik.read(buffer,length);
        cout << "Wczytano " << plik.gcount() << " bajtow do bufora" << endl;
        helpReader =charToString(buffer,length);
        cout<<helpReader<<endl;
        height=bin2dec(helpReader);
        cout<<"Height "<<height<<endl;
        ///end of height
        ///wczytanie pixelWidth
        plik.read(buffer,length);
        cout << "Wczytano " << plik.gcount() << " bajtow do bufora" << endl;
        helpReader =charToString(buffer,length);
        cout<<helpReader<<endl;
        pixelWidth=bin2dec(helpReader);
        cout<<"pixelWidth "<<pixelWidth<<endl;
        ///end of pixelWidth
        ///wczytaniey
        length =16;
        buffer = new char [length];
        plik.read(buffer,length);
        cout << "Wczytano " << plik.gcount() << " bajtow do bufora" << endl;
        helpReader =charToString(buffer,length);
        cout<<helpReader<<endl;
        dictionaryStart=bin2dec(helpReader);
        cout<<"dictionaryStart"<<dictionaryStart<<endl;
        /// endo of dictionaryStart
        ///wczytanie pictureStart

        plik.read(buffer,length);
        cout << "Wczytano " << plik.gcount() << " bajtow do bufora" << endl;
        helpReader =charToString(buffer,length);
        cout<<helpReader<<endl;
        pictureStart=bin2dec(helpReader);
        cout<<"pictureStart "<<pictureStart<<endl;
        ///end of pictureStart


        screen = SDL_SetVideoMode(width, height, 32,SDL_RESIZABLE|SDL_DOUBLEBUF);

        readSlownik();


    }
    else cout << "Nie znaleziono pliku" <<endl;

    plik.close();

}



void Decoder::Funkcja1()// wcis 1 by zadzialalo
{

   maxColors =32;
      open();
}


void Decoder::Funkcja2()// wcis 2 by zadzialalo
{

    maxColors =30;
    open();
}


/// metoda rysujaca obraz
void Decoder::drawPicture()
{
    SDL_Color finalColor;
    int i = 0;
    cout<<"size: "<<pixels.size();
         for(int x=0; x<width; x++){
                for(int y=0; y<height; y++){
                finalColor = pixels[i];
                    setPixel(x,y,finalColor.r,finalColor.g,finalColor.b);
                    SDL_Flip(screen);
                    i++;
                }
         }
         saveBMP();
}


/// zapisanie pliku wynikowego
void Decoder::saveBMP()
{
    string name_save;
    cout<<"Wprowadz nazwe zapisu pliku ";
    cin>>name_save;

    size_t found = name_save.find(".bmp");

    if(found==-1)
    {
        name_save = name_save + ".bmp";
    }

    char *nazwa_save= new char[name_save.length()+1];
    strcpy( nazwa_save, name_save.c_str() );

    SDL_SaveBMP (screen, nazwa_save);
    cout<<"zapisano"<<endl;
}



void Decoder::setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{

    if ((x>=0) && (x<width) && (y>=0) && (y<height))
    {
        /* Zamieniamy poszczególne sk3adowe koloru na format koloru pixela */
        Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

        /* Pobieramy informacji ile bajtów zajmuje jeden pixel */
        int bpp = screen->format->BytesPerPixel;

        /* Obliczamy adres pixela */
        Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

        /* Ustawiamy wartooa pixela, w zale?nooci od formatu powierzchni*/
switch(bpp)
        {
        case 1: //8-bit
            *p = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4: //32-bit
            *(Uint32 *)p = pixel;
            break;

        }
        /* update the screen (aka double buffering) */
    }
}
void Decoder::czyscEkran(Uint8 R, Uint8 G, Uint8 B)
{

    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, R, G, B));
    SDL_Flip(screen);

}

int Decoder::setEkran()
{
    // console output
    freopen( "CON", "wt", stdout );
    freopen( "CON", "wt", stderr );

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    // make sure SDL cleans up before exit
    atexit(SDL_Quit);


    // create a new window
    screen = SDL_SetVideoMode(width,height, 32,SDL_RESIZABLE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set video: %s\n", SDL_GetError());
        return 1;
    }

    SDL_WM_SetCaption(tytul , NULL );
    // program main loop
    bool done = false;
    while (!done)
    {
        // message processing loop
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            // check for messages
            switch (event.type)
            {
            // exit if the window is closed
            case SDL_QUIT:
                done = true;
                break;
                // check for keypresses
            case SDL_KEYDOWN:
            {
                // exit if ESCAPE is pressed
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    done = true;
                if (event.key.keysym.sym == SDLK_1)
                    Funkcja1();
                if (event.key.keysym.sym == SDLK_2)
                    Funkcja2();
                if (event.key.keysym.sym == SDLK_b)
                    czyscEkran(0, 0, 10);
                break;
            }
            } // end switch
        } // end of message processing

    } // end main loop


    // all is well ;)


}




