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

void deleteOldMaps() {
   std::filesystem::remove_all("map");
   std::filesystem::create_directories("map");
}

void saveActualMap() {
    std::ofstream out;
    char filename[20];
    sprintf(filename, "map/%d.txt", current_game.getMap());
    out.open(filename);
    for(pcoords t = actual_map; t != NULL; t = t->next) out<<t->x<<" "<<t->y<<"\n";
    out.close();
}

void regenOldMap(WINDOW * win, bool refresh) {
    if(!refresh) {
        actual_map = NULL;
        std::ifstream in;
        char filename[20];
        sprintf(filename, "map/%d.txt", current_game.getMap());
        in.open(filename);
        
        int x,y;
        while(in>>x>>y) addCoord(x,y);
    }   
    
    pcoords t = actual_map;
    int nexty = t->next->y;
    int w=0;
    while(t->next != NULL) {
    
        if(w<t->x) mvwaddch(win, t->y, w, '_');
        else if(w == t->x) {
            if(nexty < t->y) mvwaddch(win,t->y, w, '/');
            else if(nexty > t->y) mvwaddch(win,t->y+1, w, '\\');
            //else mvwaddch(win,t->y, w, 'S');
            
            t = t->next;
            if(t->next!=NULL) nexty = t->next->y;
            
        }
        w++;
    }
    while(w<t->x) {
        mvwaddch(win, t->y, w, '_');
        w++;
    }
}