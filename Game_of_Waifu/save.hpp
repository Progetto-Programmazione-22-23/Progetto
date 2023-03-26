struct igame {
    bool nuovo;
    int xplayer, yplayer, money;
    double vita;
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
        void setVita(double x);
        double getVita();
};