#include <ncurses.h>
#include <string>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <cstring>
#include "player.cpp"
using namespace std;

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

    if(current_game.isNew())
        current_game.setPlayerPos(2,pryMax-2);

    Player player = Player(playerwin, current_game.getPlayerY(), current_game.getPlayerX(), '@');
    start_color();
    init_color(8,128,128,128);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, 8, COLOR_BLACK);


    // Loop di gioco
    bool loop = true;
    while (loop){

        // erase();

        // controlla l'armatura WIP
        current_game.setMaxVita(14);

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

        refresh();
        wrefresh(playwin);
        box(playwin, 0, 0);
        wrefresh(playerwin);

        player.getmv(loop);

        player.update();

        player.display();

        // refresh();

        napms(35);

        // std::this_thread::sleep_for(std::chrono::milliseconds(40));       
        // !!! modificando il numero di milliseconds aumento o diminuisco gli fps. se li aumento il gioco va più fluido, ma i tempi di risposta
        // del player ai tasti è molto più lento (50 è un buon valore per la fluidità, ma non buono per gli input). Al contrario 40 è un ottimo 
        // valore per gli input, ma il gioco sfarfalla. Come risolvere? Non ne ho idea. 45 non è perfetto nè come sfarfallio nè come input... ma
        // diciamo che se fanno entrambi mezzo schifo è come se fossero entrambi mezzo ok ;_;
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


