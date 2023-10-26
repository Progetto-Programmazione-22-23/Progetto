#include "map_save.hpp"

pcoords actual_map = NULL, specials = NULL;

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

void addSpecial(int x, int y) {
    pcoords c = new coords;
    c->x = x, c->y = y, c->next = NULL;
    if(specials == NULL) specials = c;
    else {
        pcoords t = specials;
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
    char mapname[20], specialname[20];

    sprintf(mapname, "map/%d.txt", current_game.getMap());
    out.open(mapname);
    for(pcoords t = actual_map; t != NULL; t = t->next) out<<t->x<<" "<<t->y<<"\n";
    out.close();

    sprintf(specialname, "map/%ds.txt", current_game.getMap());
    out.open(specialname);
    for(pcoords t = specials; t != NULL; t = t->next) out<<t->x<<" "<<t->y<<"\n";
    out.close();
}

void regenOldMap(WINDOW * win, bool refresh) {
    if(!refresh) {
        
        for(pcoords t = actual_map, q;t!=NULL;t = q) {
            q = t->next;
            t = NULL, delete(t);
        }
        for(pcoords t = specials, q;t!=NULL;t = q) {
            q = t->next;
            t = NULL, delete(t);
        }

        actual_map = NULL;
        std::ifstream in,ins;
        char filename[20];
        sprintf(filename, "map/%d.txt", current_game.getMap());
        in.open(filename);
        int x,y;
        while(in>>x>>y) addCoord(x,y);

        specials = NULL;
        char specialname[20];
        sprintf(specialname, "map/%ds.txt", current_game.getMap());
        ins.open(specialname);
        while(in>>x>>y) addSpecial(x,y);
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

    for(pcoords q = specials;q!=NULL;q = q->next) {
        mvwaddch(win,q->y, q->x, 'S');
    }
}