#include "inventory.hpp"
#include <cstring>
#include <string>
#include <cstdlib>


void setupINV(){
    
}

void updateINV(){

}

void drawINV(){

}

void open_inventory(){
    int syMax, sxMax;
    getmaxyx(stdscr, syMax, sxMax);

    WINDOW *invWin = newwin(syMax-(syMax/10)-2, sxMax-(sxMax/10)-2, syMax/20+2, sxMax/20+1);
    box(invWin, 0, 0);
    keypad(invWin, true);
    nodelay(invWin, TRUE);
    int inyMax, inxMax;
    getmaxyx(invWin, inyMax, inxMax);

    int n = 4;
    std::string oggetti[n] = {"spada lunga", "scudo di doran", "palle potenti", "freccia"};
    int choice;
    int highlights = 0;

    bool open = true;
    while (open){
        for (int i = 0; i < n; i++){ // costruisco il menu
            if (i == highlights) wattron(invWin, A_REVERSE);
            mvwprintw(invWin, i+1, 2, "%s", oggetti[i].c_str());
            wattroff(invWin, A_REVERSE);
        }
        choice = wgetch(invWin);

        switch(choice){ // mi muovo nel menu
            case KEY_UP:
                highlights--;
                if (highlights == -1) highlights = 0;
                break;
            case KEY_DOWN:
                highlights++;
                if (highlights == 4) highlights = 3;
                break;
            case 'i':
                open = false;
                break;
            default:
                break;
        }
        
        if (choice == 10){ // quando premo invio
            break;
        }
    }
}
