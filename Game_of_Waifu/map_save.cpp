#include "map_save.hpp"

pcoords actual_map = NULL, specials = NULL; 
pline platforms = NULL;

void addCoord(int x,int y) {
    pcoords c = new coords;
    c->x = x, c->y = y, c->next = NULL;
    if(actual_map == NULL){
        actual_map = c;
    } else {
        pcoords t = actual_map;
        while(t->next!=NULL){
            t = t->next;
        }
        t->next = c;
    }
}

void addSpecial(int x, int y) {
    pcoords c = new coords;
    c->x = x, c->y = y, c->next = NULL;
    if(specials == NULL){
        specials = c;
    } else {
        pcoords t = specials;
        while(t->next!=NULL){
            t = t->next;
        }
        t->next = c;
    }
}

void saveSpecials() {
    std::ofstream out;
    char specialname[20];
    sprintf(specialname, "map/%ds.txt", current_game.getMap());
    out.open(specialname);
    for(pcoords t = specials; t != NULL; t = t->next){
        out<<t->x<<" "<<t->y<<"\n";
    }
    out.close();   
}

void removeSpecial(int i) {
    pcoords q;
    if(i==0) {
        q = specials;
        specials = specials->next;
    }
    else {
        pcoords t = specials;
        for(int i=0;i<i-1 && t->next!=NULL;i++) t = t->next;
        
        if(t->next!=NULL) {
            q = t->next;
            t->next = t->next->next;
        }
    }
    q = NULL, delete(q);

    saveSpecials();
}

void addPlatform(int x, int y, int len) {
    pline c = new line;
    c->x = x, c->y = y, c->len = len, c->next = NULL;
    if (platforms == NULL){
        platforms = c;
    } else {
        pline t = platforms;
        while(t->next!=NULL){
            t = t->next;
        }
        t->next = c;
    }
}

void deleteOldMaps() {
   std::filesystem::remove_all("map");
   std::filesystem::create_directories("map");
}



void saveActualMap() {
    std::ofstream out;
    char mapname[20], platname[20];

    sprintf(mapname, "map/%d.txt", current_game.getMap());
    out.open(mapname);
    for(pcoords t = actual_map; t != NULL; t = t->next){
        out<<t->x<<" "<<t->y<<"\n";
    }
    out.close();

    sprintf(platname, "map/%dp.txt", current_game.getMap());
    out.open(platname);
    for(pline t = platforms; t != NULL; t = t->next){
        out<<t->x<<" "<<t->y<<" "<<t->len<<"\n";
    }
    out.close();

    saveSpecials();
}

int lastHouseX = 0;
void spawnHouse(WINDOW * win, int y, int w) {
        lastHouseX = w+4;
        
        mvwprintw(win, y, w, "____");
        mvwprintw(win, y, w+5, "_");
        mvwprintw(win, y, w+11, "___");
        mvwprintw(win, y, w+9, "_");
        wattron(win,COLOR_PAIR(3));
        mvwprintw(win, y, w+4, "|");
        mvwprintw(win, y, w+10, "|");
        mvwprintw(win, y-1, w, "    /=====\\");
        mvwprintw(win, y-2, w, "     |===|");
        mvwprintw(win, y-3, w, "      /*\\");
        mvwprintw(win, y-4, w, "       _");
        wattroff(win,COLOR_PAIR(3));
        wattron(win,COLOR_PAIR(5));
        mvwprintw(win, y, w+6, "[O]");
        wattroff(win,COLOR_PAIR(5));
        /*
        while(w < t->x) {
            if (w == (t->x - 11)){
                mvwaddch(win, t->y, w, '|');
                mvwaddch(win, t->y- 1, w, '/');
            }else if (w == (t->x - 10) || w == (t->x - 6)){
                mvwaddch(win, t->y, w, '_');
                mvwaddch(win, t->y-1, w, '=');
                mvwaddch(win, t->y-2, w, '|');
            }else if (w == (t->x - 9)){
                mvwaddch(win, t->y, w, '_');
                mvwaddch(win, t->y-1, w, '=');
                mvwaddch(win, t->y-2, w, '=');
                mvwaddch(win, t->y-3, w, '/');
            }else if (w == (t->x - 8)){
                mvwaddch(win, t->y, w, 'O');
                mvwaddch(win, t->y-1, w, '=');
                mvwaddch(win, t->y-2, w, '=');
                mvwaddch(win, t->y-3, w, '*');
                mvwaddch(win, t->y-4, w, '_');
            }else if (w == (t->x - 7)){
                mvwaddch(win, t->y, w, '_');
                mvwaddch(win, t->y-1, w, '=');
                mvwaddch(win, t->y-2, w, '=');
                mvwaddch(win, t->y-3, w, '\\');
            }else if (w == (t->x - 5)){
                mvwaddch(win, t->y, w, '|');
                mvwaddch(win, t->y- 1, w, '\\');
            }
            w++;
        }
        */
}   

