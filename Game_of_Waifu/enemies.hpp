#include <ncurses.h>
#include <stdlib.h>
//#include "save.cpp"

class Mob{
    protected:
        int life;
        int x, y;
        char character;
        bool fly;
        WINDOW *curwin;
    public:
        Mob(WINDOW * win = NULL, int l = 0, int y = 0, int x = 0, char ch = ' ', bool f = false);
        int getX();
        int getY();
        char getChar();
        int getlife();
        WINDOW* getwin();
        int random(int max);
        void stop();
};

struct nemico {
    Mob nem;
    nemico * next;
};
typedef nemico* pnemici;

class Mobs{
    protected:
        pnemici Moblist;
    public:
        void InsMob(pnemici hd);
        void Death(pnemici hd, nemico x);
        void update(pnemici hd);
        void display(pnemici hd);
};