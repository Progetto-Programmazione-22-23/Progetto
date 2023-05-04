#include <ncurses.h>
int main() {
    // inizializza ncurses
    initscr();

    // disabilita l'eco degli input dell'utente
    noecho();

    // nasconde il cursore
    curs_set(0);

    // disegna la mappa
    mvaddstr(0, 0, "+--------------------------------+");
    for (int i = 1; i < 9; i++) {
        mvaddstr(i, 0, "|                                |");
    }
    mvaddstr(9, 0, " |                                                                      *****               ");
    mvaddstr(10, 0, "|                                                                     ********             ");
    mvaddstr(11, 0, "|                                              ____                    *****               ");
    mvaddstr(12, 0, "|                  _______                   _/    \_                                      ");
    mvaddstr(13, 0, "|                //       \\               _/        \_              _______               ");
    mvaddstr(14, 0, "|               //         \\            _/            \            |_?_|_$_|              ");
    mvaddstr(15, 0, "|              //           \\__________/               \                           __     ");
    mvaddstr(16, 0, "|             //                                         \                        x|       ");
    mvaddstr(17, 0, "|____________//___________________________________________\_______________________x|_______");
    mvaddch ("");
    // aggiorna lo schermo
    refresh();

    // aspetta un input dall'utente
    getch();

    // ripristina lo stato precedente di ncurses e termina il programma
    endwin();
    return 0;
}