#include <fstream>
using namespace std;

struct game {
    bool nuovo;
    int player_pos[2], money;
    double vita;
};

game current_game = {true,{0,0},0,5};

game get_last_game() {
    game last;

    //WIP
    int data, i=0;
    ifstream in;
    in.open("player.txt");
    while(in>>data) {
        if(i==0) last.player_pos[0] = data;
        else if(i==1) last.player_pos[1] = data;
        else if(i==2) last.money = data;
        else if(i==3) last.vita = data;
        i++;
    }

    in.close();

    last.nuovo=false;
    

    return last;
}

void save_all() {
    ofstream out;
    out.open("player.txt");
    out<<current_game.player_pos[0]<<"\n"<<current_game.player_pos[0]<<"\n"<<current_game.money<<"\n"<<current_game.vita;
    out.close();
}

void save_player_pos(int x, int y) {
    current_game.player_pos[0] = x;
    current_game.player_pos[1] = y;
}

void save_money(int x) {
    current_game.money = x;
}

void save_vita(double x) {
    current_game.vita = x;
}