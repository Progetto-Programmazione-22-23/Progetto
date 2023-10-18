#include "player.hpp"
#include "map.cpp"


Player::Player(WINDOW * win, int y, int x, char c) {
  this->curwin = win;
  // this->invnt = inv;
  this->x = x;
  this->y = y;
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

void Player::stop(){
  if (!is_jumping) this->x_velocity = 0;
}

void Player::jump(int tik) {
  if (this->is_jumping == false){
    this->is_jumping = true;
    ActualTik = tik;
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

int calcYmin(int x) {
  pcoords t = actual_map;
  while(t != NULL) {
    if(x<=t->x) return t->y;
    t=t->next;
  }
  return 0;
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
  if(getX() >= end-2){        // solo se la lista di nemici è vuota 
    this->x = 4;
    this->y = yMax-3;
    GoNext(win);
  }
  else if(getX() <= 1 && current_game.getMap()>0) {
    this->x = end-4;
    this->y = yMax-3;
    GoPrev(win);
  } 
}

int Player::getX() {return x;}
int Player::getY() {return y;}
char Player::getChar() {return character;}

void Player::getmv(bool &loop, int tik){
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
    case ' ':
      jump(tik);
      break;
    // case ' ':
    //   Player::attack();
    //   break;
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
    case 'p':
      open_shop();
      break;
    case 27:
      current_game.saveAll();
      loop = false;
      break;
    case 'x':
      debugging();
      break;
    case 10:  // press enter 
      shoot();
      break;
    case ERR:
      stop();
      break;

    default:
      break;
  }
  // Dopo aver gestito l'input del giocatore, verifica le collisioni
//  checkCollisions();

  moveBullet();   // Sposta il proiettile
  //usleep(10000);  // Aggiorna la posizione del proiettile ogni 10 millisecondi

}

void Player::display() {
  mvwaddch(curwin, y, x, character);
  refresh();
  current_game.setPlayerPos(x, y);
}

void Player::shoot(){
  if(!bulletFired){
    this->x = getX(); // NON FUNZIONA
    this->y = getY(); // NON FUNZIONA
    bulletX = this->x + 8;
    bulletY = this->y + 3;
    bulletFired = true;
    bulletDistance = 0;
  }
}

void Player::moveBullet(){
  if (bulletFired && bulletDistance < maxBulletDistance) {
        mvaddch(bulletY, bulletX, ' ');   // Cancella il proiettile dalla posizione precedente
        bulletX++;                        // Sposta il proiettile verso destra
        mvaddch(bulletY, bulletX, '>');   // Disegna il proiettile nella nuova posizione
        refresh();                        // Aggiorna la finestra
        bulletDistance++;
    } else if (bulletDistance >= maxBulletDistance) {
        // Il proiettile ha raggiunto la distanza massima, disattivalo
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