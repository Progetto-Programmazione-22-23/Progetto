#include <ncurses.h>
#include "save.cpp"

#define G 2

class Player {
protected:
    int yLoc, xLoc, yMax, xMax;
    char character;
    WINDOW * curwin;

public:
    
    Player(WINDOW * win, int y, int x, char c) {
        curwin = win;
        yLoc = y;
        xLoc = x;
        getmaxyx(curwin, yMax, xMax);
        keypad(curwin, true);
        character = c;
    }

    void gravity(){
        while (1){
            mvwaddch(curwin, yLoc, xLoc, ' ');
            if (yLoc+2 != yMax) yLoc++;
            else break;
            display();
            wrefresh(curwin);
            napms(75);
        }
    }

    void jump(){
        double g = G;
        for (int i = 0; i < 5; i++ ){
            mvwaddch(curwin, yLoc, xLoc, ' ');
            yLoc -= 1*g;
            g -= 0.3;
            if (yLoc < 1) yLoc = 1;
            display();
            wrefresh(curwin);
            napms(75);
        }
        gravity();
    }

    void mvleft(){
        mvwaddch(curwin, yLoc, xLoc, ' ');
        this->character = '<';
        xLoc--;
        if(xLoc < 1) xLoc = 1;
    }

    void mvright(){
        mvwaddch(curwin, yLoc, xLoc, ' ');
        this->character = '>';
        xLoc++;
        if(xLoc > xMax-2) xLoc = xMax-2;
    }

    int getmv(){
        int choice = wgetch(curwin);
        switch (choice){
            case 'a':
                mvleft();
                break;
            case 'd':
                mvright();
                break;
            case 'w':
                jump();
                break;
            default:
                break;
        }
        return choice;
    }

    void display(){
        mvwaddch(curwin, yLoc, xLoc, character);
        save_player_pos(xLoc,yLoc);
    }
};