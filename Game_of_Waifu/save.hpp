#include "oggetti.cpp"

struct igame {
    bool nuovo;
    int xplayer, yplayer, money, vita, maxvita, damage, armor;

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
        void setMoney(int x);
        int getMoney();
        void setVita(int x);
        int getVita();
        void setMaxVita(int x);
        int getMaxVita();
};