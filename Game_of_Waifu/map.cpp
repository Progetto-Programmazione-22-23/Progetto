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
}

void GoStraight(WINDOW * win, int h, int l){mvwaddch(win, h, l, '_');}
void GoUp(WINDOW * win, int h, int l){mvwaddch(win, h, l, '/');}               
void GoDown(WINDOW * win, int h, int l){mvwaddch(win, h, l, '\\');}

/// SPECIAL BLOCK SECTION ///

// qui vanno create tutte le trappole ed i blocchi di aiuto (cure, spawn armi ecc...) che vengono poi selezionati dalle funzioni sotto in modo random

void SpawnTrap(WINDOW * win, int h, int l){
    mvwaddch(win, h, l, 'T');
}

void SpawnHelp(WINDOW * win, int h, int l){
    mvwaddch(win, h, l, 'H');
}

void SpecialBlock(WINDOW * win, int h, int l){
    int i = rand() % 2;     // 50%
    if (i == 0) SpawnTrap(win, h, l);
    else SpawnHelp(win, h, l);
}

/// END SPECIAL BLOCK SECTION ///

void mapgenerator(WINDOW * win){
    srand(time(NULL));
    getmaxyx(win, high, len);
    int i, last = 100;
    int H = high -3;            // altezza attuale del livello: +1 se vado up, -1 se vado down;
    int L = Lstart;          // x attuale nella generazione;

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
}

void mapSave(){                
    std::ofstream out;
    out.open("map.txt");

}

// vorrei fare un file in cui durante la generazione della mappa vengono salvate le coordinate (ad ogni x associo la relativa altezza del blocco nella mappa)   
// e il simbolo corrispondente (_, L, ⅃, blocco speciale...) in modo da poter ricreare la mappa una volta usciti dal gioco se si salva.
// una volta finito il livello, il txt viene cancellato e si ricrea una nuova mappa da zero. Il player potrebbe essere tenuto sopra la mappa 
// controllando, in base alla sua posizione nelle x, se la sua altezza è <= della rispettiva y nel file di testo

// La mappa viene generata, ora devo riuscire a mantenerla anche perchè non si capisce nulla