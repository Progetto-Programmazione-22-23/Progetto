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
        // WINDOW *curwin;
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
};

// Mob Zombie(int y = 0, int x = 0, int l = 2, int s = 5, int d = 1, char ch = 'Z', bool f = false);
// Mob Golem(int y = 0, int x = 0, int l = 5, int s = 8, int d = 2, char ch = 'G', bool f = false);

// class Zombie: public Mob{
//     public:
//         Zombie(WINDOW * win = NULL, int y = 0, int x = 0, int l = 2, int s = 5, int d = 1, char ch = 'Z', bool f = false);
// };

// class Golem: public Mob{
//     public:
//         Golem(WINDOW * win = NULL, int y = 0, int x = 0, int l = 5, int s = 8, int d = 2, char ch = 'G', bool f = false);
// };

struct nemico {
    Mob nem;
    nemico * next;
};
typedef nemico* pnemici;

pnemici InsMob(pnemici hd, Mob x);
pnemici InsZombie(pnemici& hd, int y, int x);
pnemici InsGolem(pnemici& hd, int y, int x);
pnemici InsBat(pnemici& hd, int y, int x);


pnemici Death(pnemici hd);
void update(pnemici hd, Player pl, int tic, WINDOW * win);
void display(pnemici hd, WINDOW * win);
void takeDmg(int dmg);

void MobSpawn(int len, pnemici& hd);
