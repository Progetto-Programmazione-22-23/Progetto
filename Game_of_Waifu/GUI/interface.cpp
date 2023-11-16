#include "interface.hpp"

void showBars(WINDOW * invWin) {
    Inventory * inv = current_game.getInventory();

    mvwprintw(invWin, 2, 33, "HOTBAR");
    for(int i=0;i<3;i++) {
            char itemname[20];
            Item item = inv->getBarItem(0,i);
            item.getName(itemname);
            if(inv->getSelected() == i) {
                wattron(invWin, A_REVERSE);
            }
            mvwprintw(invWin, i+3, 32, "[%d] %s", i+1, itemname);
            wattroff(invWin, A_REVERSE);
        }
    

        mvwprintw(invWin, 7, 33, "ARMOR");

        for(int i=0;i<3;i++) {
            char itemname[20];
            Item item = inv->getBarItem(1,i);
            item.getName(itemname);
            if(item.getId()==0) wattron(invWin, COLOR_PAIR(3));
            mvwprintw(invWin, i+8, 32, "- %s", itemname);
            wattroff(invWin, COLOR_PAIR(3));
        }
}

void showStats(WINDOW * win) {
    
    int yMax, xMax;
    getmaxyx(win, yMax, xMax);

    char cuori_pieni[15] ="";
    int actual, missing;
    for(actual=0;actual<current_game.getVita();actual++) {
        if(actual%2==0) strcat(cuori_pieni,"<");
        else strcat(cuori_pieni,"3");
    }
    wattron(win, COLOR_PAIR(1));
    mvwprintw(win, 1 , 2,cuori_pieni);
    wattroff(win, COLOR_PAIR(1));
    
    char cuori_vuoti[15] = "";
    for(missing=actual;missing<10+current_game.getMaxVita();missing++) {
        if(missing%2==0) strcat(cuori_vuoti,"<");
        else strcat(cuori_vuoti,"3");
    }
    wattron(win,COLOR_PAIR(3));
    mvwprintw(win, 1 , 2+actual,"%s    ",cuori_vuoti);
    wattroff(win,COLOR_PAIR(3));

    char lives[current_game.getLives()] = "";
    for(int i=0;i<current_game.getLives();i++) strcat(lives,"o");
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, 1 , 13+current_game.getMaxVita(),"%s        ", lives);
    wattroff(win, COLOR_PAIR(2));

    wattron(win,COLOR_PAIR(5));
    mvwprintw(win, 3 , 3, "Money: %d$  ", current_game.getMoney());
    wattroff(win,COLOR_PAIR(5));

    wattron(win,COLOR_PAIR(6));
    mvwprintw(win, 4 , 3, "Ammo: %d^  ", current_game.getAmmo());
    wattroff(win,COLOR_PAIR(6));

    showBars(win);

    char values[80];
    sprintf(values, "Forza %.1f | Resis. %.1f | Veloc. %.1f", 
    current_game.getAtk(), current_game.getRes(), current_game.getSpeed());
    mvwprintw(stdscr, (yMax/20)-1 , 45, values);
}