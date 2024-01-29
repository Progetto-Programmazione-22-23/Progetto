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

int calcYmin(int x) {
  pcoords t = actual_map;
  while(t != NULL) {
    if(x<t->x || (x==t->x && t->y<t->next->y)) 
      return t->y;
    t=t->next;
  }
  return 0;
}

void GoStraight(WINDOW * win, int h, int l){
    mvwaddch(win, h, l, '_') ;
}

void GoUp(WINDOW * win, int h, int l){
    mvwaddch(win, h, l, '/'), addCoord(l,h);
}

void GoDown(WINDOW * win, int h, int l){
    mvwaddch(win, h, l, '\\'), addCoord(l,h-1);
}

/// SPECIAL BLOCK SECTION ///

// qui vanno create tutte le trappole ed i blocchi di aiuto (cure, spawn armi ecc...) che vengono poi selezionati dalle funzioni sotto in modo random

// void Bomb(){
//     current_game.setVita(current_game.getVita()-1);
// }

// void Robberry(){
//     current_game.setMoney(current_game.getMoney()-1);
// }

// void SpawnTrap(){
//     int i = rand() % 2;
//     if (i == 0){
//         Bomb();
//     }else if (i == 1){
//         Robberry();
//     }
// }

void Heal(int amount){
    if(current_game.getVita()>=10+current_game.getMaxVita())
        Money(1), Ammos(2);
    else {
        int incr = current_game.getVita()+amount*(current_game.getLuck()+1);
        if(incr > 10+current_game.getMaxVita())
            incr = 10+current_game.getMaxVita();

        current_game.setVita(incr);
    }
}

void Money(int amount){
    current_game.setMoney(current_game.getMoney()+amount*(current_game.getLuck()+1));
}

void Ammos(int amount) {
        int incr = current_game.getAmmo()+amount*(current_game.getLuck()+1);
        current_game.setAmmo(incr);   
}

void SpawnHelp(){
    int tot = 3;
    //if(current_game)
    int i = rand() % tot;
    if (i == 0) Money(2);
    else if (i == 1) Heal(1);
    else if(i == 2) Ammos(3);
}

void SpecialBlock(WINDOW * win, int h, int l){
    init_pair(100, COLOR_BLACK, COLOR_YELLOW);
    wattron(win, COLOR_PAIR(100));
    mvwaddch(win, h, l, '$');
    wattroff(win, COLOR_PAIR(100));
    addSpecial(l,h);
}

void UseLuckyBlock(){
    
    int i = rand() % 2;     // 50% tra blocco buono o cattivo
    if (i == 0){
        SpawnHelp();
    }else{
        SpawnHelp();
    }
}
/// END SPECIAL BLOCK SECTION ///

/*
void SpawnBullet(WINDOW * win, int h, int l){
    mvwaddch(win, h, l, 'O');
    // salvare i proiettili in memoria :P
}
*/

void SpawnPlatform(WINDOW * win, int high, int len){
    int NumSpecialBlock = 0;
    int i, L = 15, h = 0;                                               // i:Possibilità di Spawn, L:No spawn prima di x = 15, h:H dal cielo
    int LastX = -100, LastYspawn = 0;                                   // X di fine e inizio dell'ultima piattaforma, Y di inizio dell'ultima piattaforma
    int counter = 0;
    bool buildable = true;
    while(L < len-15){
        i = rand() % 3;                                                 // Spawn 33% delle volte
        int spawnSpecial = rand()%2;
        int lenPlat = (rand() % 6) + 10;                                // Len Platform random
        if (i == 1){
            int Xspawn = L;

            /*Calcolo a quale altezza spawnare*/
            if (Xspawn-LastX < 8 && counter < 3){
                counter++; 
                h = LastYspawn-4;
            }else if (Xspawn-LastX < 8 && counter >= 3){
                counter--;
                h = LastYspawn+4;
            }else{
                h = calcYmin(Xspawn)-4;
                counter = 1;
            }

            /*Controllo non ci siano collisioni con la mappa*/
            for (int k = 0; k<lenPlat; k++){
                if (calcYmin(k+L)-h < 3) buildable = false;
                k++;
            }

            /*Costruisco*/
            if (buildable){
                addPlatform(L,h,lenPlat);

                mvwaddch(win, h, L, '<');
                LastYspawn = h;         
                L++;
                lenPlat--;
                for (int j = 0; j<lenPlat-1; j++){
                    if (spawnSpecial == 1 && j == lenPlat/2 && NumSpecialBlock < 3){SpecialBlock(win, h-1, L); NumSpecialBlock++;}
                    mvwaddch(win, h, L, '='); 
                    L++;
                }
                mvwaddch(win, h, L, '>');
                LastX = L;
                L++;
                lenPlat = 0;
            } else {L++; buildable = true;}
        }
        L+=3;
    }
}

void mapgenerator(WINDOW * win){
    clearMaps();
    actual_map = NULL;
    specials = NULL;
    platforms = NULL;

    int NumBullet = 0;

    srand(time(NULL));
    getmaxyx(win, high, len);
    int i, last = 100;
    int H = high-3;            // altezza attuale del livello: +1 se vado up, -1 se vado down;
    int L = Lstart;             // x attuale nella generazione;

    SpawnStart(win, H);         // inizio mappa
    
    while(L < len-15){
        i = rand() % 50;
        if ((i>0 && i<6)&&(last>6 && last<12)||(last>0 && last<6)&&(i>6 && i<12)){
            GoStraight(win, H, L), L++;  // se prima sono andato su, non posso andare giu (e viceversa)
        }
        if (i>0 && i<=6 && H > high/2){
            GoUp(win, H, L), L++, H--;
        }
        //else if (i == 6 && NumBullet < 4){ SpawnBullet(win, H, L), L++, NumBullet++;}   // trappole o strumenti;
        else if (i>6 && i<12 && H < high-3){
            H++, GoDown(win, H, L), L++;
        }else{
            GoStraight(win, H, L), L++;     // molto più frequente del resto (7 volte su 10);
        }
        last = i;
    }

    SpawnEnd(win, H, L);           // fine mappa
    SpawnPlatform(win, high, len);
    saveActualMap();
}