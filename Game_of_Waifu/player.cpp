#include <ncurses.h>


class Player {
protected:
    int yLoc, xLoc, yMax, xMax;
    char character;
    WINDOW * curwin;

public:
    Player (WINDOW * win, int y, int x, char  c);

    // void mvup();
    // void mvdown();
    void mvleft();
    void mvright();
    void jumpdx();
    void jumpsx();
    int getmv();
    void display();
    //void gravity();

};

Player::Player(WINDOW * win, int y, int x, char c) {
    curwin = win;
    yLoc = y;
    xLoc = x;
    getmaxyx(curwin, yMax, xMax);
    keypad(curwin, true);
    character = c;
}

// void Player::mvup(){
//     mvwaddch(curwin, yLoc, xLoc, ' ');
//     yLoc--;
//     if (yLoc < 1) yLoc = 1;
// }

// void Player::mvdown(){
//     mvwaddch(curwin, yLoc, xLoc, ' ');
//     yLoc++;
//     if (yLoc > yMax-2) yLoc = yMax-2;
// }

void Player::mvleft(){
    mvwaddch(curwin, yLoc, xLoc, ' ');
    this->character = '<';
    xLoc--;
    if(xLoc < 1) xLoc = 1;
}

void Player::mvright(){
    mvwaddch(curwin, yLoc, xLoc, ' ');
    this->character = '>';
    xLoc++;
    if (xLoc > xMax-2) xLoc = xMax-2;
}

void Player::jumpsx() {
    this->character = '^';
    // Salta in alto
    for(int i = 0; i < 4; i++){
        mvwaddch(curwin, yLoc, xLoc, ' ');
        yLoc--;
        xLoc--;
        if (yLoc < 1) yLoc = 1;
        if (xLoc < 1) xLoc = 1;
        display();
        wrefresh(curwin);
        napms(50);              // millisecondi di stop
    }
    // Verso sinistra
    this->character = '<';
    for(int i = 0; i < 4; i++){
        mvwaddch(curwin, yLoc, xLoc, ' ');
        xLoc--;
        if (xLoc < 1) xLoc = 1;
        display();
        wrefresh(curwin);
        napms(50);
    }
    // Scende al suolo
    this->character = 'v';
    for(int i = 0; i < 4; i++){
        mvwaddch(curwin, yLoc, xLoc, ' ');
        yLoc++;
        xLoc--;
        if (xLoc < 1) xLoc = 1;
        display();
        wrefresh(curwin);
        napms(50);
    }
    this->character = '<';
}

void Player::jumpdx() {
    this->character = '^';
    // Salta in alto
    for(int i = 0; i < 4; i++){
        mvwaddch(curwin, yLoc, xLoc, ' ');
        yLoc--;
        xLoc++;
        if (yLoc < 1) yLoc = 1;
        if (xLoc > xMax-2) xLoc = xMax-2;
        display();
        wrefresh(curwin);
        napms(50);
    }
    // Verso destra
    this->character = '>';
    for(int i = 0; i < 4; i++){
        mvwaddch(curwin, yLoc, xLoc, ' ');
        xLoc++;
        if (xLoc > xMax-2) xLoc = xMax-2;
        display();
        wrefresh(curwin);
        napms(50);
    }
    // Scende al suolo
    this->character = 'v';
    for(int i = 0; i < 4; i++){
        mvwaddch(curwin, yLoc, xLoc, ' ');
        yLoc++;
        xLoc++;
        if (xLoc > xMax-2) xLoc = xMax-2;
        display();
        wrefresh(curwin);
        napms(50);
    }
    this->character = '>';
}

int Player::getmv(){
    int choice = wgetch(curwin);
    switch (choice){
        // case 'w':
        //     mvup();
        //     break;
        // case 's':
        //     mvdown();
        //     break;
        case 'a':
            mvleft();
            break;
        case 'd':
            mvright();
            break;
        case 'q':
            jumpsx();
            break;
        case 'e':
            jumpdx();
            break;
        default:
            break;
    }
    return choice;
}

// void Player::gravity(){
//     while(1){
//         if (yLoc == '_'){
//             yLoc--;
//         }
//     }
// }

void Player::display(){
    mvwaddch(curwin, yLoc, xLoc, character);
}

