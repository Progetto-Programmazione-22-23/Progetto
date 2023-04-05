#include "TonyEffe.hpp"

Tony::Tony(WINDOW * win, int y, int x, int xv, int yv) : Nemico(win, yv, xv){
    this->flyer = false;
    this->character = 'T';
    this->life = 10;
}

