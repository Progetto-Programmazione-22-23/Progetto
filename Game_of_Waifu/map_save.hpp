#include <filesystem>

struct coords {
    int x,y;
    coords* next; 
};
typedef coords* pcoords;

struct line {
    int x,y,len;
    line* next;
};
typedef line* pline;

int Lstart = 10;

void deleteOldMaps();
void addCoord(int x,int y);
void addSpecial(int x, int y);
void removeSpecial(int i);
void saveSpecials();
void addPlatform(int x, int y);
void saveActualMap();
void regenOldMap(WINDOW * win, bool refresh);