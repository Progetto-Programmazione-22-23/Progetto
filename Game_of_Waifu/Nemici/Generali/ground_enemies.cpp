#include "ground_enemies.hpp"

NemicoTerra::NemicoTerra(WINDOW * win, int y, int x, int l, char c) : Nemico (win, y, x, l, c){
    this->terra = true;
}

void NemicoTerra::mv(){
    int x = random(2);
    if (x%2 == 0) {
        this->x_velocity -= HORIZONTAL_ACCELERATION;
        if (this->x_velocity < -HORIZONTAL_MAX_VELOCITY) {
            this->x_velocity = -HORIZONTAL_MAX_VELOCITY;
        }
    } else {
        this->x_velocity += HORIZONTAL_ACCELERATION;
        if (this->x_velocity > HORIZONTAL_MAX_VELOCITY) {
            this->x_velocity = HORIZONTAL_MAX_VELOCITY;
        }
    }
}