void regenOldMap(WINDOW * win, bool refresh) {
    if(!refresh) {
        
        for(pcoords t = actual_map, q;t!=NULL;t = q) {  // Elimina la lista di coordinate actual_map
            q = t->next;
            t = NULL, delete(t);
        }
        for(pcoords t = specials, q;t!=NULL;t = q) {    // Elimina la lista di coordinate speciale
            q = t->next;
            t = NULL, delete(t);
        }
        for(pline t = platforms, q;t!=NULL;t = q) {     // Elimina la lista di coordinate platforms
            q = t->next;
            t = NULL, delete(t);
        }

        std::ifstream in, ins, inp;

        actual_map = NULL;
        char filename[20];
        sprintf(filename, "map/%d.txt", current_game.getMap());
        in.open(filename);
        int x,y;
        while(in>>x>>y){
            addCoord(x,y);
        }

        specials = NULL;
        char specialname[20];
        sprintf(specialname, "map/%ds.txt", current_game.getMap());
        ins.open(specialname);
        while(ins>>x>>y){
            addSpecial(x,y);
        }

        platforms = NULL;
        int len;
        char platname[20];
        
        sprintf(platname, "map/%dp.txt", current_game.getMap());
        inp.open(platname);

        while(inp>>x>>y>>len){
            addPlatform(x,y,len);
        }
    }   
    
    pcoords t = actual_map;
    int nexty = t->next->y;
    int w=0;

    while(t->next != NULL) {    
        if(w<t->x) mvwaddch(win, t->y, w, '_');
        else if(w == t->x) {
            if(nexty < t->y){
                mvwaddch(win,t->y, w, '/');
            }else if(nexty > t->y){
                mvwaddch(win,t->y+1, w, '\\');
            }
            t = t->next;
            if(t->next!=NULL){
                nexty = t->next->y;
            }
        }
        w++;
    }

    /*
         _
        /*\
       |===|
      /=====\
    __|_[O]_|____
    
    */
    
    if(current_game.getMap()%5 == 0) {
        spawnHouse(win, t->y, w); 
        w+=13;
    }

    while(w<t->x) {
        mvwaddch(win, t->y, w, '_');
        w++;
    }

        
    
    

    for(pcoords q = specials;q!=NULL;q = q->next) {
        if(refresh){
            wattron(win, COLOR_PAIR(104));
        }
        mvwaddch(win, q->y, q->x, '$');
        if(refresh){
            wattroff(win, COLOR_PAIR(104));
        }
    }
    
    for(pline q = platforms; q != NULL; q = q->next) {
        mvwaddch(win,q->y, q->x, '<');
        for(int i=1;i<q->len-1;i++){
            mvwaddch(win,q->y, q->x+i, '=');
        }
        mvwaddch(win,q->y, q->x+q->len-1, '>');
    }

    
}