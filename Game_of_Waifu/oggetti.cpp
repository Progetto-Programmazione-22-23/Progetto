#include "oggetti.hpp"
#include <string.h>

Item::Item(int id, int price, char* name, int category, int amount) {
    this->id = id;
    this->price = price;
    strcpy(this->name, name);
    this->category = category;
    this->amount = amount;
}
int Item::getId() { return id; }
int Item::getPrice() { return price; }
void Item::getName(char* name) { strcpy(name,this->name); }

//Item shop_list[2] = {Item(),Item(1,300,"Healthy Armor",1,4)}

class Usable : public Item {

};

class PowerUp : public Item {

};