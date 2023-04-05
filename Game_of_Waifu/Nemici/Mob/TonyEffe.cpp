#include "TonyEffe.hpp"

Tony::Tony(WINDOW * win, int y, int x, int l, char c, bool t):NemicoTerra(win, y, x){
    this->life = 10;
    this->character = 'T';
}