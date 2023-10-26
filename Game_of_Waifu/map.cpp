#include "map.hpp"

void SpawnStart(WINDOW * win, int h){
    int l = 0;
    while (l < Lstart){
        mvwaddch(win, h, l, '_');        // piattaforma di spawn;
        l++;
    }
}

void SpawnEnd(WINDOW * win, int h, int l){
    while (l < len){
        mvwaddch(win, h, l, '_');        // piattaforma di fine;
        l++;
    }
    addCoord(len,h);
}



void GoStraight(WINDOW * win, int h, int l){mvwaddch(win, h, l, '_') ;}
void GoUp(WINDOW * win, int h, int l){mvwaddch(win, h, l, '/'), addCoord(l,h);}               
void GoDown(WINDOW * win, int h, int l){mvwaddch(win, h, l, '\\'), addCoord(l,h-1);}

// void MobSpawn(int len){
//     int i = 0;
//     while (i<5){
//         int Xspawn = rand()%len;
//         int MobType = rand()%3;
//         if (MobType == 0) InsZombie(hd, calcYmin(Xspawn), Xspawn);
//         else if (MobType == 1) InsZombie(hd, calcYmin(Xspawn), Xspawn);
//         else if (MobType == 1) InsZombie(hd, calcYmin(Xspawn) - 5, Xspawn);
//     }
// }

/// SPECIAL BLOCK SECTION ///

// qui vanno create tutte le trappole ed i blocchi di aiuto (cure, spawn armi ecc...) che vengono poi selezionati dalle funzioni sotto in modo random

void Bomb(){/*salute -1*/}
void Robberry(){/*money -x*/}
void SpawnTrap(){
    int i = rand() % 2;
    if (i == 0) Bomb();
    else if (i == 1) Robberry();
}

void Heal(){/*salute +1*/}
void Money(){/*salute +x*/}
void SpawnHelp(){
    int i = rand() % 2;
    if (i == 0) Heal();
    else if (i == 1) Money();
}

void SpecialBlock(WINDOW * win, int h, int l){
    mvwaddch(win, h, l, 'S');
    //addCoord(l,h);

    // se le coordinate del player sono le stesse del blocco speciale, si attiva un effetto random

    int i = rand() % 2;     // 50%
    if (i == 0) SpawnTrap();
    else SpawnHelp();
}

/// END SPECIAL BLOCK SECTION ///

void mapgenerator(WINDOW * win){
    actual_map = NULL;
    srand(time(NULL));
    getmaxyx(win, high, len);
    int i, last = 100;
    int H = high -3;            // altezza attuale del livello: +1 se vado up, -1 se vado down;
    int L = Lstart;             // x attuale nella generazione;

    SpawnStart(win, H);         // inizio mappa
    
    while(L < len-10){
        i = rand() % 50;
        if ((i>0 && i<6)&&(last>6 && last<12)||(last>0 && last<6)&&(i>6 && i<12)) GoStraight(win, H, L), L++;  // se prima sono andato su, non posso andare giu (e viceversa)
        if (i>0 && i<6 && H > high-30) GoUp(win, H, L), L++, H--;
        else if (i == 6) SpecialBlock(win, H, L), L++;      // trappole o strumenti;
        else if (i>6 && i<12 && H < high-3)  H++, GoDown(win, H, L), L++;
        else GoStraight(win, H, L), L++;                      // molto più frequente del resto (7 volte su 10);
        last = i;
    }

    SpawnEnd(win, H, L);           // fine mappa
    // MobSpawn(len);
    saveActualMap();
}

