#include "enemies.hpp"

Mob::Mob (int y, int x, int l, int s, int d, int as, char ch, int m, bool fl, bool rn, int color, int type) {
    this->stats.life = l;
    this->stats.speed = s;
    this->stats.dmg = d;
    this->stats.atkSpeed = as;
    this->x = x;
    this->y = y;
    this->character = ch;
    this->fly = fl;
    this->ranged = rn;
    this->type = type;
    this->color = color;
    this->moneyDrop = m;
}

int absolute(int x){
    if (x<0) return -x;
    else return x;
}

/*get*/
int Mob::getX() {return this->x;}
int Mob::getY() {return this->y;}
int Mob::getType() {return this->type;}
char Mob::getChar() {return this->character;}
int Mob::getlife() {return this->stats.life;}
void Mob::setlife(int l) {this->stats.life = l;}
bool Mob::getfly() {return this->fly;}
bool Mob::getRanged() {return this->ranged;}
int Mob::getspeed() {return this->stats.speed;}
int Mob::getAtkSpeed() {return this->stats.atkSpeed;}
int Mob::getDmg() {return this->stats.dmg;}
int Mob::getColor() {return this->color;}
int Mob::getMoneyDrop() {return this->moneyDrop;}

/*movimenti*/
void Mob::mvleft(){this->x--;}
void Mob::mvright(){this->x++;}
void Mob::mvup(){this->y--;}
void Mob::mvdown(){this->y++;}
void Mob::setY(int nY) {this->y = nY;}

/*Danno al Mob*/
void Mob::NemDmg(int dmg){this->stats.life -= dmg;};

/*Danno al Player*/
void takeDmg(int dmg) {
    int total = current_game.getVita() - dmg;
    if(total < 0) total = 0;
    current_game.setVita(total);
}

