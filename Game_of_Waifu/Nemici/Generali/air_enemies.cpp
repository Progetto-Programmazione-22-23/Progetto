#include "air_enemies.hpp"

NemicoAria::NemicoAria(WINDOW * win, int y, int x, int l, char c) : Nemico (win, y, x, l, c){
    this->terra = false;
}

void NemicoAria::fly() {
    int x = random(9);
    if (x == 2 || x == 4 || x == 6 || x == 8) x++;
    else if (x == 1 || x == 3 || x == 5 || x == 7) x--;
    else if (x == 0) y++;
    else if (x == 9) y--;
}