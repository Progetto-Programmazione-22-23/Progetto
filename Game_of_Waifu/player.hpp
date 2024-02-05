#include <ncurses.h>
#include "GUI/inventory.cpp"
#include "GUI/shop.cpp"
#include "map.cpp"
// #include "collision.cpp"

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
        // Object bullet;
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
        // WINDOW * invnt;
    public:
        /*struct Object {
            int yO;
            int yO;
            int dmgO;
        }*/
        Player(WINDOW * win = NULL, int y = 0, int x = 0, char c = ' ');
        void move_left();
        void move_right();
        void stop();
        void jump(int tik);
        void attack(WINDOW * win);
        void swordAtk(WINDOW * win);
        bool isSwording();
        swordXY swordInfo();
        int getX();
        int getY();
        int getBulletX();
        int getBulletY();
        int getLastHit();
        char getChar();
        void drop();
        void teleport(int nx, int ny);
        void updateLastHit(int tick);
        void getMv(WINDOW * pwin, WINDOW * uwin, bool &loop, int tik);
        bool onPlatform(WINDOW * win);
        void dropFromPlatfrorm(WINDOW * win);
        bool onLucky(WINDOW * win);
        void update(int end, WINDOW * win, int tik);
        void shoot();
        void shooting(WINDOW * win, int direction);
        void stopBullet();
        void moveBullet(WINDOW * win);
        void display();
};



