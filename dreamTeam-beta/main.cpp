#include <SDL/SDL.h>
#include "mainwindow.h"
#include <QApplication>

#undef qMain

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* screen = SDL_SetVideoMode(800,600,32,0);
    SDL_WM_SetCaption("Hello, C++ Lab", 0);

    SDL_Event evt;
    bool doWork=true;
    while(doWork) {
        while(SDL_PollEvent(&evt)) {
            if(evt.type == SDL_QUIT)
                doWork=false;
        }
        SDL_Flip(screen);
    }
    SDL_Quit();
    return 0;
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //return a.exec();
}
