#include "oggetti.hpp"

void spacePhrase(char s[]) {
    for(int i=0; i<strlen(s); i++) 
        if(s[i]=='-') 
            s[i]=' ';
}

pitemlist allItems;
Item getItem(pitemlist l, int index) {
    Item item;
    for(pitemlist t = l; t != NULL; t = t->next) {
        if((t->val).getId()==index) item = t->val;
    }
    return item;
}
pitemlist addItem(pitemlist l, Item item) {
    pitemlist q = new itemlist;
    q->val = item;
    q->next = l;
    return q;
}

void loadItems() {
    allItems = NULL;
    std::ifstream in;
    in.open("items.txt");
    int id, price, rarity, upgrade_id;
    char name[25], desc[60];
    bool shop, bar;
    while(in>>id>>price>>name>>shop>>bar>>rarity>>upgrade_id>>desc) {
        //std::cout<<id<<price<<name<<shop<<bar<<rarity<<upgrade_id<<desc<<"\n";
        spacePhrase(name);
        spacePhrase(desc);
        //allItems = addItem(allItems, Item(id,price,name,shop,bar,rarity,upgrade_id,desc));
        allItems = addItem(allItems, Item(id,price,name,shop,bar,rarity,upgrade_id,desc));
    }
    in.close();
}

Item::Item(int id, int price, char name[], bool shoppable, bool hot_armor, int rarity, int upgrade, char desc[]) {
//Item::Item(int id, int price, char name[], bool shoppable, bool hot_armor, char desc[]) {
    this->id = id;
    this->price = price;
    strcpy(this->name, name);
    
    this->shoppable = shoppable;
    this->hot_armor = hot_armor;
    this->rarity = rarity;
    this->upgrade = upgrade;
    strcpy(this->desc, desc);
}
int Item::getId() { return id; }
int Item::getPrice() { return price; }
void Item::getName(char* name) { strcpy(name,this->name); }
void Item::getDesc(char* desc) { strcpy(desc,this->desc); }
bool Item::isShoppable() { return shoppable; }
bool Item::getBar() { return hot_armor; }
int Item::getRarity() { return rarity; }
int Item::upgradesFrom() { return upgrade; }

Inventory::Inventory(pitemlist inv) {
    this->inv = inv;
    for(int i=0;i<3;i++) {
        this->hotbar[i] = Item();
        this->armor[i] = Item();
    }
    this->selected = 1;
}
void Inventory::setBars(Item hotbar[], Item armor[]) {
    for(int i=0;i<3;i++) {
        this->hotbar[i] = hotbar[i];
        this->armor[i] = armor[i];
    }
}

// hot_armor 0: hotbar, 1: armor
Item Inventory::getBarItem(bool hot_armor, int i) {
    if(!hot_armor) return this->hotbar[i];
    else return this->armor[i];
}
void Inventory::setBarItem(bool hot_armor, int i, Item item) {
    if(!hot_armor) this->hotbar[i] = item;
    else this->armor[i] = item;
}
pitemlist Inventory::getInventoryHead() { return this->inv;}
void Inventory::setSelected(int hot) {
    this->selected = hot;
}
int Inventory::getSelected() { return selected; }
bool Inventory::isActive(bool hot_armor, int id) {
    if(!hot_armor) return hotbar[selected].getId() == id;
    else {
        bool found = false;
        for(int i=0;i<3 && !found;i++) {
            found = armor[i].getId() == id;
        }
    }
}
