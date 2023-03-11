// #include <ncurses.h>
// using namespace std;

// int main (int argc, char **argv){

//     initscr();             // inizializza lo schermo

//     int x, y;
//     x = y = 10;
//     move(y, x);

//     printw("Hello World!");

//     // refresh();             // refresha lo schermo per matcharlo alla memoria

//     clear();                  // clear screen

//     int w = getch();               // reagisce agli input da tastiera
//     move (0, 0);
//     printw ("%d", w);

//     mvprintw (1, 1, "%d", w);      // move + print;
//     getch();

//     endwin();              // termina ncurses

//     return 0;
// }