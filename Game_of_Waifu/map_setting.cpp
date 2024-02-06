#include "map_setting.hpp"

void MobSpawn(int len, pnemici& hd){
    srand(time(NULL));
    int i = 0;
    int lv = current_game.getBestLvl();
    if (lv > 4) lv = 4;
    while (i<lv+2){
        int Xspawn = 15 + rand()%(len-15);
        int MobType = rand()%NumMob;
        if (MobType == 0) hd = InsZombie(hd, calcYmin(Xspawn), Xspawn, lv);
        else if (MobType == 1) hd = InsGolem(hd, calcYmin(Xspawn), Xspawn, lv);
        else if (MobType == 2) hd = InsCerbottaniere(hd, calcYmin(Xspawn), Xspawn, lv);
        else if (MobType == 3) hd = InsBat(hd, calcYmin(Xspawn) - 5, Xspawn, lv);
        else if (MobType == 4) hd = InsDemon(hd, calcYmin(Xspawn) - 5, Xspawn, lv);
        else hd = InsZombie(hd, calcYmin(Xspawn), Xspawn, lv); 
        i++;
    }
}

/* SALVA LE STATS DEI MOB DELL'ULTIMA MAPPA, 1 PER RIGA */
void saveMobs(pnemici hd){
    std::ofstream out;
    out.open("enemies.txt");
    for(pnemici e = hd; e != NULL; e = e->next) {
        Mob m = e->nem;
        out<<m.getType()<<" "<<m.getlife()<<" "<<m.getX()<<" "<<m.getY()<<"\n";
    }
    out.close();
}

/* (PROCEDIMENTO INVERSO) RICOSTRUISCE POS. E TIPO DI MOB IN BASE ALLE RIGHE DI "enemies.txt" */
void mobRespawn(pnemici& hd) {
    int lvl = current_game.getLevel();
    std::ifstream in;
    in.open("enemies.txt");
    int type, life, x, y;
    while(in>>type>>life>>x>>y) {
        switch(type) {
        case 0:
            hd = InsZombie(hd, y, x, lvl);
            break;
        case 1:
            hd = InsGolem(hd, y, x, lvl);
            break;
        case 2:
            hd = InsCerbottaniere(hd, y, x, lvl);
            break;
        case 10:
            hd = InsBat(hd, y, x, lvl);
            break;
        case 11:
            hd = InsDemon(hd, y, x, lvl);
            break;
        default:
            break;
        }

        hd->nem.setlife(life);
    }
}

/* GESTIONE IL CAMBIAMENTO DI MAPPA AVANTI/DIETRO */
void GoNext(WINDOW * win, int len, pnemici& hd){    // (AVANTI)
    wclear(win);
    int n = current_game.getMap(), l = current_game.getLevel();
    current_game.setMap(n+1);

    if(n == l) {                                                // MAPPA NUOVA -> AUMENTO LIVELLO, NUOVI MOB
        current_game.setLevel(l+1);
        current_game.setBestLvl(current_game.getBestLvl()+1);
        mapgenerator(win); 
        MobSpawn(len, hd);
    } else                                                      // MAPPA GIÀ VISTA -> LA RIPRISTINA        
        regenOldMap(win, false);

}

void GoPrev(WINDOW * win, pnemici hd) {             // (INDIETRO) SALVA I MOB, RIPRISTINA MAPPA PRECEDENTE
    saveMobs(hd);
    wclear(win);
    current_game.setMap(current_game.getMap()-1);
    regenOldMap(win, false);
}

void ChangeMap(Player* pl, WINDOW * win, int end, int yMax, pnemici& hd){
    if(pl->getX() >= end-2 && (hd == NULL || current_game.getMap()<current_game.getLevel())){        // solo se la lista di nemici è vuota 
    pl->teleport(4, yMax-3); 
    GoNext(win, end, hd);
  }
  else if(pl->getX() <= 1 && current_game.getMap()>0) {
    pl->teleport(end-4, yMax-3);
    GoPrev(win, hd);
  } 
}