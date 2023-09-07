#include <ncurses.h>
#include <stdlib.h>
#include <fstream>
#include <time.h>
//#include "save.cpp"

int high, len;
int minH = 3;   // altezza minima per non sbattere sulla cornice;
int Lstart = 10;
int Lend = 10;     // lunghezze piattaforme inizio e fine;

void SpawnStart(WINDOW * win, int h);          // base di inizio di ogni livello;
void SpawnEnd(WINDOW * win, int h, int l);            // base di fine di ogni livello, porta al successivo;

void SpecialBlock(WINDOW * win, int h, int l);        // pezzo di strada dritta con blocco speciale;
void SpawnTrap(WINDOW * win, int h, int l);
void SpawnHelp(WINDOW * win, int h, int l);

void GoUp(WINDOW * win, int h, int l);
void GoStraight(WINDOW * win, int h, int l);
void GoDown(WINDOW * win, int h, int l);
void mapgenerator(WINDOW * win);

void mapSave();
