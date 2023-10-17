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
        WINDOW *curwin;
    public:
        Mob(WINDOW * win = NULL, int l = 0, int s = 0, int d = 0, int y = 0, int x = 0, char ch = ' ', bool f = false);
        int getX();
        int getY();
        char getChar();
        int getlife();
        bool getfly();
        WINDOW* getwin();
        int getDmg();

        int random(int max);
        void stop();
        void mvleft();
        void mvright();
        void mvup();
        void mvdown();
};

struct nemico {
    Mob nem;
    nemico * next;
};
typedef nemico* pnemici;

pnemici InsMob(pnemici hd, Mob x);
pnemici Death(pnemici hd);
void update(pnemici hd, Player pl, int minY);
void display(pnemici hd);
void takeDmg(int dmg);


