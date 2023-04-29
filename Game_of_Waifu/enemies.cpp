#include "enemies.hpp"



Mob::Mob (WINDOW * win, int y, int x, char ch) {
    this->nemlist->curwin = win;
    this->nemlist->x = x;
    this->nemlist->y = y;
    this->nemlist->character = ch;
}

int Mob::getX() {
    return this->nemlist->x;
}

int Mob::getY() {
    return this->nemlist->y;
}

char Mob::getChar() {
    return this->nemlist->character;
}

int Mob::random(int max) {
    return rand() % max;
}

void Mob::InsMob(pnemici hd) {
    // headins o taleins, ancora non so 
}

void Mob::Death(pnemici hd) {
    // remove from list
}

void Mob::update(pnemici hd) {
    // movimento dei vari mob verso il player
    // simil pathfinding
}

void Mob::display(pnemici hd) {
    while(hd != NULL){
        mvwaddch(hd->curwin, hd->y, hd->x, hd->character);
        hd = hd->next;
    }
}