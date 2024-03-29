#include "inv_logic.cpp"

struct igame {
    double xplayer, yplayer, map, money, vita, ammo, level, lives, bestlvl, stats[CATEGORIES];
    Inventory inventory;
    bool nuovo2;

};

class Game {
    igame setting;
    int state;

    public:
        Game(igame s);
        void saveAll();
        void continueLast();
        int getState();
        void UpState();
        void setPlayerPos(int x, int y);
        int getPlayerX();
        int getPlayerY();
        bool eNuovo();
        void setMoney(int x);
        int getMoney();
        void setVita(double x);
        double getVita();
        void updateStats();
        double getMaxVita();
        double getAtk();
        double getRes();
        double getLuck();
        int getMap();
        void setMap(int i);
        int getAmmo();
        void setAmmo(int i);
        int getLevel();
        void setLevel(int i);
        int getLives();
        void setLives(int i);
        int getBestLvl();
        void setBestLvl(int i);
        Inventory* getInventory();
};