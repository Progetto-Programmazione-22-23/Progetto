#include <ncurses.h>
using namespace std;

void clearSelect(WINDOW * win, int start=56, int end=-1);

void purchaseFeedback(WINDOW * win, bool success);

void OpenChoiceShop(WINDOW * win, string[]);

void openWeapon(WINDOW * WeaponWin, int n);

void open_shop(WINDOW * win);