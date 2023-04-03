#include <ncurses.h>
#include <stdlib.h>
#include "save.cpp"

class Nemico{
    protected:
        int y, x, yMax, xMax;
        float x_velocity, y_velocity;
        WINDOW * curwin;
    public:
        Nemico(WINDOW * win = NULL, int y = 0, int x = 0);
        void spawn();
        void move();
        void stop();
        void jump();
        int getX();
        int getY();
        char getChar();
        void update();
        void display();
};