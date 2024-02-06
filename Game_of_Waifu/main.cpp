#include <ncurses.h>
#include <ctime>
#include <cstring>
#include <string>
#include <cstdlib>
#include "save.cpp"
#include "map_setting.cpp"
#include "GUI/interface.cpp"
#include "game_text.cpp"
using namespace std;

/* GESTIONE PERDITA DI UNA VITA */
bool endGame = false;
void resetLife(WINDOW * win, pnemici& hd, Player& p, bool& loop) {
    wclear(win);
    dead = false;
    int l = current_game.getLives();

    if(l==1) {          // ERA L'ULTIMA VITA -> GAME OVER
        loop = false; 
        endGame = true;
    
    } else {            
        int ymax, xmax;
        getmaxyx(win, ymax, xmax);

        current_game.setVita(10+current_game.getMaxVita()); // REFULLA LA HEALTH-BAR
        
        current_game.setLives(l-1);
        current_game.setMap(0);
        current_game.setLevel(0);
        deleteOldMaps();            // ELIMINA LE MAPPE SALVATE PRIMA e poi NE GENERA UNA NUOVA
        mapgenerator(win);

        for(pnemici t = hd, q;t!=NULL;t = q) {  // Elimina la lista di nemici attuali e poi NE SPAWNA DI NUOVI
            q = t->next;
            t = NULL, delete(t);
        }
        hd = NULL;
        MobSpawn(xmax, hd);

        p.teleport(2,ymax-3);   // Riporta il player alle coords iniziali
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

    if(current_game.eNuovo()) {                        // È STATO CLICKATO 'start' -> NUOVO GAME
        current_game.setPlayerPos(2,pryMax-3);
        deleteOldMaps();
        mapgenerator(playerwin);
        MobSpawn(prxMax, hd);
        current_game.getInventory()->setBarItem(0,0,getItem(allItems,1)); // "Spada di Legno" aggiunta nel primo slot della Hotbar
    }
    else {                              // È STATO CLICKATO 'continue' -> RIPRISTINA VECCHIA MAPPA E MOBS
        regenOldMap(playerwin, false);
        mobRespawn(hd);
    }

    Player player = Player(playerwin, current_game.getPlayerY(), current_game.getPlayerX(), '@');

    /* COLORI USATI NEL GIOCO */
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
        cont++;     // aumento tick di gioco

        /* GESTIONE DELLO STATO DELL'INVENTARIO: SE IL GIOCO NON È AL PASSO -> AGGIORNA LE STATS */
        if(state!=current_game.getState()) {
            current_game.updateStats();
            state = current_game.getState();

            wclear(userwin);
            wrefresh(userwin);
        }
        
        showStats(userwin);

        /*CONTROLLO DEI MOB*/
        update(hd, &player, cont, playerwin, bullHd);           // movimenti
        hd = Death(hd);                                         // elimino mob morti
        display(hd, playerwin);                                 // disegno i mob in vita

        /*Proiettile Player*/
        player.moveBullet(playerwin);

        /*Proiettili Nemici*/
        bullHd = moveShoot(bullHd, playerwin, player);
        bullHd = removeShoot(bullHd);

        /* CONTROLLO MORTE DEL PLAYER */
        if(dead) resetLife(playerwin, hd, player, loop);
        
        if(player.isSwording()) player.swordAtk(playerwin); // CANCELLA LA SPADA DA SCHERMO SE È STATA USATA
        player.getMv(playerwin, userwin, loop, cont); // prende user input 

        box(playerwin, 0, 0);     // aggiorna le finestre
        box(userwin, 0, 0);
        wrefresh(playerwin);
        wrefresh(userwin);

        if(!loop) saveMobs(hd); // SE STIAMO USCENDO DAL GAME -> SALVA I MOB SU FILE

        player.update(prxMax, playerwin, cont);
        ChangeMap(&player, playerwin, prxMax, pryMax, hd); 

        player.display();           // disegna il player

        napms(35);                  // 35ms di pausa (circa 30fps)
    } 
    if(endGame) gameOver(); // GAMEOVER SE HAI PERSO TUTTE LE VITE
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

        /* "continue" -> SETTA "current_game" CON IL SALVATAGGIO PRECEDENTE  */
        if(highlights == 1) current_game.continueLast(); 
        
        start();
    }

    getch();
    endwin();
    /*END*/

    return 0;
}