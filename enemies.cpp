#include "enemies.hpp"

Nemico::Nemico (WINDOW * win, int y, int x) {
    this->curwin = win;
    this->x = x;
    this->y = y;
    this->x_velocity = 0;
    this->y_velocity = 0;
    getmaxyx(curwin, yMax, xMax);
}