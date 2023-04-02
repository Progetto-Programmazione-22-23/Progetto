#include <ncurses.h>
#include "save.cpp"

#define GRAVITY 0.4
#define JUMP_VELOCITY -3
#define HORIZONTAL_ACCELERATION 2
#define HORIZONTAL_MAX_VELOCITY 2

class Player {
    protected:
        int y, x, yMax, xMax;
        float x_velocity, y_velocity;
        bool is_jumping;
        char character;
        WINDOW * curwin;
    public:
        Player(WINDOW * win = NULL, int y = 0, int x = 0, char c = ' ');
        void move_left();
        void move_right();
        void stop();
        void jump();
        int getX();
        int getY();
        char getChar();
        void getmv(bool &loop);
        void update();
        void display();

};