#include <ncurses.h>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include "map_save.cpp"
//#include "save.cpp"

int high, len;
int minH = 3;   // altezza minima per non sbattere sulla cornice;

int Lend = 10;     // lunghezze piattaforme inizio e fine;

void SpawnStart(WINDOW * win, int h);          // base di inizio di ogni livello;
void SpawnEnd(WINDOW * win, int h, int l);            // base di fine di ogni livello, porta al successivo;

void SpecialBlock(WINDOW * win, int h, int l);        // pezzo di strada dritta con blocco speciale;
void SpawnTrap();
void SpawnHelp();
void Heal();
void Money();
void Bomb();

void GoUp(WINDOW * win, int h, int l);
void GoStraight(WINDOW * win, int h, int l);
void GoDown(WINDOW * win, int h, int l);
void mapgenerator(WINDOW * win);

void mapSave(int, int, char);
