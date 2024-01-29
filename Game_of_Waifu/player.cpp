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
int Player::getBulletX() {return bulletX;}
int Player::getBulletY() {return bulletY;}
int Player::getSwordX() {return swordX:}
int Player::getSwordY() {return swordY:}
int Player::getLastHit() {return LastHit;}
void Player::updateLastHit(int tick) {this->LastHit = tick;}
char Player::getChar() {return character;}
void Player::drop() {this->y+=1;}
void Player::teleport(int nx, int ny) {this->x = nx; this->y = ny;}

bool Player::onPlatform(WINDOW * win){
  bool OnPlat = false;
  if (mvwinch(win, getY()+1, getX()) == '=') {OnPlat = true;}
  else if (mvwinch(win, getY()+1, getX()) == '<') {OnPlat = true;}
  else if (mvwinch(win, getY()+1, getX()) == '>') {OnPlat = true;}
  return OnPlat;
}

void Player::dropFromPlatfrorm(WINDOW * win){if(onPlatform(win)) {mvwaddch(curwin, y, x, ' ');this->y+=1;}}

bool Player::onLucky(WINDOW * win){
  bool OnLuck = false;
  pcoords lucky = specials;
  int index = 0;
  while (lucky != NULL){
    if (getX() == lucky->x && getY() == lucky->y) {
      OnLuck = true;
      removeSpecial(index);
    }
    lucky = lucky->next;
    index++;
  }
  return OnLuck;
}

void Player::move_left() {
  this->x_velocity -= HORIZONTAL_ACCELERATION;
  if (this->x_velocity < -HORIZONTAL_MAX_VELOCITY) {this->x_velocity = -HORIZONTAL_MAX_VELOCITY;}
}

