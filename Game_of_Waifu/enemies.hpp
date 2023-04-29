#include <ncurses.h>
#include <stdlib.h>
//#include "save.cpp"


#define GRAVITY 0.4
#define JUMP_VELOCITY -3
#define HORIZONTAL_ACCELERATION 2
#define HORIZONTAL_MAX_VELOCITY 2

struct nemico {
    int life;
    int x, y;
    char character;
    bool fly;
    WINDOW *curwin;
    nemico * next;
};
typedef nemico* pnemici;

class Mob{
    protected:
        pnemici nemlist;
    public:
        Mob(WINDOW * win = NULL, int y = 0, int x = 0, char ch = ' ');
        int getX();
        int getY();
        char getChar();
        int random(int max);
        void stop();
        void InsMob(pnemici a);
        void Death(pnemici a);
        void update(pnemici a);
        void display(pnemici a);
};