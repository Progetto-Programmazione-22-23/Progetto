#include <ncurses.h>
#include "inventory.cpp"

#define GRAVITY 0.4
#define JUMP_VELOCITY -3
#define HORIZONTAL_ACCELERATION 1
#define HORIZONTAL_MAX_VELOCITY 1

class Player {
    protected:
        int y, x, yMax, xMax;
        int bulletX, bulletY;
        int bulletDistance = 0;
        const int maxBulletDistance = 10;
        float x_velocity, y_velocity;
        bool is_jumping;
        bool bulletFired = false;
        char character;
        WINDOW * curwin;
        // WINDOW * invnt;
    public:
        Player(WINDOW * win = NULL, int y = 0, int x = 0, char c = ' ');
        void move_left();
        void move_right();
        void stop();
        void jump();
        void attack();
        int getX();
        int getY();
        char getChar();
        void takedmg(int d);
        void getmv(bool &loop);
        void update(int, WINDOW *);
        void shoot();
        void display();
        void moveBullet();
};