#include "enemies.cpp"

int NumMob = 4;

void MobSpawn(int len, pnemici& hd);
void saveMobs(pnemici hd);

void GoNext(WINDOW * win, int len, pnemici& hd);                                 // quando arrivi alla piattaforma di fine, nuovo livello
void GoPrev(WINDOW * win);

void ChangeMap(Player* pl, WINDOW * win, int end, int yMax, pnemici& hd);