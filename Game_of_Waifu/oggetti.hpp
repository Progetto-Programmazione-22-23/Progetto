#include <string.h>
#include <fstream>
#define CATEGORIES 2

class Item {
    protected:
        int id, price, modifiers[2];
        char name[20];
    public:
        Item(int id=0, int price=0, char name[]="ciao");
        int getId();
        int getPrice();
        void getName(char* name);
};

void loadItems();

struct itemlist {
    Item val;
    itemlist* next;
};
typedef itemlist* pitemlist;


class Inventory {
    protected:
        pitemlist inv;
        Item hotbar[3], armor[3];
    public:
        Inventory(pitemlist inv=NULL);
        void setBars(Item hotbar[], Item armor[]);
        Item getBarItem(bool hot_armor, int i);
        void setBarItem(bool hot_armor, int i, Item item);
        pitemlist getInventoryHead();
        
        //pitemlist insertInInv(Item el);
};