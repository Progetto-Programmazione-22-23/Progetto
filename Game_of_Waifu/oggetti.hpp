#include <string.h>
#include <fstream>
#define CATEGORIES 6

class Item {
    protected:
        int id, price, rarity, upgrade;
        double modifiers[CATEGORIES];
        //int id, price, modifiers[2];
        char name[25], desc[60];
        bool shoppable=false, hot_armor=true;
    public:
        Item(int id=0, int price=0, char name[]="ciao", bool shoppable=false, bool hot_armor=true, int rarity=0, int upgrade=0, char desc[]="");
        //Item(int id=0, int price=0, char name[]="", bool shoppable=false, bool hot_armor=true, char desc[]="");
        void setModifiers(int mods[]);
        int getId();
        int getPrice();
        void getName(char* name);
        void getDesc(char* desc);
        bool isShoppable();
        bool getBar();
        int upgradesFrom();
        int getRarity();
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

class Inventory {
    protected:
        pitemlist inv;
        Item hotbar[3], armor[3];
        int selected;
    public:
        Inventory(pitemlist inv=NULL);
        void setBars(Item hotbar[], Item armor[]);
        Item getBarItem(bool hot_armor, int i);
        void setBarItem(bool hot_armor, int i, Item item);
        pitemlist getInventoryHead();
        void setSelected(int hot);
        int getSelected();
        bool isActive(bool hot_armor, int id);
        
        //pitemlist insertInInv(Item el);
};