#include <SDL/SDL.h>
#include "Compressor.h"
#include "DT_Color.h"
#include <list>

using namespace std;
/* konstruktor klasy tworz¹cy pocz¹tkowe has³a s³ownika
@param startColors lista kolorów obrazka
*/
Compressor::Compressor(list<DT_Color&> startColors, Picture* picture, const int& colorType) {
    this->picture = picture;
    this->colorType = colorType;

    for(list<DT_Color&>::iterator it = startColors.begin(); it != startColors.end(); it++;) {
        list<DT_Color&> color;
        color.push_back(*it);
        dictionarySize++;
        dictionary.insert(pair<int, List<DT_Color&>>(dictionarySize , color));
    }
}

/* w³aœciwa kompresja LZW
@return lista kolejno zapisanych pixeli wg. indeksów s³ownika LZW
*/
list<int> Compressor::getPixels(int colorType) {
    list<int> output;
    list<DT_Color&> c;

    int x = picture->getPictureWidth(),
        y = picture->getPictureHeight();

    for(int i = 0; i < x; i++) { //dla ka¿dego pixel w obrazku
        for(int j = 0; j < y; i++) {
            DT_Color& color = this->getPixel(x, y);

            c.push_back(color);

            if(this->getDictionaryIndex(c) > 0) { //je¿eli c+s jest w s³oniku
                 // c = c+s
            } else {
                output.push_back(this->getDictionaryIndex(c)); //dodajemy indeks c na wyjœcie

                //c = c+s
                dictionarySize++; //zwiekszamy licznik hase³ w s³owniku
                dictionary.insert(pair<int, list<DT_Color&>>(dictionarySize, c)); //dodanie nowego has³a do s³ownika

                c.remove(); //c = s
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

DT_Color& Compressor::getPixel(int x, int y) {
    return picture->getColor(x,y,this->colorType);
}

int Compressor::getDictionaryIndex(list<DT_Color&> c) {

    //dla ka¿dego elementu mapy dictionary sprawdzamy czy list<DT_Color&> maj¹ takie same wartosci/kolory a nie referencje!!

    for(map<int, List<DT_Color&>>::iterator it = dictionary.begin(); it != dictionary.end(); it++) {
        if(it->second->size() == c.size()) { //je¿eli listy maj¹ takie same rozmiary
            bool listsAreSame = true;
            for(list<DT_Color&>::iterator listIt = it->second->begin(); //iterujemy po listach
                list<DT_Color&>::iterator listItC = c.begin();
                listIt != it->second->end();
                listIt++) {

                    if(*listIt != listItC) //je¿eli chocia¿ jeden kolor jest inny
                        listsAreSame = false; //listy nie s¹ takie same
            }

            if(listsAreSame) { //je¿eli s¹ takie same to zwracamy indeks ze s³ownika LZW
                return &(it->first);
            }

        }
    }

    return -1; //-1 je¿eli c nie ma w s³owniku

}