void Player::move_right() {
  this->x_velocity += HORIZONTAL_ACCELERATION;
  if (this->x_velocity > HORIZONTAL_MAX_VELOCITY) {this->x_velocity = HORIZONTAL_MAX_VELOCITY;}
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
  int h = 5;                   // altezza del salto (altezza = h / jumpspeed)
  int jumpspeed = 1;           // velocita di salto (più è bassa, più è veloce)
  mvwaddch(curwin, y, x, ' ');
  regenOldMap(win, true);

  if (onLucky(win)) SpawnHelp();
  
  if (this->is_jumping && (tik-ActualTik)%jumpspeed == 0 && (tik-ActualTik) <= h) {this->y-=1;} 
  else if (this->is_jumping && (tik-ActualTik) > h+4 && this->y < minY && (tik-ActualTik)%jumpspeed == 0){
    if (!onPlatform(win)) {this->y+=1;}
    else if (onPlatform(win)) {this->is_jumping = false;}
  } else if (this->y == minY){
    this->is_jumping = false;
  }
  this->x += this->x_velocity;

  if (this->y >= minY) {
    this->y = minY;
    this->y_velocity = 0;
    this->is_jumping = false;
  }

  if (!this->is_jumping && this->y<minY && !onPlatform(win)){
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
void Player::getMv(WINDOW * playerwin, WINDOW * userwin, bool &loop, int tik) {
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
    case 's':
      dropFromPlatfrorm(playerwin);
      break;
    case 'i':
      open_inventory(userwin);
      break;
    case 'o':
      if(current_game.getMap()%5==0) //&& Player::getX()>=lastHouseX && Player::getX()<=lastHouseX+7)
        open_shop(userwin);
      break;
    case 27:
      current_game.saveAll();
      loop = false;
      break;
    case 10:  // press enter 
      if (!bulletFired) direction = ds;
      attack(playerwin, 0);
      break;
    case 'q':
      if (!bulletFired) direction = 2;
      attack(playerwin, 1);
      break;
    case ERR:
      stop();
      break;

    default:
      int digit = ch-'0';
      if(digit >= 1 && digit <= 3) {
        current_game.getInventory()->setSelected(digit-1);
        current_game.UpState();
      }
      break;
  }
}

// 0: destra, 1: sinistra
void Player::attack(WINDOW * win, bool dir) {
  int s = current_game.getInventory()->getSelected();
  Item item = current_game.getInventory()->getBarItem(0,s);
  int id = item.getId(), special = item.getAmount();

  this->swordX = getX();
  this->swordY = getY();
  this->swording = true;

  if(id!=0) {
    if(id<10) {
      wattron(win,  COLOR_PAIR(3));
      for(int i=1;i<=1+special;i++) {
        mvwaddch(win, getY(), getX()+ds*i, '-');
      } 

    
      wattroff(win, COLOR_PAIR(3));
      refresh(); 
    }
    else if (id < 20) {
      shoot(dir);
    }
  }
}

void Player::swordAtk(WINDOW * win){
  mvwaddch(win, swordY, swordX, ' ');   // Cancella il proiettile dalla posizione precedente
  if (direction == 0) {this->swordX; mvwaddch(win, swordY, swordX, '-'); this->swordX++; mvwaddch(win, swordY, swordX, '-');}
  else if (direction == 1) {this->swordX; mvwaddch(win, swordY, swordX, '-'); this->swordX--; mvwaddch(win, swordY, swordX, '-');}
  refresh();                              // Aggiorna la finestra
}

void Player::shoot(int i){
  if(!bulletFired){
    // if (i == 0 && ds == 1) {this->bulletX = getX()+1; this->bulletY = getY();}
    // else if (i == 0 && ds == -1) {this->bulletX = getX()-1; this->bulletY = getY();}
    // else if (i == 1) {this->bulletX = getX(); this->bulletY = getY()-1;}
    this->bulletX = getX();
    this->bulletY = getY();
    this->bulletFired = true;
    this->bulletDistance = 0;
  }
}

void Player::shooting(WINDOW * win, int direction){
  mvwaddch(win, bulletY, bulletX, ' ');   // Cancella il proiettile dalla posizione precedente
  if (direction == 0) {this->bulletX++; mvwaddch(win, bulletY, bulletX, '>');}
  else if (direction == 1) {this->bulletX--; mvwaddch(win, bulletY, bulletX, '<');}
  else if (direction == 2) {this->bulletY--; mvwaddch(win, bulletY, bulletX, '^');}
  this->bulletDistance++;
  refresh();                              // Aggiorna la finestra
}

void Player::stopBullet() {this->bulletDistance = maxBulletDistance;}

void Player::moveBullet(WINDOW * win){
  double m = (1+current_game.getInventory()->getBarItem(0,current_game.getInventory()->getSelected()).getAmount())/2.0; // 2 -> lungo, 1 -> normale
  //3 -> 4/2, 2 -> 3/2, 1-> 2/2
  maxBulletDistance = m * ogBulletDistance;

  if (bulletFired && direction == 1 && bulletDistance < maxBulletDistance) {
    if (mvwinch(win, bulletY, bulletX) == '\\' || mvwinch(win, bulletY, bulletX+1) == '/') stopBullet();
    shooting (win, 0);
  } else if (bulletFired && direction == -1 && bulletDistance < maxBulletDistance) {
    if (mvwinch(win, bulletY, bulletX) == '\\' || mvwinch(win, bulletY, bulletX-1) == '/') stopBullet();
    shooting (win, 1);
  } else if (bulletFired && direction == 2 && bulletDistance < maxBulletDistance){
    if (mvwinch(win, bulletY-1, bulletX) == '=' || mvwinch(win, bulletY-1, bulletX) == '<' || mvwinch(win, bulletY-1, bulletX) == '>') stopBullet();
    shooting (win, 2);
  } else if (bulletDistance >= maxBulletDistance) {           // Il proiettile ha raggiunto la distanza massima, disattivalo
    mvwaddch(win, bulletY, bulletX, ' ');
    bulletFired = false;
    bulletDistance = 0;
    this->bulletX = -1;
    this->bulletY = -1;
  }
}

void Player::display() {
  mvwaddch(curwin, y, x, character);
  refresh();
  current_game.setPlayerPos(x, y);
}