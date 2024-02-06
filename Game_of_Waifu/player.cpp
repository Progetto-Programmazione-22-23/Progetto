#include "player.hpp"

Player::Player(WINDOW * win, int y, int x, char c) {
  this->curwin = win;
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

// ds 1: DESTRA | -1: SINISTRA
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
      if(current_game.getMap()%3==0 && Player::getX()>=lastHouseX && Player::getX()<=lastHouseX+7)
        open_shop(userwin);   // SHOP DISPONIBILE OGNI 3 LIVELLI, SOLO A FINE MAPPA
      break;
    case 27:
      current_game.saveAll(); // CON [ESC] ESCE DAL GAME LOOP, SALVANDO I PROGRESSI
      loop = false;
      break;
    case 10:  // press enter 
      if (!bulletFired) direction = ds; // SPARO ORIZZONTALE
      attack(playerwin);
      break;
    case 'q':
      if (!bulletFired) direction = 2; // SPARO VERSO L'ALTO
      attack(playerwin);
      break;
    case KEY_UP:
      break;
    case KEY_DOWN:
      break;
    case KEY_LEFT:
      break;
    case KEY_RIGHT:
      break;
    case ERR:
      stop();
      break;

    default:                          // 1, 2, 3 ti selezionano i rispettivi slot nell'hotbar
      int digit = ch-'0';
      if(digit >= 1 && digit <= 3) {
        current_game.getInventory()->setSelected(digit-1);
        current_game.UpState();
      }
      break;
  }
}

void Player::attack(WINDOW * win) {
  int s = current_game.getInventory()->getSelected();
  Item item = current_game.getInventory()->getBarItem(0,s);
  int id = item.getId(), special = item.getAmount(); // ID dell'ITEM IN MANO ed il suo "special amount"

  if(id!=0) {
    int ammos = current_game.getAmmo();

    /* GESTIONE INTERAZIONI CON LA SPADA */
    if(id<10) {
      wattron(win,  COLOR_PAIR(3));
      for(int i=1;i<=1+special;i++)   // STAMPA SPADA LUNGA 'special' A SCHERMO
        mvwaddch(win, getY(), getX()+ds*i, '-');
      wattroff(win, COLOR_PAIR(3));

      this->swordX = getX();
      this->swordY = getY();
      this->swordL = special;
      this->swording = true; // AVVISA CHE STIAMO ATTACCANDO CON LA SPADA

    }
    /* INTERAZIONI CON L'ARCO */
    else if (id < 20 && ammos > 0) {
      shoot();
      current_game.setAmmo(ammos-1);
    }
    /* INTERAZIONI CON LE POZIONI */
    else if(id < 40 && id >= 30) {

      if(id == 32)
        current_game.setLives(current_game.getLives()+1); // pozione "One Life Up"
      
      else {
        int total = current_game.getVita()+item.getModifier(0); // rimanenti pozioni di guarigione
        if(total > 10+current_game.getMaxVita()) 
          total = 10+current_game.getMaxVita();
        current_game.setVita(total);
      }

      inv->setBarItem(0,inv->getSelected(),Item());   // "Consuma" l'item
      current_game.UpState();
    }
  }
}

/* CANCELLA LA SPADA STAMPATA A SCHERMO */
void Player::swordAtk(WINDOW * win){
  for(int i=1;i<=1+this->swordL;i++) 
        mvwaddch(win, swordY, swordX+ds*i, ' ');

  this->swording = false;
}

bool Player::isSwording() {return this->swording;}
swordXY Player::swordInfo(){return {swordX, swordY, 1+swordL, ds};}


void Player::shoot(){
  if(!bulletFired){
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

/* NEL CASO STIA RIFLETTENDO UN COLPO AVVERSARIO CON LO SCUDO */
bool isReflecting = false;
int reflectingDmg = 0;

void Player::moveBullet(WINDOW * win){
  // (MULTIPLIER) amount: 1 -> m = 2/2 = 1 | 2 -> m = 3/2 = 1.5 | 3 -> m = 4/2 = 2
  double m = (1+current_game.getInventory()->getBarItem(0,current_game.getInventory()->getSelected()).getAmount())/2.0; 
  
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
    if(isReflecting) isReflecting = false;
  }
}

void Player::display() {
  mvwaddch(curwin, y, x, character);
  refresh();
  current_game.setPlayerPos(x, y);
}