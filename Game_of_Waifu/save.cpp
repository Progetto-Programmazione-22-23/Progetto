#include <fstream>
#include "save.hpp"
using namespace std;

igame fresh = {true,0,0,0,10,10,1,0,};//{Item(1,300,"Healthy Armor",1,4),Item(),Item()}};
Game current_game = Game(fresh);

Game::Game(igame s) {
    this->setting = s;
}

void Game::saveAll() {
    ofstream out;
    out.open("player.txt");
    out<<setting.xplayer<<"\n"
    <<setting.yplayer<<"\n"
    <<setting.money<<"\n"
    <<setting.vita<<"\n"
    <<setting.maxvita<<"\n";
    out.close();
}

void Game::continueLast() {
    igame last;

    int data, i=0;
    ifstream in;
    in.open("player.txt");
    while(in>>data) {
        if(i==0) last.xplayer = data;
        else if(i==1) last.yplayer = data;
        else if(i==2) last.money = data;
        else if(i==3) last.vita = data;
        else if(i==4) last.maxvita = data;
        i++;
    }

    in.close();
    last.nuovo=false;
    
    setting = last;
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