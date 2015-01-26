#include <SDL/SDL.h>
#include "Compressor.h"
#include <list>

using namespace std;
/* konstruktor klasy tworzacy poczatkowe hasla slownika
@param startColors lista kolorów obrazka
@param picture obiekt klasy Picture bedacy reprezentacja obrazka wejsciowego
*/
Compressor::Compressor(list<SDL_Color> startColors, Picture* picture) {
    this->picture = picture;

    for(list<SDL_Color>::iterator it = startColors.begin(); it != startColors.end(); it++) {
        list<SDL_Color> color;
        color.push_back(*it);
        dictionarySize++;
        dictionary.insert(pair<int, list<SDL_Color> >(dictionarySize , color));
    }
}

/* wlasciwa kompresja LZW
@return lista kolejno zapisanych pixeli wg. indeksów ssownika LZW
*/
list<int> Compressor::getPixels() {
    list<int> output;
    list<SDL_Color> c;

    int x = picture->getPictureWidth(),
        y = picture->getPictureHeight();

    for(int i = 0; i < x; i++) { //dla kazdego pixel w obrazku
        for(int j = 0; j < y; i++) {
            SDL_Color color = this->getPixel(x, y);

            c.push_back(color);

            if(this->getDictionaryIndex(c) > 0) { //jezeli c+s jest w sloniku
                 // c = c+s
            } else {
                output.push_back(this->getDictionaryIndex(c)); //dodajemy indeks c na wyjscie

                //c = c+s
                dictionarySize++; //zwiekszamy licznik hasel w slowniku
                dictionary.insert(pair<int, list<SDL_Color> >(dictionarySize, c)); //dodanie nowego hasla do slownika

                c.clear(); //c = s
                c.push_back(color);
            }
        }
    }

    //dla ostatniego pixela
    if(!c.empty()) {
        output.push_back(this->getDictionaryIndex(c));
    }

    return output;
}

/* pobiera piksel z obrazka w odpowiednim trybie koloru
@param Y polozenie pixela na osi Y
@return obiekt klasy DT_Color bedacy reprezentacjz piksela
*/
SDL_Color Compressor::getPixel(int x, int y) {
    return picture->getPixelColor(x,y);
}

/*
@param c lista kolorów, które nalezy odszukac w slowniku
@return zwraca pozycje w sloniku lub -1 jezeli slowa nie ma w slowniku
*/
int Compressor::getDictionaryIndex(list<SDL_Color> c) {

    //dla kazdego elementu mapy dictionary sprawdzamy czy list<DT_Color&> maja takie same wartosci/kolory a nie referencje!!

    for(map<int, list<SDL_Color> >::iterator it = dictionary.begin(); it != dictionary.end(); it++) {
        if((*it).second.size() == c.size()) { //jezeli listy maja takie same rozmiary
            bool listsAreSame = true;
            list<SDL_Color>::iterator listIt = (*it).second.begin();
            list<SDL_Color>::iterator listItC = c.begin();
            for(; listIt != (*it).second.end() && listItC != c.end(); listIt++, listItC++) {
                if(((*listIt).r != (*listItC).r) || ((*listIt).g != (*listItC).g) || ((*listIt).b != (*listItC).b))
                    listsAreSame = false;
            }

            if(listsAreSame) { //jezeli sa takie same to zwracamy indeks ze slownika LZW
                return (*it).first;
            }

        }
    }

    return -1; //-1 jezeli c nie ma w slowniku

}