/*funzioni di inserimento dei diversi mob*/
pnemici InsMob(pnemici hd, Mob x) {pnemici nhd = new nemico; nhd->nem = x; nhd->next = hd; return nhd;}
pnemici InsZombie(pnemici& hd, int y, int x, int lv) {return InsMob(hd, Mob (y, x, lv+1, 10, (lv/2)+1, 0, 'Z', 1, false, false, 10, 0));}
pnemici InsGolem(pnemici& hd, int y, int x, int lv) {return InsMob(hd, Mob (y, x, 3+lv+lv/2, 20, lv+1, 0, 'G', 3, false, false, 11, 1));}
pnemici InsCerbottaniere(pnemici& hd, int y, int x, int lv) {return InsMob(hd, Mob (y, x, lv+1, 7, (lv/2)+1, 65, 'C', 2, false, true, 12, 2));}
pnemici InsBat(pnemici& hd, int y, int x, int lv) {return InsMob(hd, Mob (y, x, (lv/3)+1, 5, lv+1, 50, 'V', 1, true, true, 20, 10));}
pnemici InsDemon(pnemici& hd, int y, int x, int lv) {return InsMob(hd, Mob (y, x, (lv/2)+1, 13, (lv/3)+lv+1, 80, 'D', 3, true, true, 21, 11));}

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
        current_game.setMoney(current_game.getMoney()+hd->nem.getMoneyDrop());
        pnemici dhd = hd; 
        hd = hd->next;
        dhd = NULL;
        delete(dhd);
    }
    
    pnemici nhd = hd;
    
    while (hd != NULL && hd->next != NULL){
        if (hd->next->nem.getlife() <= 0) {
            current_game.setMoney(current_game.getMoney()+hd->nem.getMoneyDrop());
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

void checkMin(WINDOW * win, pnemici hd, int minY){
    if (!hd->nem.getfly() && hd->nem.getY() != minY) {
        mvwaddch(win, hd->nem.getY(), hd->nem.getX(), ' ');
        hd->nem.setY(minY);
    }
    if (hd->nem.getfly() && hd->nem.getY() > minY-5) {
        mvwaddch(win, hd->nem.getY(), hd->nem.getX(), ' ');
        hd->nem.setY(minY-5);
    }
}

void playerContactDmg(Player* pl, Mob nem, int ActualTick){
    if (pl->getX() == nem.getX() && pl->getY() == nem.getY()){
        if (pl->getLastHit() < ActualTick-80) {
            if (nem.getRanged()) takeDmg(1);
            else takeDmg(nem.getDmg()); 
            pl->updateLastHit(ActualTick);
        }
    }
}

void mobSwordDmg(Player* pl, Mob& nem, int ds){
    swordXY spada = pl->swordInfo();
    if (nem.getY() == spada.sY && absolute(nem.getX() - pl->getX()) <= spada.len && (nem.getX() - pl->getX())*ds <= 0 && pl->isSwording()){
        nem.NemDmg(current_game.getInventory()->getBarItem(0,current_game.getInventory()->getSelected()).getModifier(1));
    }
}

void mobShootDmg(Player* pl, Mob& nem){
    if (pl->getBulletX() == nem.getX() && pl->getBulletY() == nem.getY()){
        nem.NemDmg(current_game.getInventory()->getBarItem(0,current_game.getInventory()->getSelected()).getModifier(1));
        pl->stopBullet();
    }
}

void update(pnemici hd, Player* pl, int ActualTick, WINDOW * win, pbullets& bullHd) {       // simil pathfinding
    int yMax, xMax;
    getmaxyx(win, yMax, xMax);   
    pcoords Chd = NULL;

    if(current_game.getMap() == current_game.getLevel()) {
        while (hd != NULL) {
            int minY = calcYmin(hd->nem.getX());
        /*controllo sempre che non siano sotto il blocco minimo*/
            checkMin(win, hd, minY);
        /*se è il loro turno, si muovono*/
            if (ActualTick % (hd->nem.getspeed()) == 0){
                mvwaddch(win, hd->nem.getY(), hd->nem.getX(), ' ');
                if (!hd->nem.getfly()){         // mob non volanti (sx, dx)
                    if (pl->getX() < hd->nem.getX() && !InList(Chd, hd->nem.getX()-1, hd->nem.getY())) 
                        hd->nem.mvleft();
                    else if (pl->getX() > hd->nem.getX() && !InList(Chd, hd->nem.getX()+1, hd->nem.getY())) 
                        hd->nem.mvright();
                    Chd = InsCoords(Chd, hd->nem.getX(), hd->nem.getY());
                } else if (hd->nem.getfly()){   // mob volanti (sx, dx, su, giu)
                    if (pl->getX() < hd->nem.getX() && !InList(Chd, hd->nem.getX()-1, hd->nem.getY())) 
                        hd->nem.mvleft();
                    else if (pl->getX() > hd->nem.getX() && !InList(Chd, hd->nem.getX()+1, hd->nem.getY())) 
                        hd->nem.mvright();
                    if (pl->getY() < hd->nem.getY() && !InList(Chd, hd->nem.getX(), hd->nem.getY()-1)) 
                        hd->nem.mvup();
                    else if (pl->getY() > hd->nem.getY() && hd->nem.getY() < minY-5 && !InList(Chd, hd->nem.getX(), hd->nem.getY()+1)) 
                        hd->nem.mvdown();
                    Chd = InsCoords(Chd, hd->nem.getX(), hd->nem.getY());
                }
            }

        /*gestione spari*/
            int ds = 0;
            if (hd->nem.getX() < pl->getX()) ds = 1;
            else if(hd->nem.getX() >= pl->getX()) ds = -1;
            if (hd->nem.getfly()) ds = 0;
            if (hd->nem.getRanged() && (ActualTick % (hd->nem.getAtkSpeed()) == 0)) 
                bullHd = addBullet(bullHd, hd->nem.getX(), hd->nem.getY(), ds, hd->nem.getDmg());

            playerContactDmg(pl, hd->nem, ActualTick);      // danni da contatto al player
            mobSwordDmg(pl, hd->nem, ds);                   // danni da spada al mob
            mobShootDmg(pl, hd->nem);                       // danni da freccia al mob

            hd = hd->next;
        }
        Chd = MobClearList(Chd);
    }
}

void display(pnemici hd, WINDOW * win) {
    init_pair(10, COLOR_RED, COLOR_GREEN);
    init_pair(11, COLOR_WHITE, 245);
    init_pair(12, COLOR_BLACK, COLOR_CYAN);
    init_pair(20, COLOR_WHITE, COLOR_BLACK);
    init_pair(21, COLOR_WHITE, COLOR_BLACK);
    if(current_game.getMap() == current_game.getLevel())
        while(hd != NULL){
            wattron(win, COLOR_PAIR(hd->nem.getColor()));
            mvwaddch(win, hd->nem.getY(), hd->nem.getX(), hd->nem.getChar());
            wattroff(win, COLOR_PAIR(hd->nem.getColor()));
            hd = hd->next;
        }
}