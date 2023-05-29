#include <ncurses.h>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include "save.cpp"
// #include "player.cpp"
#include "enemies.cpp"
// #include "enemies.cpp"
// #include "gui.cpp"
using namespace std;

void interface(int yMax, int xMax){

/*ok*/

    char cuori_pieni[15] ="";
    int actual, missing;
    for(actual=0;actual<current_game.getVita();actual++) {
        if(actual%2==0) strcat(cuori_pieni,"<");
        else strcat(cuori_pieni,"3");
    }
    attron(COLOR_PAIR(1));
    mvwprintw(stdscr, (yMax/20)-1 , 9,cuori_pieni);
    attroff(COLOR_PAIR(1));
    char cuori_vuoti[15] = "";
    for(missing=actual;missing<10+current_game.getMaxVita();missing++) {
        if(missing%2==0) strcat(cuori_vuoti,"<");
        else strcat(cuori_vuoti,"3");
    }
    attron(COLOR_PAIR(3));
    mvwprintw(stdscr, (yMax/20)-1 , 9+actual,cuori_vuoti);
    attroff(COLOR_PAIR(3));

    char removeExtra[11];
    for(int i=0;i<11-current_game.getMaxVita();i++)
        strcat(removeExtra, " ");
    mvwprintw(stdscr, (yMax/20)-1 , 19+current_game.getMaxVita(), removeExtra);

    char money[18];
    sprintf(money, "Money: %d$", current_game.getMoney());
    attron(COLOR_PAIR(2));
    mvwprintw(stdscr, (yMax/20)-1 , 30, money);
    attroff(COLOR_PAIR(2));

    char values[80];
    sprintf(values, "Forza %.1f | Magia %.1f | Resis. %.1f | Veloc. %.1f | Fortuna %.1f", 
    current_game.getAtk(), current_game.getMagic(), current_game.getRes(), current_game.getSpeed(), current_game.getLuck());
    mvwprintw(stdscr, (yMax/20)-1 , 45, values);


    Inventory* playerInv = current_game.getInventory();
    int spacing = 20;
    for(int i=0;i<3;i++) {
        char hotbar_item[29], item_name[25];
        playerInv->getBarItem(0,i).getName(item_name);
        sprintf(hotbar_item, "[%d] %s", i+1, item_name);
        if(i==playerInv->getSelected()) attron(COLOR_PAIR(4));
        mvwprintw(stdscr, yMax-2, spacing, hotbar_item);
        if(i==playerInv->getSelected()) attroff(COLOR_PAIR(4));
        spacing += strlen(hotbar_item) + 3;
    }
    
    char testin[4];
    sprintf(testin, "[%d] ", playerInv->getBarItem(0,1).getPrice());
    //mvwprintw(stdscr, yMax-2, 70, testin);
}

void start(){
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    /*TUTTO (anche vita ed inventario rapido)*/
    WINDOW * playwin = newwin(yMax-(yMax/10), xMax-(xMax/10), yMax/20, xMax/20);
    // box(playwin, 0, 0);
    keypad(playwin, true);
    nodelay(playwin, TRUE);
    int pyMax, pxMax;
    getmaxyx(playwin, pyMax, pxMax); 

    /*FINESTRA CON PG*/
    WINDOW * playerwin = newwin(yMax-(yMax/10)-2, xMax-(xMax/10)-2, yMax/20+2, xMax/20+1);
    box(playerwin, 0, 0);
    keypad(playerwin, true);
    nodelay(playerwin, TRUE);
    int pryMax, prxMax;
    getmaxyx(playerwin, pryMax, prxMax);

    if(current_game.eNuovo())
        current_game.setPlayerPos(2,pryMax-2);

    Player player = Player(playerwin, current_game.getPlayerY(), current_game.getPlayerX(), '@');
    start_color();
    //init_color(16,124,252,0);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, 245, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);



    // disegna la mappa
    // mvwprintw(playerwin, 1, 1, "+--------------------------------+");
    // for (int i = 2; i < 10; i++) {
    //     mvwprintw(playerwin, i, 1, "|                                |");
    // }
    // mvwprintw(playerwin, 10, 1, "|                                                                      *****               ");
    // mvwprintw(playerwin, 11, 1, "|                                                                     ********             ");
    // mvwprintw(playerwin, 12, 1, "|                                              ____                    *****               ");
    // mvwprintw(playerwin, 13, 1, "|                  _______                   _/    \_                                      ");
    // mvwprintw(playerwin, 14, 1, "|                //       \\               _/        \_              _______               ");
    // mvwprintw(playerwin, 15, 1, "|               //         \\            _/            \            |_?_|_$_|              ");
    // mvwprintw(playerwin, 16, 1, "|              //           \\__________/               \                           __     ");
    // mvwprintw(playerwin, 17, 1, "|             //                                         \                        x|       ");
    // mvwprintw(playerwin, 18, 1, "|____________//___________________________________________\_______________________x|_______");



    /*MOB LIST*/
    Mob Koopa (playerwin, 3, 1, pryMax-2, prxMax/2, 'K', false);
    Mob Pidgeon (playerwin, 3, 1, pryMax/2, prxMax/2+15, 'V', true);

    pnemici hd = NULL; 
    //hd = InsMob(hd, Koopa);
    hd = InsMob(hd, Pidgeon);

    // Loop di gioco
    int cont = 0;
    bool loop = true;
    int state = -1;
    while (loop){
        // erase();
        cont++;
        // controlla l'armatura WIP
        // current_game.setMaxVita(14);
        if(state!=current_game.getState()) {
            current_game.updateStats();
            state = current_game.getState();
        }
        interface(yMax, xMax);

        /*CONTROLLO DEI MOB*/
        if (cont%3 == 0) update(hd, player, pryMax-6); // ogni 3 loop muove i nemici
        display(hd); // disegna i nemici

        //erase();
        box(playwin, 0, 0); // aggiorna le finestre
        refresh();
        wrefresh(playwin);
        wrefresh(playerwin);

        player.getmv(loop); // prende user input 

// PAUSE per l'inventario: subroutine

        player.update();

        player.display(); // disegna il pg

        /*CONTROLLO DEI MOB*/
        if (cont%3 == 0) update(hd, player, pryMax-6);
        display(hd);

        napms(35);
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

/*Come creare il menu: */
    WINDOW * menuwin = newwin(6, xMax-12, yMax/2+4, 5);
    wborder(menuwin, 0, 0, (int)'=', (int)'=', (int)'<', (int)'>', (int)'<', (int)'>');
    refresh();
    wrefresh(menuwin);
    keypad(menuwin, true); // to get key input (up, down, left, right);
    nodelay(stdscr, TRUE);

    string scelte[4] = {"start", "continue", "options", "info"};
    int choice;
    int highlights = 0;

    loadItems();
    while (1){
        for (int i = 0; i < 4; i++){ // costruisco il menu
            if (i == highlights) wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i+1, 2, "%s", scelte[i].c_str());
            wattroff(menuwin, A_REVERSE);
        }
        choice = wgetch(menuwin);

        switch(choice){ // mi muovo nel menu
            case KEY_UP:
                highlights--;
                if (highlights == -1) highlights = 0;
                break;
            case KEY_DOWN:
                highlights++;
                if (highlights == 4) highlights = 3;
                break;
            default:
                break;
        }
        
        if (choice == 10){ // quando premo invio
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