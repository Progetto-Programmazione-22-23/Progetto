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

//sostituisce il primo item 'base' che trova con l'item 'up'
void Inventory::subItem(Item base, Item up) {
    bool found = false;
    for(int i=0;i<2 && !found;i++) 
        for(int j=0;j<3 && !found;j++)
            if(Inventory::getBarItem(i,j).getId() == base.getId()) {
                Inventory::setBarItem(i,j,up);
                found = true;
            }
    
    if(!found) {
        int i = 0;
        for(pitemlist q = this->inv; q != NULL && !found; q = q->next, i++)
            if(q->val.getId() == base.getId()) {
                q->val = up;
                found = true;
            } 
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

bool Inventory::isPossessed(int id) {
    if(id==0) return true;

    bool found = false;
    for(int i=0;i<2 && !found;i++)
        for(int j=0;j<3 & !found;j++)
            found = Inventory::getBarItem(i,j).getId()==id;
        
    if(!found)
        for(pitemlist q = this->inv; q != NULL && !found; q = q->next)
            found = q->val.getId()==id;

    return found;
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