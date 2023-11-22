#include "game_text.hpp"

void gameTitle(int xMax, int yMax){
    const char* myString;

    myString = R"(  _______    __   __     _____    ______      _____    __    __    _____ )";
    mvprintw(yMax/2-10, xMax/2-40, myString);
    myString = R"(/\_______)\ /\_\ /_/\  /\_____\  /_/\___\    /\___/\  /_/\  /\_\ /\_____\)";
    mvprintw(yMax/2-9, xMax/2-40, myString);
    myString = R"(\(___  __\/( ( (_) ) )( (_____/  ) ) ___/   / / _ \ \ ) ) \/ ( (( (_____/)";
    mvprintw(yMax/2-8, xMax/2-40, myString);
    myString = R"(  / / /     \ \___/ /  \ \__\   /_/ /  ___  \ \(_)/ //_/ \  / \_\\ \__\  )";
    mvprintw(yMax/2-7, xMax/2-40, myString);
    myString = R"( ( ( (      / / _ \ \  / /__/_  \ \ \_/\__\ / / _ \ \\ \ \\// / // /__/_ )";
    mvprintw(yMax/2-6, xMax/2-40, myString);
    myString = R"(  \ \ \    ( (_( )_) )( (_____\  )_)  \/ _/( (_( )_) ))_) )( (_(( (_____\)";
    mvprintw(yMax/2-5, xMax/2-40, myString);
    myString = R"(  /_/_/     \/_/ \_\/  \/_____/  \_\____/   \/_/ \_\/ \_\/  \/_/ \/_____/)";
    mvprintw(yMax/2-4, xMax/2-40, myString);
}

void gameOver(){
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW * overWin = newwin(yMax, xMax, 0, 0);
    wborder(overWin, 0, 0, (int)'=', (int)'=', (int)'<', (int)'>', (int)'<', (int)'>');
    wclear(stdscr);
    refresh();
    wrefresh(overWin);
    keypad(overWin, true); // to get key input (up, down, left, right);
    nodelay(stdscr, TRUE);

    int overYMax, overXMax;
    getmaxyx(overWin, overYMax, overXMax);

    while (true){
        const char* myString;

        mvwprintw(overWin, overYMax/2-10, overXMax/2-20, "%s", "( (                            ( /(                   )");
        myString = R"(                                 )                   )";
        mvprintw(overYMax/2-10, overXMax/2-40, myString, overWin);
        myString = R"( (                            ( /(                   )";
        mvprintw(overYMax/2-9, overXMax/2-40, myString, overWin);
        myString = R"( )\ )       )     )      (    )\())   )      (   (   )";
        mvprintw(overYMax/2-8, overXMax/2-40, myString, overWin);
        myString = R"((()/(    ( /(    (      ))\  ((_)\   /((    ))\  )(  )";
        mvprintw(overYMax/2-7, overXMax/2-40, myString, overWin);
        myString = R"( /(_))_  )(_))   )\  ' /((_)   ((_) (_))\  /((_)(()\ )";
        mvprintw(overYMax/2-6, overXMax/2-40, myString, overWin);
        myString = R"((_)) __|((_)_  _((_)) (_))    / _ \ _)((_)(_))   ((_))";
        mvprintw(overYMax/2-5, overXMax/2-40, myString, overWin);
        myString = R"(  | (_ |/ _` || '  \()/ -_)  | (_) |\ V / / -_) | '_|)";
        mvprintw(overYMax/2-4, overXMax/2-40, myString, overWin);
        myString = R"(   \___|\__,_||_|_|_| \___|   \___/  \_/  \___| |_|   )";
        mvprintw(overYMax/2-3, overXMax/2-40, myString, overWin);
    }
}