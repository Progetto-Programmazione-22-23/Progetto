#include "enemies.cpp"

class NemicoTerra : public Nemico {
    protected:
        bool terra;
    public:
        NemicoTerra(WINDOW * win = NULL, int y = 0, int x = 0, int l = 0, char c = ' ');
        void mv();
};