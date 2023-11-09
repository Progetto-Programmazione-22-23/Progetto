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
    mvwprintw(win, 1 , 1,cuori_pieni);
    wattroff(win, COLOR_PAIR(1));
    
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
    sprintf(money, "Money: %d$  ", current_game.getMoney());
    attron(COLOR_PAIR(2));
    mvwprintw(stdscr, (yMax/20)-1 , 30, money);
    attroff(COLOR_PAIR(2));

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