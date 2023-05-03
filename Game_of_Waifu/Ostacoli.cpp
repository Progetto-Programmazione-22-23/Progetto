#include <ncurses.h>
#include <iostream>

bool isObstacle(char** map, int x, int y) {
    char c = map[y][x];
    return (c == '|' || c == '/' || c == '\\');
}

int main() {
    
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // finestra per la mappa
    WINDOW* mapWin = newwin(20, 40, 1, 2);

    // crea la mappa
    char** map = new char*[20];
    for (int i = 0; i < 20; i++) {
        map[i] = new char[40];
    }

    // inizializza la mappa
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 40; j++) {
            if (i == 0 || i == 19) {
                map[i][j] = '-';
            }
            else if (j == 0 || j == 39) {
                map[i][j] = '|';
            }
            else {
                map[i][j] = ' ';
            }
        }
    }

    // disegna la mappa
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 40; j++) {
            mvwaddch(mapWin, i, j, map[i][j]);
        }
    }

    // creazione del personaggio
    int x = 2;
    int y = 2;

    mvwprintw(mapWin, y, x, "O");

    wrefresh(mapWin);

    
    int ch;
    bool quit = false;
    while (!quit) {
        ch = getch();
        switch (ch) {
            case KEY_LEFT:
                if (x > 1 && !isObstacle(map, x - 1, y)) {
                    mvwprintw(mapWin, y, x, " ");
                    x--;
                    mvwprintw(mapWin, y, x, "O");
                }
                break;
            case KEY_RIGHT:
                if (x < 38 && !isObstacle(map, x + 1, y)) {
                    mvwprintw(mapWin, y, x, " ");
                    x++;
                    mvwprintw(mapWin, y, x, "O");
                }
                break;
            case KEY_UP:
                if (y > 1 && !isObstacle(map, x, y - 1)) {
                    mvwprintw(mapWin, y, x, " ");
                    y--;
                    mvwprintw(mapWin, y, x, "O");
                }
                break;
            case KEY_DOWN:
                if (y < 18 && !isObstacle(map, x, y + 1)) {
                    mvwprintw(mapWin, y, x, " ");
                    y++;
                    mvwprintw(mapWin, y, x, "O");
                }
                break;
            case 'q':
                quit = true;
                break;
        }

        wrefresh(mapWin);
    }

    delwin(mapWin);
    endwin();
    refresh();

    for (int i = 0; i < 20; i++) {
    delete[] map[i];
}
delete[] map;

endwin();

return 0;
}