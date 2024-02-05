#include <ncurses.h>
#include <stdlib.h>
#include "player.cpp"
#include "enemies_bullet.cpp"
//#include "save.cpp"
int NumMob = 5;

struct statistics {
    int life;
    int speed;
    int dmg;
    int atkSpeed;
};

int absolute(int x);

class Mob{
    protected:
        statistics stats;
        int type;
        int x, y;
        char character;
        bool fly, ranged;
        int color;
        int moneyDrop;
    public:
        Mob(int y = 0, int x = 0, int l = 0, int s = 0, int d = 0, int as = 0, char ch = ' ', int m = 0, bool f = false, bool r = false, int color = 0, int type = 0);
        int getX();
        int getY();
        int getType();
        char getChar();
        int getlife();
        void setlife(int l);
        bool getfly();
        bool getRanged();
        int getspeed();
        int getAtkSpeed();
        int getDmg();
        int getColor();
        int getBulletX();
        int getBulletY();
        int getMoneyDrop();

        void stop();
        void mvleft();
        void mvright();
        void mvup();
        void mvdown();
        void setY(int y);
        void NemDmg(int dmg);
        void chargeShoot(WINDOW * win, int x, int y, int direction);
        void enShoot(WINDOW * win, int x, int y, int direction);
        void flyEnShoot(WINDOW * win, int x, int y);
};

struct nemico {
    Mob nem;
    nemico * next;
};
typedef nemico* pnemici;



pnemici InsMob(pnemici hd, Mob x);
pnemici InsZombie(pnemici& hd, int y, int x, int lv);
pnemici InsGolem(pnemici& hd, int y, int x, int lv);
pnemici InsCerbottaniere(pnemici& hd, int y, int x, int lv);
pnemici InsBat(pnemici& hd, int y, int x, int lv);
pnemici InsDemon(pnemici& hd, int y, int x, int lv);

pcoords InsCoords(pcoords& hd, int mx, int my);
pcoords MobClearList(pcoords& hd);
bool InList(pcoords& hd, int mx, int my);

pnemici Death(pnemici& hd);
void checkMin(WINDOW * win, pnemici hd, int minY);

void playerContactDmg(Player* pl, Mob nem, int ActualTick);
void mobSwordDmg(Player* pl, Mob& nem, int ds);
void mobShootDmg(Player* pl, Mob& nem);
void update(pnemici hd, Player* pl, int ActualTick, WINDOW * win, pbullets& bullHd);
void display(pnemici hd, WINDOW * win);