#include "player.hpp"

Player::Player(WINDOW * win, int y, int x, char c) {
    this->curwin = win;
    this->x = x;
    this->y = y;
    this->x_velocity = 0;
    this->y_velocity = 0;
    this->is_jumping = false;
    this->character = c;
    getmaxyx(curwin, yMax, xMax);
  }

  void Player::move_left() {
    //mvwaddch(curwin, y, x, ' ');
    this->x_velocity -= HORIZONTAL_ACCELERATION;
    if (this->x_velocity < -HORIZONTAL_MAX_VELOCITY) {
      this->x_velocity = -HORIZONTAL_MAX_VELOCITY;
    }
  }

  void Player::move_right() {
    //mvwaddch(curwin, y, x, ' ');
    this->x_velocity += HORIZONTAL_ACCELERATION;
    if (this->x_velocity > HORIZONTAL_MAX_VELOCITY) {
      this->x_velocity = HORIZONTAL_MAX_VELOCITY;
    }
  }

  void Player::stop(){
    if (!is_jumping) this->x_velocity = 0;
  }

  void Player::jump() {
    bool fast = true;
    if (x_velocity == 0) fast = false;
    if (!this->is_jumping) {
      this->y_velocity = JUMP_VELOCITY ;
      if (!fast) this->x_velocity = x_velocity*10;
      else this->x_velocity = x_velocity*1.5;
      this->is_jumping = true;
    }
  }

  int ds = 1; // 0: destra, 1: sinistra
  void Player::attack() {
    // booleano che controlla se ho un'arma selezionata
    // true -> uso l'arma
    // false -> attacco base corpo a corpo
    int s = current_game.getInventory()->getSelected();
    int id = current_game.getInventory()->getBarItem(0,s).getId();
    if(id!=0) {
      if(id == 1) {
        mvwaddch(curwin, current_game.getPlayerY(), current_game.getPlayerX()+ds, '-');
      }
    }
  }

  void Player::update() {
    mvwaddch(curwin, y, x, ' ');
    // erase();
    if (this->is_jumping) {
      double k = 1;
      //if(current_game.getInventory()->) k = 1.5;
      this->y_velocity += GRAVITY/k ;   // dividi per aumentare, molt. per diminuire
    }
    this->x += this->x_velocity;
    this->y += this->y_velocity;

    if (this->y >= yMax-2) {
      this->y = yMax-2;
      this->y_velocity = 0;
      this->is_jumping = false;
    }
    if (this->x < 1) {
      this->x = 1;
      this->x_velocity = 0;
    } else if (this->x > xMax - 2) {
      this->x = xMax - 2;
      this->x_velocity = 0;
    }
  }

  int Player::getX(){
    return x;
  }

  int Player::getY(){
    return y;
  }

  char Player::getChar(){
    return character;
  }

  void Player::getmv(bool &loop){
    int ch;
    ch = getch();
    switch(ch) {
      case 'd':
        move_right();
        ds = 1;
        break;
      case 'a':
        move_left();
        ds = -1;
        break;
      case 'w':
        jump();
        break;
      case ' ':
        Player::attack();
        break;
      case '1':
        current_game.getInventory()->setSelected(0);
        current_game.UpState();
        break;
      case '2':
        current_game.getInventory()->setSelected(1);
        current_game.UpState();
        break;
      case '3':
        current_game.getInventory()->setSelected(2);
        current_game.UpState();
        break;
      case 'i':
        open_inventory();
        break;
      case 27:
        current_game.saveAll();
        loop = false;
        break;
      case 'x':
        debugging();
        break;
      case ERR:
        stop();
        break;
      default:
        break;
    }
  }

void Player::open_inventory(){

  // disegna una finestra sopra lo schermo
  // deve anche mettere in pausa il gioco.
}

  void Player::display() {
    mvwaddch(curwin, y, x, character);
    current_game.setPlayerPos(x, y);
  }