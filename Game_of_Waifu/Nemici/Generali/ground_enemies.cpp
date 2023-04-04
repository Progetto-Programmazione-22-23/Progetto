#include "ground_enemies.hpp"

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
