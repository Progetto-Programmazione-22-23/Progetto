#include <ncurses.h>
#include <stdlib.h>
#include "player.cpp"
//#include "save.cpp"
int NumMob = 5;

class Mob{
    protected:
        int life, speed, dmg, type, atkSpeed;
        int x, y;
        char character;
        bool fly, ranged;
        int color;
    public:
        Mob(int y = 0, int x = 0, int l = 0, int s = 0, int d = 0, int as = 0, char ch = ' ', bool f = false, bool r = false, int color = 0, int type = 0);
        int getX();
        int getY();
        int getType();
        char getChar();
        int getlife();
        void setlife(int l);
        bool getfly();
        bool getRanged();
        int getspeed();
        WINDOW* getwin();
        int getDmg();
        int getColor();

        int random(int max);
        void stop();
        void mvleft();
        void mvright();
        void mvup();
        void mvdown();
        void setmin(int ym);
        void NemDmg(int dmg);
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
void update(pnemici hd, Player pl, int ActualTick, WINDOW * win);
void display(pnemici hd, WINDOW * win);
void takeDmg(int dmg);