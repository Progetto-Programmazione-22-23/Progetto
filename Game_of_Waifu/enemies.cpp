#include "enemies.hpp"

Mob::Mob (int y, int x, int l, int s, int d, char ch, bool fl) {
    this->life = l;
    this->speed = s;
    this->dmg = d;
    this->x = x;
    this->y = y;
    this->character = ch;
    this->fly = fl;
}

/*get*/
int Mob::getX() {return this->x;}
int Mob::getY() {return this->y;}
char Mob::getChar() {return this->character;}
int Mob::getlife() {return this->life;}
bool Mob::getfly() {return this->fly;}
int Mob::getspeed() {return this->speed;}
int Mob::getDmg() {return this->dmg;}

/*generazione di numeri random*/
int Mob::random(int max) {return rand() % max;}

/*movimenti*/
void Mob::mvleft(){this->x--;}
void Mob::mvright(){this->x++;}
void Mob::mvup(){this->y--;}
void Mob::mvdown(){this->y++;}
void Mob::setmin(int ym) {this->y = ym;}

/*funzioni di inserimento dei diversi mob*/
pnemici InsMob(pnemici hd, Mob x) {
    pnemici nhd = new nemico;
    nhd->nem = x;
    nhd->next = hd;
    return nhd;
}
pnemici InsZombie(pnemici hd, int y, int x) {Mob Zombie(y, x, 2, 10, 1, 'Z', false); InsMob(hd, Zombie);}
pnemici InsGolem(pnemici hd, int y, int x) {Mob Golem(y, x, 5, 20, 3, 'G', false); InsMob(hd, Golem);}
pnemici InsBat(pnemici hd, int y, int x) {Mob Bat(y, x, 1, 5, 1, 'V', true); InsMob(hd, Bat);}

/*funzioni di gestione della lista di mob*/
pnemici Death(pnemici hd) {
    while (hd->nem.getlife() == 0){
        pnemici dhd = hd;
        hd = hd->next;
        dhd = NULL;
    }
    pnemici nhd = hd;
    while (hd->next != NULL){
        pnemici dhd = hd->next;
        if (hd->next->nem.getlife() == 0){hd->next = hd->next->next; dhd = NULL;}
        hd = hd->next;
    }
    return nhd;
}

void update(pnemici hd, Player pl, int tic, WINDOW * win) {       // simil pathfinding
    while (hd != NULL) {
        int minY = calcYmin(hd->nem.getX());
        if (tic % (hd->nem.getspeed()) == 0){
            mvwaddch(win, hd->nem.getY(), hd->nem.getX(), ' ');
            if (!hd->nem.getfly()){
                if (hd->nem.getY() != minY) hd->nem.setmin(minY);
                if (pl.getX() < hd->nem.getX()) hd->nem.mvleft();
                else if (pl.getX() > hd->nem.getX()) hd->nem.mvright();
            } else if (hd->nem.getfly()){
                if (hd->nem.getY() > minY-5) hd->nem.setmin(minY-5);
                if (pl.getX() < hd->nem.getX()) hd->nem.mvleft();
                else if (pl.getX() > hd->nem.getX()) hd->nem.mvright();
                if (pl.getY() < hd->nem.getY()) hd->nem.mvup();
                else if (pl.getY() > hd->nem.getY() && hd->nem.getY() < minY-5) hd->nem.mvdown();
            }
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

void display(pnemici hd, WINDOW * win) {
    while(hd != NULL){
        mvwaddch(win, hd->nem.getY(), hd->nem.getX(), hd->nem.getChar());
        hd = hd->next;
    }
}