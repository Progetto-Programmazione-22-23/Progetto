#include "interface.hpp"

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


    char values[80];
    sprintf(values, "Forza %.1f | Magia %.1f | Resis. %.1f | Veloc. %.1f", 
    current_game.getAtk(), current_game.getMagic(), current_game.getRes(), current_game.getSpeed());
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