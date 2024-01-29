#include "enemies_bullet.hpp"

pbullets addBullet(pbullets& hd, int x, int y, int ds, int bD) {
    pbullets nhd = new bullet; 
    nhd->bull.xBull = x;
    nhd->bull.yBull = y;
    nhd->bull.direction = ds;
    nhd->bull.distance = 0;
    nhd->bull.bDmg = bD;
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

bool checkBulletCollision(shoot sh, WINDOW * win){
    if (mvwinch(win, sh.yBull+1, sh.xBull) == '=' && sh.direction == 0) return true;
    if (mvwinch(win, sh.yBull+1, sh.xBull) == '>' && sh.direction == 0) return true;
    if (mvwinch(win, sh.yBull+1, sh.xBull) == '<' && sh.direction == 0) return true;
    if (mvwinch(win, sh.yBull+1, sh.xBull) == '_' && sh.direction == 0) return true;
    if (mvwinch(win, sh.yBull+1, sh.xBull) == '/' && sh.direction == 0) return true;
    if (mvwinch(win, sh.yBull+1, sh.xBull) == '\\' && sh.direction == 0) return true;

    if (mvwinch(win, sh.yBull, sh.xBull+1) == '/' && sh.direction == 1) return true;
    if (mvwinch(win, sh.yBull, sh.xBull-1) == '\\' && sh.direction == -1) return true;

    return false;
}

void dmgPlayer(shoot sh){
    current_game.setVita(current_game.getVita()-sh.bDmg);
}

bool checkBullPlayerColl(shoot sh, WINDOW * win){
    if (mvwinch(win, sh.yBull+1, sh.xBull) == '@' && sh.direction == 0) {
        dmgPlayer(sh);
        return true; 
    }
    if (mvwinch(win, sh.yBull, sh.xBull+1) == '@' && sh.direction == 1){
        dmgPlayer(sh);
        return true; 
    }
    if (mvwinch(win, sh.yBull, sh.xBull-1) == '@' && sh.direction == -1){
        dmgPlayer(sh);
        return true; 
    }

    return false;
}

pbullets moveShoot(pbullets& hd, WINDOW * win){
    pbullets nhd = hd;

    while (hd != NULL) {
        if (checkBulletCollision(hd->bull, win) || checkBullPlayerColl(hd->bull, win)) hd->bull.distance = maxShootDistance-1;

        mvwaddch(win, hd->bull.yBull, hd->bull.xBull, ' ');
        if (hd->bull.direction == -1) {hd->bull.xBull--; mvwaddch(win, hd->bull.yBull, hd->bull.xBull, '*'); hd->bull.distance++;}
        else if (hd->bull.direction == 1) {hd->bull.xBull++; mvwaddch(win, hd->bull.yBull, hd->bull.xBull, '*'); hd->bull.distance++;}
        else if (hd->bull.direction == 0) {hd->bull.yBull++; mvwaddch(win, hd->bull.yBull, hd->bull.xBull, 'v'); hd->bull.distance++;}
        
        if (hd->bull.distance >= maxShootDistance) mvwaddch(win, hd->bull.yBull, hd->bull.xBull, ' ');
        hd = hd->next;
    }

    return nhd;
}