#include <ncurses.h>
#include <stdlib.h>
#include "save.cpp"

class Nemico{
    protected:
        int life;
        int y, x, yMax, xMax;
        float x_velocity, y_velocity;
        char character;
        WINDOW * curwin;
    public:
        Nemico(WINDOW * win = NULL, int y = 0, int x = 0, int l = 0, char c = ' ');
        void stop();
        int getX();
        int getY();
        char getChar();
        int random(int max);
        void display();
};