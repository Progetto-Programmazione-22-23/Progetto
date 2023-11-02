#include <ncurses.h>
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

void equip();
void inspect();
void sell();

void openchoice(WINDOW * win, int, string[]);
void open_inventory(WINDOW * win);