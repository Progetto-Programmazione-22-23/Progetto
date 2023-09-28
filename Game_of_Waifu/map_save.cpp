#include "map_save.hpp"

pcoords actual_map = NULL;

void addCoord(int x,int y) {
    pcoords c = new coords;
    c->x = x, c->y = y, c->next = NULL;
    if(actual_map == NULL) actual_map = c;
    else {
        pcoords t = actual_map;
        while(t->next!=NULL) t = t->next;
        t->next = c;
    }
}

void saveActualMap() {
    std::ofstream out;
    char filename[20];
    sprintf(filename, "map/%d.txt", current_game.getMap());
    out.open(filename);
    for(pcoords t = actual_map; t != NULL; t = t->next) out<<t->x<<" "<<t->y<<"\n";
    out.close();
}

void regenOldMap(WINDOW * win) {
    actual_map = NULL;
    std::ifstream in;
    char filename[20];
    sprintf(filename, "map/%d.txt", current_game.getMap());
    in.open(filename);
    
    int x,y;
    while(in>>x>>y) addCoord(x,y);

    int w = 0, prevy = 0;
    for(pcoords t = actual_map; t != NULL; t = t->next) {
        if(w<t->x) mvwaddch(win, t->y, w, '_');
        else if(w == t->x) {
            //if(prevy > t->y) mvwaddch(win, w, t->y, '/');  ! DA FINIRE !
            //else if(t->prev->y )
        }
        w++;
    }
}