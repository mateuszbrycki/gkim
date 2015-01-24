/*Dekorator do SDL_COLOR - przeładowanie operatora != */

#include "DT_Color.h"
#include <SDL/SDL.h>

DT_Color::DT_Color(SDL_Color color) {
    this->color = color;
}

int DT_Color::operator!=(const SDL_Color &second) {
    if((this->color.r != second.r) || (this->color.g != second.g) || (this->color.b != second.b)) {
        return -1;
    }

    return 1;
}
