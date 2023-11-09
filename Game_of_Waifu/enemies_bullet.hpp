#include <ncurses.h>

int maxShootDistance = 20;

struct shoot {
    int xBull;
    int yBull;
    int direction;
    int bDmg;
    int distance;
}; 

struct bullet {
    shoot bull;
    bullet* next;
};
typedef bullet* pbullets;

pbullets addBullet(pbullets& hd, int x, int y, int ds);
pbullets removeShoot(pbullets& hd);
void moveShoot(pbullets hd, WINDOW * win);