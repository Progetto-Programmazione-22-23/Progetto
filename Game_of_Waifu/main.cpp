#include <ncurses.h>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include "save.cpp"
#include "player.cpp"
#include "TonyEffe.cpp"
using namespace std;

void mobspawner(WINDOW *win, int yM, int xM){
    Tony tony = Tony(win, yM-2, xM-2, 0, 0);
}

void interface(int yMax, int xMax){

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
    for(missing=actual;missing<current_game.getMaxVita();missing++) {
        if(missing%2==0) strcat(cuori_vuoti,"<");
        else strcat(cuori_vuoti,"3");
    }
    attron(COLOR_PAIR(3));
    mvwprintw(stdscr, (yMax/20)-1 , 9+actual,cuori_vuoti);
        attroff(COLOR_PAIR(3));

    char money[8] = "Money: ";
    char dollars[10];
    sprintf(dollars, "%d", current_game.getMoney());
    strcat(money,dollars);
    strcat(money,"$");
    attron(COLOR_PAIR(2));
    mvwprintw(stdscr, (yMax/20)-1 , 30, money);
    attroff(COLOR_PAIR(2));

    Inventory* playerInv = current_game.getInventory();
    int spacing = 20;
    for(int i=0;i<3;i++) {
        char hotbar_item[29];
        sprintf(hotbar_item, "[%d] ", i+1);
        char item_name[25];
        playerInv->getBarItem(0,i).getName(item_name);
        strcat(hotbar_item, item_name);
        if(i+1==playerInv->getSelected()) attron(COLOR_PAIR(4));
        mvwprintw(stdscr, yMax-2, spacing, hotbar_item);
        if(i+1==playerInv->getSelected()) attroff(COLOR_PAIR(4));
        spacing += strlen(hotbar_item) + 3;
    }
}

void start(){
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW * playwin = newwin(yMax-(yMax/10), xMax-(xMax/10), yMax/20, xMax/20);
    // box(playwin, 0, 0);
    keypad(playwin, true);
    nodelay(playwin, TRUE);
    int pyMax, pxMax;
    getmaxyx(playwin, pyMax, pxMax);

    //Player player = Player(playwin, g.player_pos[1], g.player_pos[0], '@');

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
    init_color(8,128,128,128);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, 8, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);


    // Loop di gioco
    bool loop = true;
    while (loop){
        erase();

        // controlla l'armatura WIP
        // current_game.setMaxVita(14);

        interface(yMax, xMax);

        mobspawner(playerwin, pryMax, prxMax);
        
        //erase();
        box(playwin, 0, 0);
        refresh();
        wrefresh(playwin);
        wrefresh(playerwin);

        player.getmv(loop);

        player.update();

        player.display();

        napms(35);
    } 
}



int main(int argc, char ** argv){

    /*START*/
    initscr();
    noecho();
    cbreak();

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

/*Come creare il menu: */
    WINDOW * menuwin = newwin(6, xMax-12, yMax/2+4, 5);
    wborder(menuwin, 0, 0, (int)'=', (int)'=', (int)'<', (int)'>', (int)'<', (int)'>');
    refresh();
    wrefresh(menuwin);
    keypad(menuwin, true);         // to get key input (up, down, left, right);
    nodelay(stdscr, TRUE);

    string scelte[4] = {"start", "continue", "options", "info"};
    int choice;
    int highlights = 0;

    loadItems();
    while (1){
        for (int i = 0; i < 4; i++){                              // costruisco il menu
            if (i == highlights) wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, i+1, 2, "%s", scelte[i].c_str());
            wattroff(menuwin, A_REVERSE);
        }
        choice = wgetch(menuwin);

        switch(choice){                // mi muovo nel menu
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
        
        if (choice == 10){            // quando premo invio
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


