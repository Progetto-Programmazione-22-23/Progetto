#include <fstream>
using namespace std;

struct game {
    bool nuovo;
    int player_pos[2], money;
};

game current_game = {true};

game get_last_game() {
    game last;

    //WIP
    int data, i=0;
    ifstream in;
    in.open("player.txt");
    while(in>>data) {
        if(i==0) last.player_pos[0] = data;
        else if(i==1) last.player_pos[1] = data;
        i++;
    }

    in.close();

    last.nuovo=false;
    

    return last;
}

void save_all() {
    ofstream out;
    out.open("player.txt");
    out<<current_game.player_pos[0]<<"\n"<<current_game.player_pos[0];
    out.close();
}

void save_player_pos(int x, int y) {
    current_game.player_pos[0] = x;
    current_game.player_pos[1] = y;
}