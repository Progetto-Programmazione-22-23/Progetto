class Item {
    protected:
        int id, price, amount, category;
        char name[20];
    public:
        Item(int id=0, int price=0, char* name="", int category=0, int amount=0);
        int getId();
        int getPrice();
        void getName(char* name);
};
