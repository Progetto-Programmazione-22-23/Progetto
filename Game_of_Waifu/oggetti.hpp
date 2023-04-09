#include <string.h>

class Item {
    protected:
        int id, price, amount, category;
        char name[20];
    public:
        Item(int id=0, int price=0, char name[]="ciao", int category=0, int amount=0);
        int getId();
        int getPrice();
        void getName(char* name);
};

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
        pitemlist getInventoryHead();
        //pitemlist insertInInv(Item el);
};