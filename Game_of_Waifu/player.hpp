#include <ncurses.h>
#include "GUI/inventory.cpp"
#include "GUI/shop.cpp"
#include "map.cpp"

#define GRAVITY 0.6
#define JUMP_VELOCITY -3
#define HORIZONTAL_ACCELERATION 1
#define HORIZONTAL_MAX_VELOCITY 1

int ActualTik = 0;

struct swordXY {
    int sX;
    int sY;
    int len;
    int ds;
};

class Player {
    protected:
        int y, x, yMax, xMax;
        int LastHit;
        int bulletX, bulletY;
        int swordX, swordY, swordL;
        int bulletDistance = 0;
        const int ogBulletDistance = 10;
        int maxBulletDistance = 10;
        float x_velocity, y_velocity;
        bool is_jumping;
        bool bulletFired = false;
        bool swording = false;
        char character;
        WINDOW * curwin;
    public:
        Player(WINDOW * win = NULL, int y = 0, int x = 0, char c = ' ');
        void move_left();
        void move_right();
        void stop();
        void jump(int tik);
        void teleport(int nx, int ny);
        void drop();
        void dropFromPlatfrorm(WINDOW * win);
        bool isSwording();
        swordXY swordInfo();
        int getX();
        int getY();
        int getBulletX();
        int getBulletY();
        int getLastHit();
        char getChar();
        void updateLastHit(int tick);
        void getMv(WINDOW * pwin, WINDOW * uwin, bool &loop, int tik);
        bool onPlatform(WINDOW * win);
        bool onLucky(WINDOW * win);
        void attack(WINDOW * win);
        void swordAtk(WINDOW * win);
        void shoot();
        void shooting(WINDOW * win, int direction);
        void stopBullet();
        void moveBullet(WINDOW * win);
        void update(int end, WINDOW * win, int tik);
        void display();
};



