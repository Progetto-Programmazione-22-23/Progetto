#include "oggetti.hpp"

Item allItems[2];

void loadItems() {
    std::ifstream in;
    in.open("items.txt");
    int a, b, i=0;
    while(in>>a>>b) {
        allItems[i] = Item(i, b, "bau");
        i++;
    }

    in.close();
}

Item::Item(int id, int price, char name[]) {
    this->id = id;
    this->price = price;
    strcpy(this->name, name);
    //this->category = category;
    //this->amount = amount;
}
int Item::getId() { return id; }
int Item::getPrice() { return price; }
void Item::getName(char* name) { strcpy(name,this->name); }

Inventory::Inventory(pitemlist inv) {
    this->inv = inv;
    for(int i=0;i<3;i++) {
        this->hotbar[i] = Item();
        this->armor[i] = Item();
    }
}
void Inventory::setBars(Item hotbar[], Item armor[]) {
    for(int i=0;i<3;i++) {
        this->hotbar[i] = hotbar[i];
        this->armor[i] = armor[i];
    }
}
Item Inventory::getBarItem(bool hot_armor, int i) {
    if(!hot_armor) return this->hotbar[i];
    else return this->armor[i];
}
pitemlist Inventory::getInventoryHead() { return this->inv;}


//Item shop_list[2] = {Item(),Item(1,300,"Healthy Armor",1,4)}
