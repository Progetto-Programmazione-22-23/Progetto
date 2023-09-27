#include "save.hpp"

igame fresh = {0,0,0,0,7,{0,0,0,0,0,0},Inventory(),true};//{Item(1,300,"Healthy Armor",1,4),Item(),Item()}};
Game current_game = Game(fresh);

Game::Game(igame s) { this->setting = s;  this->state = 0; }
Inventory* Game::getInventory() { return &(this->setting.inventory); }

void debugging() {
    //std::cout<<"sus";
    //current_game.setMoney(current_game.getMoney()+1);
    //Inventory inv = current_game.getInventory();
    //inv.setBarItem(0,1,allItems[1]);
    //current_game.setInventory(inv);
}

void Game::updateStats() {
    double s[CATEGORIES] = {};
    for(int i=0;i<3;i++)
        for(int j=0;j<CATEGORIES;j++)
            s[j] += setting.inventory.getBarItem(1,i).getModifier(j);

    for(int j=0;j<CATEGORIES;j++)
        s[j] += setting.inventory.getBarItem(0,setting.inventory.getSelected()).getModifier(j);
    
    for(int i=0;i<CATEGORIES;i++) {
        setting.stats[i] = s[i];
    }
}

void Game::saveAll() {
    std::ofstream out;
    out.open("player.txt");
    out<<setting.xplayer<<"\n"
    <<setting.yplayer<<"\n"
    <<setting.map<<"\n"
    <<setting.money<<"\n"
    <<setting.vita<<"\n";
    for(int j=0;j<CATEGORIES;j++) 
        out<<setting.stats[j]<<"\n";
    for(int j=0;j<2;j++) for(int i=0;i<3;i++) 
        out<<setting.inventory.getBarItem(j,i).getId()<<"\n";
    for(pitemlist l = setting.inventory.getInventoryHead();l!=NULL;l=l->next)
        out<<l->val.getId()<<"\n";
    out.close();
}

void Game::continueLast() {
    igame last;

    double data; 
    int i=0;
    std::ifstream in;
    in.open("player.txt");
    Item hotbar[3], armor[3];
    Inventory playerInv = Inventory();
    while(in>>data) {
        if(i==0) last.xplayer = data;
        else if(i==1) last.yplayer = data;
        else if(i==2) last.map = data;
        else if(i==3) last.money = data;
        else if(i==4) last.vita = data;
        else if(i<=4+CATEGORIES) last.stats[i-5] = data; // i = 4
        else if(i<=7+CATEGORIES) hotbar[i-(CATEGORIES+5)] = getItem(allItems, (int)data);
        else if(i<=10+CATEGORIES) armor[i-(CATEGORIES+8)] = getItem(allItems, (int)data);
        else playerInv.giveItem(getItem(allItems, (int)data));
        i++;
    }

    in.close();
    last.nuovo2=false;

    playerInv.setBars(hotbar, armor);
    last.inventory = playerInv;
    
    this->setting = last;
}

int Game::getState() { return this->state; }
void Game::UpState() { this->state++;}

bool Game::eNuovo() {
    return this->setting.nuovo2;
}

void Game::setPlayerPos(int x, int y) {
    setting.xplayer = x;
    setting.yplayer = y;
}

int Game::getPlayerX() {
    return setting.xplayer;
}
int Game::getPlayerY() {
    return setting.yplayer;
}

void Game::setMoney(int x) {
    setting.money = x;
}
int Game::getMoney() {
    return setting.money;
}

void Game::setVita(double x) {
    setting.vita = x;
}
double Game::getVita() {
    return setting.vita;
}
double Game::getMaxVita() {
    return setting.stats[0];
}
int Game::getMap() {
    return setting.map;
}
void Game::setMap(int i) {
    setting.map = i;
}
double Game::getAtk() { return setting.stats[1];}
double Game::getMagic(){ return setting.stats[2];}
double Game::getRes(){ return setting.stats[3];}
double Game::getSpeed(){ return setting.stats[4];}
double Game::getLuck(){ return setting.stats[5];}