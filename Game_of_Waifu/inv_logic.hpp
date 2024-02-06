#include "oggetti.cpp"

class Inventory {
    protected:
        pitemlist inv;
        Item hotbar[3], armor[3];
        int selected;
           
    public:
        void remove(int index);
        int firstSlot(bool hot_armor);
        Inventory(pitemlist inv=NULL);
        void setBars(Item hotbar[], Item armor[]);
        Item getBarItem(bool hot_armor, int i);
        void setBarItem(bool hot_armor, int i, Item item);
        pitemlist getInventoryItem(int index);
        bool isPossessed(int id);
        int calcLen();
        void setSelected(int hot);
        int getSelected();
        void giveItem(Item item);
        void subItem(Item base, Item up);
        void equip(int index);
        void unequip(bool hot_armor, int index);
};