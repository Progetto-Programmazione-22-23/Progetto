#include <ncurses.h>
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;


int printItemStats(WINDOW * choiceWin, Item item);
void openchoice(WINDOW * win, int pos);
void open_inventory(WINDOW * win);