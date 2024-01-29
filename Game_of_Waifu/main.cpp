#include <ncurses.h>
#include <ctime>
#include <cstring>
#include <string>
#include <cstdlib>
#include "save.cpp"
// #include "gui.cpp"
// #include "collision.cpp"
// #include "enemies.cpp"
// #include "inventory.cpp"
// #include "map_save.cpp"
#include "map_setting.cpp"
#include "GUI/interface.cpp"
#include "game_text.cpp"
// #include "map.cpp"
// #include "oggetti.cpp"
// #include "player.cpp"
// #include "shop.cpp"
using namespace std;

void resetLife(WINDOW * win, pnemici& hd, Player& p, bool& loop) {
    wclear(win);
    dead = false;
    int l = current_game.getLives();
    if(l==1) {
        loop = false; //game over
    } else {
        int ymax, xmax;
        getmaxyx(win, ymax, xmax);

        current_game.setVita(10+current_game.getMaxVita());
        
        current_game.setLives(l-1);
        current_game.setMap(0);
        current_game.setLevel(0);
        deleteOldMaps();
        mapgenerator(win);

        for(pnemici t = hd, q;t!=NULL;t = q) {  // Elimina la lista di nemici attuali
            q = t->next;
            t = NULL, delete(t);
        }
        hd = NULL;
        MobSpawn(xmax, hd);

        p.teleport(2,ymax-3);
    }
}

void start(){
    pnemici hd = new nemico;
    hd = NULL;
    pbullets bullHd = new bullet;
    bullHd = NULL;
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    /*FINESTRA CON PG*/
    WINDOW * playerwin = newwin(yMax-(yMax/10)-20, xMax-(xMax/10)-2, yMax/20+20, xMax/20+1);
    box(playerwin, 0, 0);
    keypad(playerwin, true);
    nodelay(playerwin, TRUE);
    int pryMax, prxMax;
    getmaxyx(playerwin, pryMax, prxMax);

    /*FINESTRA USER*/
    WINDOW * userwin = newwin(yMax-pryMax-5, xMax-(xMax/10)-40, yMax/20, xMax/20+1);
    box(userwin, 0, 0);
    nodelay(userwin, TRUE);

    if(current_game.eNuovo()) {                        // disegna la mappa
        current_game.setPlayerPos(2,pryMax-3);
        deleteOldMaps();
        mapgenerator(playerwin);
        MobSpawn(prxMax, hd);
    }
    else {
        regenOldMap(playerwin, false);
        mobRespawn(hd);
    }
    Player player = Player(playerwin, current_game.getPlayerY(), current_game.getPlayerX(), '@');
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, 245, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
    init_pair(104, COLOR_BLACK, COLOR_YELLOW);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    // Loop di gioco
    int cont = 0;     /*numero di loop di gioco (Tick)*/
    bool loop = true; 
    int state = -1;   
    while (loop){
        cont++;
        // controlla l'armatura WIP
        // current_game.setMaxVita(14);
        if(state!=current_game.getState()) {
            current_game.updateStats();
            state = current_game.getState();
        }
        //interface(yMax, xMax);
        showStats(userwin);

        /*CONTROLLO DEI MOB*/
        update(hd, &player, cont, playerwin, bullHd);           // movimenti
        hd = Death(hd);                                         // elimino mob morti
        display(hd, playerwin);                                 // disegno i mob in vita
        if(dead) resetLife(playerwin, hd, player, loop);

        /*Proiettile Player*/
        player.moveBullet(playerwin);
        player.attack(palyerwin);

        /*Proiettili Nemici*/
        bullHd = moveShoot(bullHd, playerwin);
        bullHd = removeShoot(bullHd);

        box(playerwin, 0, 0);     // aggiorna le finestre
        box(userwin, 0, 0);
        wrefresh(playerwin);
        wrefresh(userwin);

        player.getMv(playerwin, userwin, loop, cont); // prende user input 
        if(!loop) saveMobs(hd);

        player.update(prxMax, playerwin, cont);
        ChangeMap(&player, playerwin, prxMax, pryMax, hd); 

        player.display();           // disegna il player

        // current_game.setLives(0);

        if (current_game.getLives() <= 0) gameOver();

        napms(35);                  // 35ms di pausa (circa 30fps)
    } 
}

int main(int argc, char ** argv){

/*START*/
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    gameTitle(xMax, yMax);

/*Come creare il menu: */
    WINDOW * menuwin = newwin(5, xMax-12, yMax/2+4, 5);
    wborder(menuwin, 0, 0, (int)'=', (int)'=', (int)'<', (int)'>', (int)'<', (int)'>');
    refresh();
    wrefresh(menuwin);
    keypad(menuwin, true); // to get key input (up, down, left, right);
    nodelay(stdscr, TRUE);

    int menuyMax, menuxMax;
    getmaxyx(menuwin, menuyMax, menuxMax);

    string scelte[3] = {"start", "continue", "info"};
    int choice;
    int highlights = 0;

    loadItems();
    bool open = true;
    while (open){
        for (int i = 0; i < 3; i++){ // costruisco il menu
            if (i == highlights) wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i+1, menuxMax/2-10, "%s", scelte[i].c_str());
            wattroff(menuwin, A_REVERSE);
        }
        choice = wgetch(menuwin);

        switch(choice){            // mi muovo nel menu
            case KEY_UP:
                highlights--;
                if (highlights == -1) highlights = 0;
                break;
            case KEY_DOWN:
                highlights++;
                if (highlights == 3) highlights = 2;
                break;
            case 10: 
                open = false;
                break;
            default:
                break;
        }
    }

    if (highlights <= 1){
        clear();
        if(highlights == 1) current_game.continueLast();
        start();
    }

    getch();
    endwin();
    /*END*/

    return 0;
}