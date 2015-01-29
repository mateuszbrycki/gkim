#include "decoder.h"




int main ( int argc, char** argv )
{
    Decoder decoder;

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
    decoder.screen = SDL_SetVideoMode(decoder.width,decoder.width, 32,SDL_RESIZABLE|SDL_DOUBLEBUF);
    if ( !decoder.screen )
    {
        printf("Unable to set video: %s\n", SDL_GetError());
        return 1;
    }

    SDL_WM_SetCaption(decoder.tytul , NULL );
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
                    decoder.Funkcja1();
                if (event.key.keysym.sym == SDLK_2)
                    decoder.Funkcja2();
                if (event.key.keysym.sym == SDLK_b)
                    decoder.czyscEkran(0, 0, 10);
                break;
            }
            } // end switch
        } // end of message processing

    } // end main loop


    // all is well ;)



    return 0;
}
