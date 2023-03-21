#include <fstream>
using namespace std;

struct game {
    bool nuovo;
    int player_pos[2];
};

game new_game = {true,{0,0}};

game get_last_game() {
    game last;

    //WIP
    int xplayer, yplayer;
    ifstream in;
    in.open("player.txt");
    in>>xplayer>>yplayer;

    in.close();

    last.nuovo=false;
    last.player_pos[0]=xplayer;
    last.player_pos[1]=yplayer;

    return last;
}

void save_player_pos(int x, int y) {
    ofstream out;
    out.open("player.txt");
    out<<x<<"\n"<<y;
    out.close();
}