#include "inv_logic.hpp"

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

void Inventory::remove(int index) {
    pitemlist q;
    if(index==0) {
        q = this->inv;
        this->inv = this->inv->next;
    }
    else {
        pitemlist t = this->inv;
        for(int i=0;i<index-1 && t->next!=NULL;i++) t = t->next;
        
        if(t->next!=NULL) {
            q = t->next;
            t->next = t->next->next;
        }
    }
    q = NULL, delete(q);
}

void Inventory::giveItem(Item item) {
    this->inv = addItem(this->inv, item);
}
void Inventory::insItem(Item item, int pos) {
    if(this->inv == NULL) giveItem(item);
    else {
        pitemlist q = new itemlist;
        q->val = item;

        pitemlist l = this->inv;
        while(pos>0 && l->next!=NULL) {
            l=l->next;
            pos--;
        }
        if(l->next==NULL) q->next = NULL;
        else q->next = l->next->next;
        l->next = q;
        
    }
    

}

int Inventory::calcLen() {
    int i=0;
    for(pitemlist l = this->inv; l!=NULL; l=l->next) i++;
    return i;
}

pitemlist Inventory::getInventoryItem(int index) {
    pitemlist l = this->inv;
    for(int i=0; i<index && l!=NULL; l = l->next) i++;
    return l;
}

void Inventory::equip(int index) {
    pitemlist item = Inventory::getInventoryItem(index);
    if(item->val.getBar()) {
        int slot = Inventory::firstSlot(1);
        if(slot>=0) {
            this->armor[slot] = item->val;
            Inventory::remove(index);
        }
    }
    else {
        Item sel = this->hotbar[this->selected];
        this->hotbar[this->selected] = item->val;
        item->val = sel;

        if(sel.getId()==0) {
            if(index==0) {
                this->inv = this->inv->next;
            } else {
                pitemlist precItem = Inventory::getInventoryItem(index-1);
                precItem->next = precItem->next->next;
                item = NULL, delete(item);
            }
        }
    }
}
void Inventory::unequip(bool hot_armor, int index) {
    Inventory::giveItem(Inventory::getBarItem(hot_armor,index));
    Inventory::setBarItem(hot_armor, index, Item());
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