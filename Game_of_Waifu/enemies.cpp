#include "enemies.hpp"

Mob::Mob (int y, int x, int l, int s, int d, char ch, bool fl, int color, int type) {
    this->life = l;
    this->speed = s;
    this->dmg = d;
    this->x = x;
    this->y = y;
    this->character = ch;
    this->fly = fl;
    this->type = type;
    this->color = color;
}

/*get*/
int Mob::getX() {return this->x;}
int Mob::getY() {return this->y;}
int Mob::getType() {return this->type;}
char Mob::getChar() {return this->character;}
int Mob::getlife() {return this->life;}
void Mob::setlife(int l) {this->life = l;}
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
pnemici InsZombie(pnemici& hd, int y, int x, int lv) {Mob Zombie(y, x, lv+1, 10, (lv/2)+1, 'Z', false, 10, 0); return InsMob(hd, Zombie);}
pnemici InsGolem(pnemici& hd, int y, int x, int lv) {Mob Golem(y, x, 3+lv+lv/2, 20, lv+1, 'G', false, 11, 1); return InsMob(hd, Golem);}
pnemici InsBat(pnemici& hd, int y, int x, int lv) {Mob Bat(y, x, 1, 5, 1, 'V', true, 12, 2); return InsMob(hd, Bat);}
pnemici InsDemon(pnemici& hd, int y, int x, int lv) {Mob Demon(y, x, 3, 13, 2, 'D', true, 13, 3); return InsMob(hd, Demon);}

/*gestione coordinate*/
pcoords InsCoords(pcoords& hd, int mx, int my) {
    pcoords Nc = new coords;
    Nc->x = mx;
    Nc->y = my;
    Nc->next = hd;
    return Nc;
}

pcoords MobClearList(pcoords& hd) {
    while (hd != NULL){
        pcoords nhd = hd;
        hd = hd->next;
        nhd = NULL;
        delete (nhd);
    }
    return NULL;
}

bool InList(pcoords& hd, int mx, int my) {
    while (hd != NULL){
        if (mx == hd->x && my == hd->y) return true;
        hd = hd->next;
    }
    return false;
}

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
    int yMax, xMax;
    getmaxyx(win, yMax, xMax);   
    pcoords Chd = NULL;

    if(current_game.getMap() == current_game.getLevel()) {
        while (hd != NULL) {
            int minY = calcYmin(hd->nem.getX());
            if (ActualTick % (hd->nem.getspeed()) == 0){
                mvwaddch(win, hd->nem.getY(), hd->nem.getX(), ' ');
                if (!hd->nem.getfly()){
                    if (hd->nem.getY() != minY) hd->nem.setmin(minY);
                    if (pl->getX() < hd->nem.getX() && !InList(Chd, hd->nem.getX()-1, hd->nem.getY())) hd->nem.mvleft();
                    else if (pl->getX() > hd->nem.getX() && !InList(Chd, hd->nem.getX()+1, hd->nem.getY())) hd->nem.mvright();
                    Chd = InsCoords(Chd, hd->nem.getX(), hd->nem.getY());
                } else if (hd->nem.getfly()){
                    if (hd->nem.getY() > minY-5) hd->nem.setmin(minY-5);
                    if (pl->getX() < hd->nem.getX() && !InList(Chd, hd->nem.getX()-1, hd->nem.getY())) hd->nem.mvleft();
                    else if (pl->getX() > hd->nem.getX() && !InList(Chd, hd->nem.getX()+1, hd->nem.getY())) hd->nem.mvright();
                    if (pl->getY() < hd->nem.getY() && !InList(Chd, hd->nem.getX(), hd->nem.getY()-1)) hd->nem.mvup();
                    else if (pl->getY() > hd->nem.getY() && hd->nem.getY() < minY-5 && !InList(Chd, hd->nem.getX(), hd->nem.getY()+1)) hd->nem.mvdown();
                    Chd = InsCoords(Chd, hd->nem.getX(), hd->nem.getY());
                }
            }
            
            if (pl->getX() == hd->nem.getX() && pl->getY() == hd->nem.getY()){
                if (pl->getLastHit() < ActualTick-80){takeDmg(hd->nem.getDmg()); pl->updateLastHit(ActualTick);}; // danni al player
            }
            if (pl->getBulletX() == hd->nem.getX() && pl->getBulletY() == hd->nem.getY()){
                hd->nem.NemDmg(100);
                pl->stopBullet();
            }
            hd = hd->next;
        }
        Chd = MobClearList(Chd);
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