#include "enemies.hpp"

Mob::Mob (WINDOW * win, int l, int d, int y, int x, char ch, bool fl) {
    this->curwin = win;
    this->life = l;
    this->dmg = d;
    this->x = x;
    this->y = y;
    this->character = ch;
    this->fly = fl;
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

bool Mob::getfly(){
    return this->fly;
}

int Mob::getDmg() { return this->dmg;}

int Mob::random(int max) {
    return rand() % max;
}

void Mob::mvleft(){
    this->x--;
}

void Mob::mvright(){
    this->x++;
}

void Mob::mvup(){
    this->y--;
}

void Mob::mvdown(){
    this->y++;
}

pnemici InsMob(pnemici hd, Mob x) {
    pnemici nhd = new nemico;
    nhd->nem = x;
    nhd->next = hd;
    return nhd;
}

pnemici Death(pnemici hd) {
    while (hd->nem.getlife() == 0){
         hd = hd->next;
    }
    pnemici nhd = hd;
    while (hd->next != NULL){
        if (hd->next->nem.getlife() == 0) hd->next = hd->next->next;
        hd = hd->next;
    }
    return nhd;
}

void update(pnemici hd, Player pl, int minY) {                                        // simil pathfinding
    while (hd != NULL) {
        mvwaddch(hd->nem.getwin(), hd->nem.getY(), hd->nem.getX(), ' ');
        if (!hd->nem.getfly()){
            if (pl.getX() < hd->nem.getX()) hd->nem.mvleft();
            else if (pl.getX() > hd->nem.getX()) hd->nem.mvright();
        } else if (hd->nem.getfly()){
            if (pl.getX() < hd->nem.getX()) hd->nem.mvleft();
            else if (pl.getX() > hd->nem.getX()) hd->nem.mvright();
            if (pl.getY() < hd->nem.getY()) hd->nem.mvup();
            else if (pl.getY() > hd->nem.getY() && hd->nem.getY() < minY) hd->nem.mvdown();
        }
        if (pl.getX() == hd->nem.getX() && pl.getY() == hd->nem.getY())
            takeDmg(hd->nem.getDmg()); /*takedmg(this->dmg)*/ // danni al player
        hd = hd->next;
    }
}

void takeDmg(int dmg) {
    int total = current_game.getVita() - dmg;
    if(total < 0) total = 0;
    current_game.setVita(total);
}

void display(pnemici hd) {
    while(hd != NULL){
        mvwaddch(hd->nem.getwin(), hd->nem.getY(), hd->nem.getX(), hd->nem.getChar());
        hd = hd->next;
    }
}