#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define MAP_WIDTH 36
#define MAP_HEIGHT 18
#define PLAYER_CHAR 'X'

int main() {
    
    initscr();
    cbreak();
    noecho();

    // crea una finestra per la mappa
    WINDOW* mapwin = newwin(MAP_HEIGHT+2, MAP_WIDTH+2, 0, 0);

    // crea una finestra per il personaggio
    WINDOW* playerwin = newwin(1, 1, 1, 1);

    // disegna la mappa
    box(mapwin, 0, 0);
    mvwprintw(mapwin, 1, 1, "+--------------------------------+");
    for (int i = 2; i < 10; i++) {
        mvwprintw(mapwin, i, 1, "|                                |");
    }
    mvwprintw(mapwin, 10, 1, "|                                                                      *****               ");
    mvwprintw(mapwin, 11, 1, "|                                                                     ********             ");
    mvwprintw(mapwin, 12, 1, "|                                              ____                    *****               ");
    mvwprintw(mapwin, 13, 1, "|                  _______                   _/    \_                                      ");
    mvwprintw(mapwin, 14, 1, "|                //       \\               _/        \_              _______               ");
    mvwprintw(mapwin, 15, 1, "|               //         \\            _/            \            |_?_|_$_|              ");
    mvwprintw(mapwin, 16, 1, "|              //           \\__________/               \                           __     ");
    mvwprintw(mapwin, 17, 1, "|             //                                         \                        x|       ");
    mvwprintw(mapwin, 18, 1, "|____________//___________________________________________\_______________________x|_______");
    
	

    // posiziona il personaggio (basso a sx)
    int player_y = MAP_HEIGHT;
    int player_x = 1;
    mvwaddch(playerwin, 0, 0, PLAYER_CHAR);

    
    wrefresh(mapwin);
    wrefresh(playerwin);

    //input dall'utente
    int ch = getch();

    
    while (ch != 'q') {
        switch (ch) {
            case KEY_UP:
                if (player_y > 1 && mvwinch(mapwin, player_y-1, player_x) == ' ') {
                    player_y--;
                }
                break;
            case KEY_DOWN:
                if (player_y < MAP_HEIGHT && mvwinch(mapwin, player_y+1, player_x) == ' ') {
                    player_y++;
                }
                break;
            case KEY_LEFT:
                if (player_x > 1 && mvwinch(mapwin, player_y, player_x-1) == ' ') {
                    player_x--;
                }
                break;
            case KEY_RIGHT:
                if (player_x < MAP_WIDTH && mvwinch(mapwin, player_y, player_x+1) == ' ') {
                    player_x++;
                }
                break;
        }

        // sposta il personaggio nella nuova posizione
        mvwin(playerwin, player_y, player_x);
        wrefresh(playerwin);

        // legge il prossimo input dall'utente
        ch = getch();
    }

    // ripristina lo stato precedente di ncurses e termina il programma
    endwin();
    return 0

