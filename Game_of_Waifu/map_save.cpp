#include "map_save.hpp"

pcoords actual_map = NULL, specials = NULL; 
pline platforms = NULL;

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

void addPlatform(int x, int y, int len) {
    pline c = new line;
    c->x = x, c->y = y, c->len = len, c->next = NULL;
    if(platforms == NULL) platforms = c;
    else {
        pline t = platforms;
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
    char mapname[20], specialname[20], platname[20];

    sprintf(mapname, "map/%d.txt", current_game.getMap());
    out.open(mapname);
    for(pcoords t = actual_map; t != NULL; t = t->next) out<<t->x<<" "<<t->y<<"\n";
    out.close();

    sprintf(specialname, "map/%ds.txt", current_game.getMap());
    out.open(specialname);
    for(pcoords t = specials; t != NULL; t = t->next) out<<t->x<<" "<<t->y<<"\n";
    out.close();

    sprintf(platname, "map/%dp.txt", current_game.getMap());
    out.open(platname);
    for(pline t = platforms; t != NULL; t = t->next) out<<t->x<<" "<<t->y<<" "<<t->len<<"\n";
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
        for(pline t = platforms, q;t!=NULL;t = q) {
            q = t->next;
            t = NULL, delete(t);
        }

        std::ifstream in, ins, inp;

        actual_map = NULL;
        char filename[20];
        sprintf(filename, "map/%d.txt", current_game.getMap());
        in.open(filename);
        int x,y;
        while(in>>x>>y) addCoord(x,y);

        specials = NULL;
        char specialname[20];
        sprintf(specialname, "map/%ds.txt", current_game.getMap());
        ins.open(specialname);
        while(ins>>x>>y) addSpecial(x,y);

        platforms = NULL;
        int len;
        char platname[20];
        sprintf(platname, "map/%dp.txt", current_game.getMap());
        inp.open(platname);
        while(inp>>x>>y>>len) addPlatform(x,y,len);
    }   
    
    pcoords t = actual_map;
    int nexty = t->next->y;
    int w=0;
    while(t->next != NULL) {
        if(w<t->x) mvwaddch(win, t->y, w, '_');
        else if(w == t->x) {
            if(nexty < t->y) mvwaddch(win,t->y, w, '/');
            else if(nexty > t->y) mvwaddch(win,t->y+1, w, '\\');
            
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
        init_pair(104, COLOR_BLACK, COLOR_YELLOW);
        if(refresh) wattron(win, COLOR_PAIR(104));
        mvwaddch(win, q->y, q->x, '$');
        if(refresh) wattroff(win, COLOR_PAIR(104));
    }
    
    for(pline q = platforms;q!=NULL;q = q->next) {
        mvwaddch(win,q->y, q->x, '<');
        for(int i=1;i<q->len-1;i++) mvwaddch(win,q->y, q->x+i, '=');
        mvwaddch(win,q->y, q->x+q->len-1, '>');
    }

    
}