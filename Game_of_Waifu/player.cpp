#include "player.hpp"

Player::Player(WINDOW * win, int y, int x, char c) {
  this->curwin = win;
  // this->invnt = inv;
  this->x = x;
  this->y = y;
  this->LastHit = -1000;
  this->x_velocity = 0;
  this->y_velocity = 0;
  this->is_jumping = false;
  this->character = c;
  getmaxyx(curwin, yMax, xMax);
}

int Player::getX() {return x;}
int Player::getY() {return y;}
int Player::getLastHit() {return LastHit;}
void Player::UpdateLastHit(int tick) {this->LastHit = tick;}
char Player::getChar() {return character;}
void Player::drop() {this->y+=1;}
void Player::Teleport(int nx, int ny) {this->x = nx; this->y = ny;}

bool Player::platformCheck(WINDOW * win){
  bool OnPlat = false;
  if (mvwinch(win, getY()+1, getX()) == '=') {OnPlat = true;}
  else if (mvwinch(win, getY()+1, getX()) == '<') {OnPlat = true;}
  else if (mvwinch(win, getY()+1, getX()) == '>') {OnPlat = true;}
  return OnPlat;
}
void Player::move_left() {
  this->x_velocity -= HORIZONTAL_ACCELERATION;
  if (this->x_velocity < -HORIZONTAL_MAX_VELOCITY) {
    this->x_velocity = -HORIZONTAL_MAX_VELOCITY;
  }
}

void Player::move_right() {
  this->x_velocity += HORIZONTAL_ACCELERATION;
  if (this->x_velocity > HORIZONTAL_MAX_VELOCITY) {
    this->x_velocity = HORIZONTAL_MAX_VELOCITY;
  }
}

void Player::stop() {if(!is_jumping) this->x_velocity = 0;}

void Player::jump(int tik) {
  if (this->is_jumping == false){
    this->is_jumping = true;
    ActualTik = tik;
  }
}

void Player::update(int end, WINDOW * win, int tik) {
  int minY = calcYmin(x);
  int h = 5;  // altezza del salto (altezza = h / jumpspeed)
  int jumpspeed = 1;  // velocita di salto (più è bassa, più è veloce)
  mvwaddch(curwin, y, x, ' ');
  regenOldMap(win, true);
  // erase();
  
  if (this->is_jumping && (tik-ActualTik)%jumpspeed == 0 && (tik-ActualTik) <= h) {this->y-=1;} 
  else if (this->is_jumping && (tik-ActualTik) > h+4 && this->y < minY && (tik-ActualTik)%jumpspeed == 0){
    if (!platformCheck(win)) {this->y+=1; /*is_jumping = false;*/}
    else if (platformCheck(win)) {this->is_jumping = false;}
  } else if (this->y == minY){
    this->is_jumping = false;
  }
  this->x += this->x_velocity;

  if (this->y >= minY) {
    this->y = minY;
    this->y_velocity = 0;
    this->is_jumping = false;
  }

  if (!this->is_jumping && this->y<minY && !platformCheck(win)){
    this->y+=1;
  }
  if (this->x < 1) {
    this->x = 1;
    this->x_velocity = 0;
  } else if (this->x > xMax - 2) {
    this->x = xMax - 2;
    this->x_velocity = 0;
  }
}

int ds = 1;
int direction;
void Player::getmv(WINDOW * userwin, bool &loop, int tik) {
  int ch;
  ch = getch();
  switch(ch) {
    case 'w':
      jump(tik);
      break;
    case 'd':
      move_right();
      ds = 1;
      break;
    case 'a':
      move_left();
      ds = -1;
      break;
    case ' ':
    if(ds>0 || current_game.getPlayerX()>1)
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
      open_inventory(userwin);
      break;
    case 'p':
      open_shop(userwin);
      break;
    case 27:
      current_game.saveAll();
      loop = false;
      break;
    case 10:  // press enter 
      if (!bulletFired) direction = ds;
      shoot(0);
      break;
    case 'q':
      if (!bulletFired) direction = 2;
      shoot(1);
      break;
    case ERR:
      stop();
      break;

    default:
      break;
  }
}

void Player::display() {
  mvwaddch(curwin, y, x, character);
  refresh();
  current_game.setPlayerPos(x, y);
}


 // 0: destra, 1: sinistra
void Player::attack() {
  // booleano che controlla se ho un'arma selezionata
  // true -> uso l'arma
  // false -> attacco base corpo a corpo
  int s = current_game.getInventory()->getSelected();
  int id = current_game.getInventory()->getBarItem(0,s).getId();
  int startX = current_game.getPlayerX()+7, startY = current_game.getPlayerY()+3;
  if(id!=0) {
    if(id<=10) {
      attron(COLOR_PAIR(1));
      mvaddch(startY, startX+ds, '-'), mvaddch(startY, startX+2*ds, '-');
      attroff(COLOR_PAIR(1));
      //checkHit(startX, startY);
    }
  }
}

void Player::shoot(int i){
  if(!bulletFired){
    if (i == 0 && ds == 1) {this->bulletX = getX()+1; this->bulletY = getY();}
    else if (i == 0 && ds == -1) {this->bulletX = getX()-1; this->bulletY = getY();}
    else if (i == 1) {this->bulletX = getX(); this->bulletY = getY()-1;}
    this->bulletFired = true;
    this->bulletDistance = 0;
  }
}

void Player::moveBullet(WINDOW * win){
  if (bulletFired && direction == 1 && bulletDistance < maxBulletDistance) {
    mvwaddch(win, bulletY, bulletX, ' ');   // Cancella il proiettile dalla posizione precedente
    this->bulletX++;                        // Sposta il proiettile
    mvwaddch(win, bulletY, bulletX, '>');   // Disegna il proiettile nella nuova posizione
    refresh();                              // Aggiorna la finestra
    this->bulletDistance++;
    if (mvwinch(win, bulletY, bulletX+1) == '\\' || mvwinch(win, bulletY, bulletX+1) == '/'){   // check collisione con il terreno
      this->bulletDistance = maxBulletDistance;
    }
  } else if (bulletFired && direction == -1 && bulletDistance < maxBulletDistance) {
    mvwaddch(win, bulletY, bulletX, ' ');
    this->bulletX--;
    mvwaddch(win, bulletY, bulletX, '<');
    refresh();
    this->bulletDistance++;
    if (mvwinch(win, bulletY, bulletX-1) == '\\' || mvwinch(win, bulletY, bulletX-1) == '/'){
      this->bulletDistance = maxBulletDistance;
    }
  } else if (bulletFired && direction == 2 && bulletDistance < maxBulletDistance){
    mvwaddch(win, bulletY, bulletX, ' ');
    this->bulletY--;
    mvwaddch(win, bulletY, bulletX, '^');
    refresh();
    this->bulletDistance++;
    if (mvwinch(win, bulletY-1, bulletX) == '=' || mvwinch(win, bulletY-1, bulletX) == '<' || mvwinch(win, bulletY-1, bulletX) == '>'){
      this->bulletDistance = maxBulletDistance;
    }
  } else if (bulletDistance >= maxBulletDistance) {
    // Il proiettile ha raggiunto la distanza massima, disattivalo
    mvwaddch(win, bulletY, bulletX, ' ');
    bulletFired = false;
    bulletDistance = 0;
  }
}