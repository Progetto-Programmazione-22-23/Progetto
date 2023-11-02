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

void Player::stop() {if (!is_jumping) this->x_velocity = 0;}

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

  if (this->is_jumping && (tik-ActualTik)%jumpspeed == 0 && (tik-ActualTik) <= h) {
    // double k = 1;
    // //if(current_game.getInventory()->) k = 1.5;
    this->y-=1;
  } else if (this->is_jumping && (tik-ActualTik) > h+4 && this->y < minY && (tik-ActualTik)%jumpspeed == 0){
    this->y+=1;
  } else if (this->y == minY){
    this->is_jumping = false;
  }
  this->x += this->x_velocity;

  if (this->y >= minY) {
    this->y = minY;
    this->y_velocity = 0;
    this->is_jumping = false;
  }
  if (!this->is_jumping && this->y<minY){
    this->y = minY;
  }
  if (this->x < 1) {
    this->x = 1;
    this->x_velocity = 0;
  } else if (this->x > xMax - 2) {
    this->x = xMax - 2;
    this->x_velocity = 0;
  }
}

int Player::getX() {return x;}
int Player::getY() {return y;}
int Player::getLastHit() {return LastHit;}
void Player::UpdateLastHit(int tick) {this->LastHit = tick;}
char Player::getChar() {return character;}
void Player::Teleport(int nx, int ny) {this->x = nx; this->y = ny;}

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
      shoot();
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

void Player::shoot(){
  if(!bulletFired){
    direction = ds;
    this->bulletX = getX()+1;
    this->bulletY = getY();
    this->bulletFired = true;
    this->bulletDistance = 0;
  }
}

void Player::moveBullet(WINDOW * win){
  if (bulletFired && direction == 1 && bulletDistance < maxBulletDistance) {
    mvwaddch(win, bulletY, bulletX, ' ');   // Cancella il proiettile dalla posizione precedente
    this->bulletX++;                        // Sposta il proiettile verso destra
    mvwaddch(win, bulletY, bulletX, '>');   // Disegna il proiettile nella nuova posizione
    refresh();                              // Aggiorna la finestra
    this->bulletDistance++;
  } else if (bulletFired && direction == -1 && bulletDistance < maxBulletDistance) {
    mvwaddch(win, bulletY, bulletX, ' ');   // Cancella il proiettile dalla posizione precedente
    this->bulletX--;                        // Sposta il proiettile verso destra
    mvwaddch(win, bulletY, bulletX, '<');   // Disegna il proiettile nella nuova posizione
    refresh();                              // Aggiorna la finestra
    this->bulletDistance++;
  }else if (bulletDistance >= maxBulletDistance) {
    // Il proiettile ha raggiunto la distanza massima, disattivalo
    mvwaddch(win, bulletY, bulletX, ' ');
    bulletFired = false;
    bulletDistance = 0;
  }
}
/*

// Funzione per controllare la collisione orizzontale con il terreno
bool checkHorizontalCollision(Player player, int groundY, int groundStartX, int groundEndX) {
    // Verifica se il giocatore si sovrappone orizzontalmente al terreno
    return (player.x >= groundStartX && player.x <= groundEndX && player.y == groundY);
}

// Funzione per controllare la collisione verticale con il terreno
bool checkVerticalCollision(int groundY, int groundStartX, int groundEndX) {
    // Verifica se il giocatore si sovrappone verticalmente al terreno
    getX();
    getY();
    return (player.x >= groundStartX && this->x <= groundEndX && this->y >= groundY);
}

void Player::checkCollisions() {
  // Controlla le collisioni orizzontali e verticali
  // con il terreno o altri oggetti se necessario

  // Supponiamo che 'groundY', 'groundStartX' e 'groundEndX'
  // rappresentino le coordinate del terreno
  bool horizontalCollision = checkHorizontalCollision(playerObject, groundY, groundStartX, groundEndX);
  bool verticalCollision = checkVerticalCollision(playerObject, groundY, groundStartX, groundEndX);

  if (horizontalCollision) {
    // Gestisci la collisione orizzontale
    // Ad esempio, ferma il movimento orizzontale del giocatore
  }

  if (verticalCollision) {
    // Gestisci la collisione verticale
    // Ad esempio, ferma il salto del giocatore se sta toccando il terreno
  }
}

*/