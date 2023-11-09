#include "enemies_bullet.hpp"

pbullets addBullet(pbullets& hd, int x, int y, int ds) {
    pbullets nhd = new bullet; 
    nhd->bull.xBull = x;
    nhd->bull.yBull = y;
    nhd->bull.direction = ds;
    nhd->bull.distance = 0;
    nhd->bull.bDmg = 1;
    nhd->next = hd; 
    return nhd;
}

pbullets removeShoot(pbullets& hd) {
    if (hd == NULL) return NULL;
    
    while (hd != NULL && hd->bull.distance >= maxShootDistance){
        pbullets dhd = hd; 
        hd = hd->next;
        dhd = NULL;
        delete(dhd);
    }
    
    pbullets nhd = hd;
    
    while (hd != NULL && hd->next != NULL){
        if (hd->next->bull.distance >= maxShootDistance) {
            pbullets dhd = hd->next;
            hd->next = hd->next->next;
            dhd = NULL;
            delete(dhd);
        } else {
            hd = hd->next;
        }
    }
    
    return nhd;
}

void moveShoot(pbullets hd, WINDOW * win){
    while (hd != NULL) {
        mvwaddch(win, hd->bull.yBull, hd->bull.xBull, ' ');
        if (hd->bull.direction == -1) {hd->bull.xBull--; mvwaddch(win, hd->bull.yBull, hd->bull.xBull, '<'); hd->bull.distance++;}
        else if (hd->bull.direction == 1) {hd->bull.xBull++; mvwaddch(win, hd->bull.yBull, hd->bull.xBull, '>'); hd->bull.distance++;}
        else if (hd->bull.direction == 0) {hd->bull.yBull++; mvwaddch(win, hd->bull.yBull, hd->bull.xBull, 'v'); hd->bull.distance++;}

        if (hd->bull.distance >= maxShootDistance) mvwaddch(win, hd->bull.yBull, hd->bull.xBull, ' ');
        hd = hd->next;
    }
}