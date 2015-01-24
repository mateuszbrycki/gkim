#ifndef DT_COLOR_H
#define DT_COLOR_H

#include <SDL/SDL.h>

using namespace std;

class DT_Color {
public:
    DT_Color(SDL_Color color);
    int operator==(const SDL_Color &second);

private:
    SDL_Color color;
};

#endif
