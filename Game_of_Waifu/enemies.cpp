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

pnemici Mobs::InsMob(pnemici hd, Mob x) {
    pnemici nhd = NULL;
    nhd->nem = x;
    nhd->next = hd;
    return nhd;
}

void Mobs::Death(pnemici hd) {
    while (hd->nem.getlife() == 0){
         hd = hd->next;
    }
    while (hd->next != NULL){
        if (hd->next->nem.getlife() == 0) hd->next = hd->next->next;
        hd = hd->next;
    }
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