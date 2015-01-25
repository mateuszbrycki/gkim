#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>

#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL/SDL.h>
#endif
#include <math.h>
#define pi 3.14

#include <iostream>
#include <string>
#include <cstddef>
#include <fstream>
#include <vector>
using namespace std;

    //zmienne
int width;
int height;
int pixelWidth;
int dictionaryStart;
int pictureStart;

vector<int> pictureRead;



string select_nazwa()
{
    string nazwa;
    cout<<"Wprowadz nazwe z którego pliku mam wczytac"<<endl;
    cin>>nazwa;
    return nazwa;
}

void open(string nazwa)
{

    fstream plik;

    // nie mam zielonego pojecia czemu w tym jebanym C:B trzeba to rzutowac jacys neardeltaczycy to pisali-.-
    char *name= new char[nazwa.length()+1];
    strcpy( name, nazwa.c_str() );

    plik.open(name);
    if(plik.good()==true)
    {
         // nie wiem czemu amelinium nie chce go otworzyc
        cout<<"otwarto";
        while(plik.eof()==true)
        {
            plik>>width;

            plik.seekg( +2,ios_base::beg ); //skok do przodu o 2 względem końca pliku
            if( plik.fail())
                cout << "Error! Nie udalo sie przesunac wewnetrznego wskaznika pliku" <<endl;
            plik>>height;

            plik.seekg( +5,ios_base::beg ); //skok do przodu o 5 względem końca pliku
            if( plik.fail())
                cout << "Error! Nie udalo sie przesunac wewnetrznego wskaznika pliku" <<endl;
            plik>>pixelWidth;


            plik.seekg( +8,ios_base::beg ); //skok do przodu o 8 względem końca pliku
            if( plik.fail())
                cout << "Error! Nie udalo sie przesunac wewnetrznego wskaznika pliku" <<endl;
            plik>>dictionaryStart;


            plik.seekg( +10,ios_base::beg ); //skok do przodu o 10 względem końca pliku
            if( plik.fail())
                cout << "Error! Nie udalo sie przesunac wewnetrznego wskaznika pliku" <<endl;
                plik>>pictureStart;
                pictureRead.push_back(pictureStart);
        }




        plik.close();
    }
    else
        cout<<"Blad otwarcia pliku"<<endl;


}

SDL_Surface *screen;
int width_ = 600;
int height_ = 450;
char const* tytul = "LZW";

void Funkcja1()// wcis 1 by zadzialalo
{

open(select_nazwa());

}




void setPixel(int x, int y, Uint8 R, Uint8 G, Uint8 B)
{
  if ((x>=0) && (x<width) && (y>=0) && (y<height))
  {
    /* Zamieniamy poszczególne sk³adowe koloru na format koloru pixela */
    Uint32 pixel = SDL_MapRGB(screen->format, R, G, B);

    /* Pobieramy informacji ile bajtów zajmuje jeden pixel */
    int bpp = screen->format->BytesPerPixel;

    /* Obliczamy adres pixela */
    Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;

    /* Ustawiamy wartoœæ pixela, w zale¿noœci od formatu powierzchni*/
    switch(bpp)
    {
        case 1: //8-bit
            *p = pixel;
            break;

        case 2: //16-bit
            *(Uint16 *)p = pixel;
            break;

        case 3: //24-bit
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
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



void czyscEkran(Uint8 R, Uint8 G, Uint8 B)
{
    SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, R, G, B));
    SDL_Flip(screen);

}

SDL_Color getPixel (int x, int y) {
    SDL_Color color ;
    Uint32 col = 0 ;
    if ((x>=0) && (x<width) && (y>=0) && (y<height)) {
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



int main ( int argc, char** argv )
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
    screen = SDL_SetVideoMode(width, height, 32,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set video: %s\n", SDL_GetError());
        return 1;
    }

    SDL_WM_SetCaption( tytul , NULL );
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

                        czyscEkran(0, 0, 10);          break;
                     }
            } // end switch
        } // end of message processing

    } // end main loop


    // all is well ;)
    printf("Exited cleanly\n");
    return 0;
}
