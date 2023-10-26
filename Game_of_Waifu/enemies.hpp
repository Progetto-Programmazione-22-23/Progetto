#include <ncurses.h>
#include <stdlib.h>
#include "player.cpp"
//#include "save.cpp"

class Mob{
    protected:
        int life, speed, dmg;
        int x, y;
        char character;
        bool fly;
    public:
        Mob(int y = 0, int x = 0, int l = 0, int s = 0, int d = 0, char ch = ' ', bool f = false);
        int getX();
        int getY();
        char getChar();
        int getlife();
        bool getfly();
        int getspeed();
        WINDOW* getwin();
        int getDmg();

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
pnemici InsZombie(pnemici& hd, int y, int x);
pnemici InsGolem(pnemici& hd, int y, int x);
pnemici InsBat(pnemici& hd, int y, int x);
pnemici InsDemon(pnemici& hd, int y, int x);


pnemici Death(pnemici& hd);
void update(pnemici hd, Player pl, int ActualTick, WINDOW * win);
void display(pnemici hd, WINDOW * win);
void takeDmg(int dmg);


