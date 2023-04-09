#include <fstream>
#include "save.hpp"
using namespace std;

//Item test = ;
igame fresh = {true,0,0,0,10,10,1,0,Inventory()};//{Item(1,300,"Healthy Armor",1,4),Item(),Item()}};
Game current_game = Game(fresh);

Game::Game(igame s) { this->setting = s; }
Inventory Game::getInventory() { return this->setting.inventory; }

void Game::saveAll() {
    ofstream out;
    out.open("player.txt");
    out<<setting.xplayer<<"\n"
    <<setting.yplayer<<"\n"
    <<setting.money<<"\n"
    <<setting.vita<<"\n"
    <<setting.maxvita<<"\n"
    <<setting.damage<<"\n"
    <<setting.res<<"\n";
    for(int j=0;j<2;j++) for(int i=0;i<3;i++) 
        out<<setting.inventory.getBarItem(j,i).getId()<<"\n";
    //for(pitemlist l = setting.inventory.getInventoryHead();l!=NULL;l=l->next)
    out.close();
}

void Game::continueLast() {
    igame last;

    int data, i=0;
    ifstream in;
    in.open("player.txt");
    Item hotbar[3], armor[3];
    while(in>>data) {
        if(i==0) last.xplayer = data;
        else if(i==1) last.yplayer = data;
        else if(i==2) last.money = data;
        else if(i==3) last.vita = data;
        else if(i==4) last.maxvita = data;
        else if(i==5) last.damage = data;
        else if(i==6) last.res = data;
        else if(i<=9) hotbar[i-7] = allItems[data];
        else if(i<=12) armor[i-10] = allItems[data];
        i++;
    }

    in.close();
    last.nuovo=false;

    Inventory playerInv = Inventory();
    playerInv.setBars(hotbar, armor);
    last.inventory = playerInv;
    
    this->setting = last;
}

bool Game::isNew() {
    return setting.nuovo;
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

void Game::setVita(int x) {
    setting.vita = x;
}
int Game::getVita() {
    return setting.vita;
}

void Game::setMaxVita(int x) {
    setting.maxvita = x;
}
int Game::getMaxVita() {
    return setting.maxvita;
}