
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include "map_save.cpp"
//#include "enemies.hpp"
//#include "save.cpp"

int high, len;
int minH = 3;   // altezza minima per non sbattere sulla cornice;

int Lend = 10;     // lunghezze piattaforme inizio e fine;

void SpawnStart(WINDOW * win, int h);                 // base di inizio di ogni livello;
void SpawnEnd(WINDOW * win, int h, int l);            // base di fine di ogni livello, porta al successivo;
int calcYmin(int x);

void SpecialBlock(WINDOW * win, int h, int l);        // pezzo di strada dritta con blocco speciale;
void SpawnHelp();
void Heal(int amount);
void Money(int amount);
void Ammos(int amount);

void GoUp(WINDOW * win, int h, int l);
void GoStraight(WINDOW * win, int h, int l);
void GoDown(WINDOW * win, int h, int l);
void SpawnPlatform(WINDOW * win, int high, int len);
void mapgenerator(WINDOW * win);