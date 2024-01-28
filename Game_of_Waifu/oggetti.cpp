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
    int id, price, upgrade_id, amount;
    double plus[CATEGORIES];
    char name[25], desc[60];
    bool bar;
    while(in>>id>>price>>name>>bar>>upgrade_id>>amount>>desc>>
    plus[0]>>plus[1]>>plus[2]>>plus[3]) {
        //std::cout<<id<<price<<name<<shop<<bar<<rarity<<upgrade_id<<desc<<"\n";
        spacePhrase(name);
        spacePhrase(desc);
        //allItems = addItem(allItems, Item(id,price,name,shop,bar,rarity,upgrade_id,desc));
        allItems = addItem(allItems, Item(id,price,name,bar,upgrade_id,desc, amount));
        allItems->val.setModifiers(plus);
    }
    in.close();
}

Item::Item(int id, int price, char name[], bool hot_armor, int upgrade, char desc[], int amount) {
//Item::Item(int id, int price, char name[], bool shoppable, bool hot_armor, char desc[]) {
    this->id = id;
    this->price = price;
    strcpy(this->name, name);
    
    this->hot_armor = hot_armor;
    this->upgrade = upgrade;
    this->amount = amount;
    strcpy(this->desc, desc);
    for(int i=0;i<CATEGORIES;i++) this->modifiers[i] = 0;
}
int Item::getId() { return id; }
int Item::getPrice() { return price; }
void Item::getName(char* name) { strcpy(name,this->name); }
void Item::getDesc(char* desc) { strcpy(desc,this->desc); }
bool Item::getBar() { return hot_armor; }
int Item::upgradesFrom() { return upgrade; }
int Item::getAmount() { return amount; }
void Item::setModifiers(double mods[]) {
    for(int i=0;i<CATEGORIES;i++)
        this->modifiers[i] = mods[i];
}
double Item::getModifier(int i) { return this->modifiers[i];}
