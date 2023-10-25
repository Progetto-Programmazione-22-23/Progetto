#include "map_setting.hpp"

void MobSpawn(int len, pnemici& hd){
    // mapgenerator(win);
    srand(time(NULL));
    int i = 0;
    while (i<5){
        int Xspawn = rand()%(len);
        int MobType = rand()%3;
        if (MobType == 0) hd = InsZombie(hd, calcYmin(Xspawn), Xspawn);
        else if (MobType == 1) hd = InsGolem(hd, calcYmin(Xspawn), Xspawn);
        else if (MobType == 2) hd = InsBat(hd, calcYmin(Xspawn) - 5, Xspawn);
        else hd = InsZombie(hd, calcYmin(Xspawn), Xspawn); 
        i++;
    }
}

void GoNext(WINDOW * win, int len, pnemici& hd){
    wclear(win);
    int n = current_game.getMap();
    current_game.setMap(n+1);
    
    char mapname[20];
    sprintf(mapname, "map/%d.txt", n+1);
    ifstream f(mapname);

    if(f.good()) regenOldMap(win, false);
    else {mapgenerator(win); MobSpawn(len, hd);}
}

void GoPrev(WINDOW * win) {
    wclear(win);
    current_game.setMap(current_game.getMap()-1);
    regenOldMap(win, false);
}

void ChangeMap(Player* pl, WINDOW * win, int end, int yMax, pnemici& hd){
    if(pl->getX() >= end-2 && hd == NULL){        // solo se la lista di nemici è vuota 
    pl->Teleport(4, yMax-3);
    GoNext(win, end, hd);
  }
  else if(pl->getX() <= 1 && current_game.getMap()>0) {
    pl->Teleport(end-4, yMax-3);
    GoPrev(win);
  } 
}