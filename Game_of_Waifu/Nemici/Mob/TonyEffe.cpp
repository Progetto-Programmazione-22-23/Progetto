#include "TonyEffe.hpp"

Tony::Tony(WINDOW * win, int y, int x, int l, char c):NemicoTerra(win, y, x){
    this->terra = true;
    this->life = 10;
    this->character = 'T';
}