#include "enemies.hpp"

Nemico::Nemico (WINDOW * win, int y, int x, int l, char c) {
    this->curwin = win;
    this->x = x;
    this->y = y;
    this->x_velocity = 0;
    this->y_velocity = 0;
    this->life = l;
    this->character = c;
    getmaxyx(curwin, yMax, xMax);
}

void Nemico::stop() {
    this->x_velocity = 0;
    this->y_velocity = 0;
}

int Nemico::getX() {
    return this->x;
}

int Nemico::getY() {
    return this->y;
}

char Nemico::getChar() {
    return this->character;
}

int Nemico::random(int max) {
    return rand() % max;
}

void Nemico::display() {
    mvwaddch(curwin, y, x, character);
    current_game.setPlayerPos(x, y);
}