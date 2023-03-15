#include <ncurses.h>
#include <string>
#include <ctime>
#include <cstdlib>
#include "player.cpp"
using namespace std;

void start(){
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    // WINDOW * playwin = newwin(20, 60, yMax/2-10, 10);
    //     box (playwin, 0, 0);
    mvwprintw(stdscr, 1, 1, "        Move: a/d    Jump: w    Jump sx: q    Jump dx: e    Esc: ctrl+C");
    //     refresh();
    //     wrefresh(playwin);
    //     keypad(playwin, true);

        Player * p = new Player(stdscr, yMax-2, 1, '>');
    
        do {                                     // do while perchè deve stampare il personaggio prima del controllo
            p->display();
            wrefresh(stdscr);
        } while (p->getmv() != 'x');

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

    string scelte[4] = {"start", "options", "info", "credits"};
    int choice;
    int highlights = 0;

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

    if (highlights == 0){
        clear();
        start();
    }
    // printw("hai scelto: %s", scelte[highlights].c_str());

    getch();
    endwin();
    /*END*/

    return 0;
}