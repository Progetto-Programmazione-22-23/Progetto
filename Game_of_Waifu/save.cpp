#include <fstream>
using namespace std;

struct game {
    bool nuovo;
    int player_pos[2];
};

game current_game = {true,{0,0}};

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

void save_player_pos(int x, int y) {
    ofstream out;
    out.open("player.txt");
    out<<x<<"\n"<<y;
    out.close();
}