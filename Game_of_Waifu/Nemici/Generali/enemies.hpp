#include <ncurses.h>
#include <stdlib.h>
#include "save.cpp"

#define GRAVITY 0.4
#define JUMP_VELOCITY -3
#define HORIZONTAL_ACCELERATION 2
#define HORIZONTAL_MAX_VELOCITY 2

class Nemico{
    protected:
        int life;
        int y, x, yMax, xMax;
        float x_velocity, y_velocity;
        char character;
        bool terra;
        WINDOW * curwin;
    public:
        Nemico(WINDOW * win = NULL, int y = 0, int x = 0, int l = 0, char c = ' ');
        void stop();
        int getX();
        int getY();
        char getChar();
        int random(int max);
        void update();
        void display();
};