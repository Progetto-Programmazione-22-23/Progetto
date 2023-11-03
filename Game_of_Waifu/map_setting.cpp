#include "map_setting.hpp"

void MobSpawn(int len, pnemici& hd){
    // mapgenerator(win);
    srand(time(NULL));
    int i = 0;
    while (i<5){
        int Xspawn = 15 + rand()%(len-15);
        int MobType = rand()%NumMob;
        if (MobType == 0) hd = InsZombie(hd, calcYmin(Xspawn), Xspawn);
        else if (MobType == 1) hd = InsGolem(hd, calcYmin(Xspawn), Xspawn);
        else if (MobType == 2) hd = InsBat(hd, calcYmin(Xspawn) - 5, Xspawn);
        else if (MobType == 3) hd = InsDemon(hd, calcYmin(Xspawn) - 5, Xspawn);
        else hd = InsZombie(hd, calcYmin(Xspawn), Xspawn); 
        i++;
    }
}

void saveMobs(pnemici hd){
    std::ofstream out;
    out.open("enemies.txt");
    for(pnemici e = hd; e != NULL; e = e->next) {
        Mob m = e->nem;
        out<<m.getType()<<" "<<m.getlife()<<" "<<m.getX()<<" "<<m.getY()<<"\n";
    }
    out.close();
}

void mobRespawn(pnemici& hd) {
    std::ifstream in;
    in.open("enemies.txt");
    int type, life, x, y;
    while(in>>type>>life>>x>>y) {
        switch(type) {
        case 0:
            hd = InsZombie(hd, y, x);
            break;
        case 1:
            hd = InsGolem(hd, y, x);
            break;
        case 2:
            hd = InsBat(hd, y, x);
            break;
        case 3:
            hd = InsDemon(hd, y, x);
            break;
        default:
            break;
        }

        hd->nem.setlife(life);
    }
}

void GoNext(WINDOW * win, int len, pnemici& hd){
    wclear(win);
    int n = current_game.getMap(), l = current_game.getLevel();
    current_game.setMap(n+1);
    if(n == l) { 
        current_game.setLevel(l+1);
        mapgenerator(win); 
        MobSpawn(len, hd);
    } else 
        regenOldMap(win, false);
    
    /*
    char mapname[20];
    sprintf(mapname, "map/%d.txt", n+1);
    ifstream f(mapname);
    */
}

void GoPrev(WINDOW * win, pnemici hd) {
    saveMobs(hd);
    wclear(win);
    current_game.setMap(current_game.getMap()-1);
    regenOldMap(win, false);
}

void ChangeMap(Player* pl, WINDOW * win, int end, int yMax, pnemici& hd){
    if(pl->getX() >= end-2 && (hd == NULL || current_game.getMap()<current_game.getLevel())){        // solo se la lista di nemici è vuota 
    pl->Teleport(4, yMax-3); 
    GoNext(win, end, hd);
  }
  else if(pl->getX() <= 1 && current_game.getMap()>0) {
    pl->Teleport(end-4, yMax-3);
    GoPrev(win, hd);
  } 
}