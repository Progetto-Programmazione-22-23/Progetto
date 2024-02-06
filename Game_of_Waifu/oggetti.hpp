#include <string.h>
#include <fstream>
#define CATEGORIES 4

class Item {
    protected:
        int id, price, upgrade, amount;
        double modifiers[CATEGORIES];
        char name[25], desc[60];
        bool hot_armor;
    public:
        Item(int id=0, int price=0, char name[]="#", bool hot_armor=true, int upgrade=0, char desc[]="", int amount=0);
        void setModifiers(int mods[]);
        int getId();
        int getPrice();
        void getName(char* name);
        void getDesc(char* desc);
        bool getBar();
        int upgradesFrom();
        int getAmount();
        double getModifier(int i);
        void setModifiers(double modifiers[]);
};


void loadItems();

struct itemlist {
    Item val;
    itemlist* next;
};
typedef itemlist* pitemlist;

Item getItem(pitemlist l, int index);
pitemlist addItem(pitemlist l, Item item);