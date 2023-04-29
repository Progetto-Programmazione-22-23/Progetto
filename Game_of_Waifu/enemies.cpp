#include "enemies.hpp"

Mob::Mob (WINDOW * win, int y, int x, char ch, int xv, int yv) {
    this->curwin = win;
    this->x = x;
    this->y = y;
    this->character = ch;
    this->x_velocity = xv;
    this->y_velocity = yv;
    getmaxyx(curwin, yMax, xMax);
}

void Mob::stop() {
    this->x_velocity = 0;
    this->y_velocity = 0;
}

int Mob::getX() {
    return this->x;
}

int Mob::getY() {
    return this->y;
}

char Mob::getChar() {
    return this->character;
}

int Mob::random(int max) {
    return rand() % max;
}

void Mob::update() {
    // erase();
    this->x += this->x_velocity;
    this->y += this->y_velocity;

    if (this->x < 1) {
      this->x = 1;
      this->x_velocity = 0;
    } else if (this->x > xMax - 2) {
      this->x = xMax - 2;
      this->x_velocity = 0;
    }
}

void Mob::display() {
    mvwaddch(curwin, y, x, character);
    // current_game.setPlayerPos(x, y);
}