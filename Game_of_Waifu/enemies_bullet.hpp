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

pbullets addBullet(pbullets& hd, int x, int y, int ds, int bD);
pbullets removeShoot(pbullets& hd);
pbullets moveShoot(pbullets& hd, WINDOW * win);
void dmgPlayer(shoot sh);
bool checkBulletCollision(shoot x, WINDOW * win);
bool checkBullPlayerColl(shoot x, WINDOW * win);