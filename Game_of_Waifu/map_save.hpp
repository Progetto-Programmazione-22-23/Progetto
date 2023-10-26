#include <filesystem>

struct coords {
    int x,y;
    coords* next; 
};
typedef coords* pcoords;

int Lstart = 10;

void deleteOldMaps();
void addCoord(int x,int y);
void saveActualMap();
void regenOldMap(WINDOW * win, bool refresh);