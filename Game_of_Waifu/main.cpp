#include <ncurses.h>
#include <string>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "zplayer.cpp"
using namespace std;

void start (game g = new_game){

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW * playwin = newwin(yMax-(yMax/10), xMax-(xMax/10), yMax/20, xMax/20);
    // box(playwin, 0, 0);
    keypad(playwin, true);
    nodelay(playwin, TRUE);
    int pyMax, pxMax;
    getmaxyx(playwin, pyMax, pxMax);

    //Player player = Player(playwin, g.player_pos[1], g.player_pos[0], '@');

    WINDOW * playerwin = newwin(yMax-(yMax/10)-4, xMax-(xMax/10)-4, yMax/20+2, xMax/20+2);
    box(playerwin, 0, 0);
    keypad(playerwin, true);
    nodelay(playerwin, TRUE);
    int pryMax, prxMax;
    getmaxyx(playerwin, pryMax, prxMax);

    if(g.nuovo) {
        g.player_pos[0] = 2;
        g.player_pos[1] = pryMax-2;
    }

    Player player = Player(playerwin, g.player_pos[1], g.player_pos[0], '@');


    // Loop di gioco
    while (true){
        clear();
        mvwprintw(stdscr, (yMax/20)-1 , 1, "        Move: a/d    Jump: w    Jump sx: q    Jump dx: e    Esc: ctrl+C");
        refresh();
        wrefresh(playwin);
        box(playwin, 0, 0);
        wrefresh(playerwin);

        player.getmv();

        player.update();

        player.display();

        refresh();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));       
        // !!! modificando il numero di milliseconds aumento o diminuisco gli fps. se li aumento il gioco va più fluido, ma i tempi di risposta
        // del player ai tasti è molto più lento (50 è un buon valore per la fluidità, ma non buono per gli input). Al contrario 40 è un ottimo 
        // valore per gli input, ma il gioco sfarfalla. Come risolvere? Non ne ho idea.
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

    getch();
    endwin();
    /*END*/

    return 0;
}


