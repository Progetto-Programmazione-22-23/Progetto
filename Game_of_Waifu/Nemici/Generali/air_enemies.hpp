#include "enemies.cpp"

class NemicoAria : public Nemico {
    protected: 
        bool terra;
    public:
        NemicoAria(WINDOW * win = NULL, int y = 0, int x = 0, int l = 0, char c = ' ');
        void fly();
};