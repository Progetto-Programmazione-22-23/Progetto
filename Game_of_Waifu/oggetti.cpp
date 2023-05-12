#include "oggetti.hpp"
//#include <iostream>

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
    int id, price, rarity, upgrade_id, amount;
    double plus[CATEGORIES];
    char name[25], desc[60];
    bool shop, bar;
    while(in>>id>>price>>name>>shop>>bar>>rarity>>upgrade_id>>amount>>desc>>
    plus[0]>>plus[1]>>plus[2]>>plus[3]>>plus[4]>>plus[5]) {
        //std::cout<<id<<price<<name<<shop<<bar<<rarity<<upgrade_id<<desc<<"\n";
        spacePhrase(name);
        spacePhrase(desc);
        //allItems = addItem(allItems, Item(id,price,name,shop,bar,rarity,upgrade_id,desc));
        allItems = addItem(allItems, Item(id,price,name,shop,bar,rarity,upgrade_id,desc, amount));
        allItems->val.setModifiers(plus);
    }
    in.close();
}

Item::Item(int id, int price, char name[], bool shoppable, bool hot_armor, int rarity, int upgrade, char desc[], int amount) {
//Item::Item(int id, int price, char name[], bool shoppable, bool hot_armor, char desc[]) {
    this->id = id;
    this->price = price;
    strcpy(this->name, name);
    
    this->shoppable = shoppable;
    this->hot_armor = hot_armor;
    this->rarity = rarity;
    this->upgrade = upgrade;
    this->amount = amount;
    strcpy(this->desc, desc);
    for(int i=0;i<CATEGORIES;i++) this->modifiers[i] = 0;
}
int Item::getId() { return id; }
int Item::getPrice() { return price; }
void Item::getName(char* name) { strcpy(name,this->name); }
void Item::getDesc(char* desc) { strcpy(desc,this->desc); }
bool Item::isShoppable() { return shoppable; }
bool Item::getBar() { return hot_armor; }
int Item::getRarity() { return rarity; }
int Item::upgradesFrom() { return upgrade; }
int Item::getAmount() { return amount; }
void Item::setModifiers(double mods[]) {
    for(int i=0;i<CATEGORIES;i++)
        this->modifiers[i] = mods[i];
}
double Item::getModifier(int i) { return this->modifiers[i];}

Inventory::Inventory(pitemlist inv) {
    this->inv = inv;
    for(int i=0;i<3;i++) {
        this->hotbar[i] = Item();
        this->armor[i] = Item();
    }
    this->selected = 0;
}
void Inventory::setBars(Item hotbar[], Item armor[]) {
    for(int i=0;i<3;i++) {
        this->hotbar[i] = hotbar[i];
        this->armor[i] = armor[i];
    }
}

int Inventory::firstSlot(bool hot_armor) {
    int free=-1;
    for(int i=0;i<3 && free<0;i++) {
        if(!hot_armor) {
            if(this->hotbar[i].getId() == 0) free = i;
        }
        else {
            if(this->armor[i].getId() == 0) free = i;
        }
    }  
    return free;
}
Item Inventory::remove(int index) {
    Item removed;
    if(index==0) {
        removed = this->inv->val;
        this->inv = this->inv->next;
    }
    else {
        pitemlist t = this->inv;
        for(int i=0;i<index-1 && t!=NULL;i++) t = t->next;
        
        if(t!=NULL) {
            removed = t->next->val;
            t->next = t->next->next;
        }
    }
    
    return removed;
}
void Inventory::giveItem(Item item) {
    this->inv = addItem(this->inv, item);
}
void Inventory::equip(int index) {
    Item item = Inventory::remove(index);
    bool bar = item.getBar();
    Inventory::setBarItem(bar, Inventory::firstSlot(bar), item);
}
void Inventory::unequip(bool hot_armor, int index) {
    //Inventory::giveItem()
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
        return found;
    }
}
