#include "enemies.hpp"

Mob::Mob (WINDOW * win, int l, int y, int x, char ch, bool fl) {
    this->curwin = win;
    this->life = l;
    this->x = x;
    this->y = y;
    this->character = ch;
}

int Mob::getX() {
    return this->x;
}

int Mob::getY() {
    return this->y;
}

char Mob::getChar() {
    return this->character;
}

WINDOW* Mob::getwin(){
    return this->curwin;
}

int Mob::getlife(){
    return this->life;
}

int Mob::random(int max) {
    return rand() % max;
}

void Mobs::InsMob(pnemici hd) {
    // headins o taleins, ancora non so 
}

void Mobs::Death(pnemici hd, nemico x) {
    
}

void Mobs::update(pnemici hd) {
    // movimento dei vari mob verso il player
    // simil pathfinding
}

void Mobs::display(pnemici hd) {
    while(hd != NULL){
        mvwaddch(hd->nem.getwin(), hd->nem.getY(), hd->nem.getX(), hd->nem.getChar());
        hd = hd->next;
    }
}