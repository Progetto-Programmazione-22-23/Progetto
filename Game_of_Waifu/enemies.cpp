#include "enemies.hpp"

Mob::Mob (int y, int x, int l, int s, int d, char ch, bool fl, int color) {
    this->life = l;
    this->speed = s;
    this->dmg = d;
    this->x = x;
    this->y = y;
    this->character = ch;
    this->fly = fl;
    this->color = color;
}

/*get*/
int Mob::getX() {return this->x;}
int Mob::getY() {return this->y;}
char Mob::getChar() {return this->character;}
int Mob::getlife() {return this->life;}
bool Mob::getfly() {return this->fly;}
int Mob::getspeed() {return this->speed;}
int Mob::getDmg() {return this->dmg;}
int Mob::getColor() {return this->color;}

/*generazione di numeri random*/
int Mob::random(int max) {return rand() % max;}

/*movimenti*/
void Mob::mvleft(){this->x--;}
void Mob::mvright(){this->x++;}
void Mob::mvup(){this->y--;}
void Mob::mvdown(){this->y++;}
void Mob::setmin(int ym) {this->y = ym;}

/*Danno al Mob*/
void Mob::NemDmg(int dmg){this->life -= dmg;};

/*Danno al Player*/
void takeDmg(int dmg) {
    int total = current_game.getVita() - dmg;
    if(total < 0) total = 0;
    current_game.setVita(total);
}

/*funzioni di inserimento dei diversi mob*/
pnemici InsMob(pnemici hd, Mob x) {pnemici nhd = new nemico; nhd->nem = x; nhd->next = hd; return nhd;}
pnemici InsZombie(pnemici& hd, int y, int x) {Mob Zombie(y, x, 2, 10, 1, 'Z', false, 10); return InsMob(hd, Zombie);}
pnemici InsGolem(pnemici& hd, int y, int x) {Mob Golem(y, x, 5, 20, 3, 'G', false, 11); return InsMob(hd, Golem);}
pnemici InsBat(pnemici& hd, int y, int x) {Mob Bat(y, x, 1, 5, 1, 'V', true, 12); return InsMob(hd, Bat);}
pnemici InsDemon(pnemici& hd, int y, int x) {Mob Demon(y, x, 3, 13, 2, 'D', true, 13); return InsMob(hd, Demon);}

/*funzioni di gestione della lista di mob*/
pnemici Death(pnemici& hd) {
    if (hd == NULL) return NULL;
    
    while (hd != NULL && hd->nem.getlife() <= 0){
        pnemici dhd = hd; 
        hd = hd->next;
        dhd = NULL;
        delete(dhd);
    }
    
    pnemici nhd = hd;
    
    while (hd != NULL && hd->next != NULL){
        if (hd->next->nem.getlife() <= 0) {
            pnemici dhd = hd->next;
            hd->next = hd->next->next;
            dhd = NULL;
            delete(dhd);
        } else {
            hd = hd->next;
        }
    }
    
    return nhd;
}

void update(pnemici hd, Player* pl, int ActualTick, WINDOW * win) {       // simil pathfinding  
    if(current_game.getMap() == current_game.getLevel()) {
        while (hd != NULL) {
            int minY = calcYmin(hd->nem.getX());
            if (ActualTick % (hd->nem.getspeed()) == 0){
                mvwaddch(win, hd->nem.getY(), hd->nem.getX(), ' ');
                if (!hd->nem.getfly()){
                    if (hd->nem.getY() != minY) hd->nem.setmin(minY);
                    if (pl->getX() < hd->nem.getX()) hd->nem.mvleft();
                    else if (pl->getX() > hd->nem.getX()) hd->nem.mvright();
                } else if (hd->nem.getfly()){
                    if (hd->nem.getY() > minY-5) hd->nem.setmin(minY-5);
                    if (pl->getX() < hd->nem.getX()) hd->nem.mvleft();
                    else if (pl->getX() > hd->nem.getX()) hd->nem.mvright();
                    if (pl->getY() < hd->nem.getY()) hd->nem.mvup();
                    else if (pl->getY() > hd->nem.getY() && hd->nem.getY() < minY-5) hd->nem.mvdown();
                }
            }
            
            if (pl->getX() == hd->nem.getX() && pl->getY() == hd->nem.getY()){
                if (pl->getLastHit() < ActualTick-75){takeDmg(hd->nem.getDmg()); pl->UpdateLastHit(ActualTick);}; // danni al player
                hd->nem.NemDmg(1);
            }
            hd = hd->next;
        }
    }
}

void display(pnemici hd, WINDOW * win) {
    init_pair(10, COLOR_RED, COLOR_GREEN);
    init_pair(11, COLOR_WHITE, 245);
    init_pair(12, COLOR_WHITE, COLOR_BLACK);
    init_pair(13, COLOR_WHITE, COLOR_BLACK);
    if(current_game.getMap() == current_game.getLevel())
        while(hd != NULL){
            wattron(win, COLOR_PAIR(hd->nem.getColor()));
            mvwaddch(win, hd->nem.getY(), hd->nem.getX(), hd->nem.getChar());
            wattroff(win, COLOR_PAIR(hd->nem.getColor()));
            hd = hd->next;
        }
}