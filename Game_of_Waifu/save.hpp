#include "oggetti.cpp"

struct igame {
    int xplayer, yplayer, money, vita, maxvita, damage, res;
    Inventory inventory;
    bool nuovo2;
    //Inventory inventory;

};

class Game {
    igame setting;

    public:
        Game(igame s);
        void saveAll();
        void continueLast();
        void setPlayerPos(int x, int y);
        int getPlayerX();
        int getPlayerY();
        bool isNew();
        bool eNuovo();
        void setMoney(int x);
        int getMoney();
        void setVita(int x);
        int getVita();
        void setMaxVita(int x);
        int getMaxVita();
        Inventory getInventory();
};