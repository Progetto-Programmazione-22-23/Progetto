#include <ncurses.h>
#include <string>
#include <ctime>
#include <cstdlib>
#include "zplayer.cpp"
using namespace std;

void start(game g=new_game){
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW * playwin = newwin(yMax-(yMax/10), xMax-(xMax/10), yMax/20, xMax/20);
    box (playwin, 0, 0);
    // mvwprintw(playwin, 2, 2, "        Move: a/d    Jump: w    Jump sx: q    Jump dx: e    Esc: ctrl+C");
    refresh();
    wrefresh(playwin);
    keypad(playwin, true);

    int pyMax, pxMax;
    getmaxyx(playwin, pyMax, pxMax);

    if(g.nuovo) {
        g.player_pos[0] = 2;
        g.player_pos[1] = pyMax-2;
    }

    Player * p = new Player(playwin, g.player_pos[1], g.player_pos[0], '>');
    mvwprintw(stdscr, (yMax/20)-1 , 1, "        Move: a/d    Jump: w    Jump sx: q    Jump dx: e    Esc: ctrl+C");
    refresh();
    wrefresh(playwin);
    
    do {                                     // do while perchè deve stampare il personaggio prima del controllo
        p->display();
        wrefresh(playwin);
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

    string scelte[4] = {"start", "continue", "options", "info"};
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
    else if(highlights == 1){
        clear();
        start(get_last_game());
    }
    // printw("hai scelto: %s", scelte[highlights].c_str());

    getch();
    endwin();
    /*END*/

    return 0;
}