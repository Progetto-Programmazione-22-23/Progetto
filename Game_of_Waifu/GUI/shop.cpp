#include "shop.hpp"

bool need2clear = false, wasGood = false;
void clearSelect(WINDOW * win, int start, int end) { // di default cancella solo la parte finale del menu
    if(end<0) {
        int xmax, ymax;
        getmaxyx(win, ymax, xmax);
        end = xmax;
    }
    for(int i=start;i<end;i++)
        for(int j=1;j<15;j++)
            mvwprintw(win, j, i, " ");
    need2clear = start<56; // non c'è più bisogno di pulire solo nel caso abbia cancellato davvero l'ultima parte
}

void purchaseFeedback(WINDOW * win, bool success) {
    wattron(win, COLOR_PAIR(1+success));
    mvwprintw(win,3,59-(2*!success),"Item acquistato");
    mvwprintw(win,4,60,"correttamente");
    if(!success) mvwprintw(win,4,56,"NON");
    wattroff(win, COLOR_PAIR(1+success));
    need2clear = true, wasGood = success; // messaggio stampato: c'è bisogno di pulire
}

void OpenChoiceShop(WINDOW * choiceWin, Item item){
    box(choiceWin, 0, 0);
    keypad(choiceWin, true);
    nodelay(choiceWin, TRUE);

    int n = 2;
    bool upgrade = item.upgradesFrom()>0;
    Item baseItem;
    if(upgrade) baseItem = getItem(allItems,item.upgradesFrom());
    char azioni[n][20] = {"", "Back"};
    int highlights = 0, choice;

    if(upgrade) sprintf(azioni[0],"Upgrade for ", item.getPrice());
    else sprintf(azioni[0],"Buy for ", item.getPrice());

    int row = printItemStats(choiceWin, item);

    bool open = true;
    while(open){
        
        if (highlights == 0) wattron(choiceWin, A_REVERSE);
        mvwprintw(choiceWin, row+4, 58, azioni[0]);
        if(upgrade) {
            char basename[20];
            baseItem.getName(basename);
            mvwprintw(choiceWin, row+5, 58, " (from %s)", basename);
        }
        wattroff(choiceWin, A_REVERSE);

        if(highlights==0) wattron(choiceWin, COLOR_PAIR(104));
        else wattron(choiceWin, COLOR_PAIR(5));
            mvwprintw(choiceWin, row+4, 66+upgrade*4, "%d$", item.getPrice());
        wattroff(choiceWin, COLOR_PAIR(104));
        wattroff(choiceWin, COLOR_PAIR(5));

        if (highlights == 1) wattron(choiceWin, A_REVERSE);
        mvwprintw(choiceWin, row+5+upgrade, 58, azioni[1]);
        wattroff(choiceWin, A_REVERSE);

        
        choice = wgetch(choiceWin);

        switch(choice){ // mi muovo nel menu
            case KEY_UP:
                highlights--;
                if (highlights == -1) highlights = 0;
                break;
            case KEY_DOWN:
                highlights++;
                if (highlights == n) highlights = n-1;
                break;
            case 'o':
                open = false;
                clearSelect(choiceWin);
                break;
            case 10:
                open = false;
                clearSelect(choiceWin); 

                if(highlights==0) {
                    bool enough = current_game.getMoney()>=item.getPrice();
                    if(enough) {
                        current_game.setMoney(current_game.getMoney()-item.getPrice());
                        if(item.getId() == 19) 
                            current_game.setAmmo(current_game.getAmmo()+5); // ECCEZIONE PER QUANDO SI COMPRANO I PROIETTILI
                        
                        else {
                            Inventory *inv = current_game.getInventory();
                            if(upgrade) {
                                inv->subItem(baseItem,item);
                                current_game.UpState();
                            } 
                            else inv->giveItem(item);
                        }
                    }
                    purchaseFeedback(choiceWin,enough);
                }
                break;
            default:
                break;
        }
    } }

void openWeapon(WINDOW * WeaponWin, int sel, char category[]){

    int n = 1;
    int choice;
    int highlights = 0;

    Inventory * inv = current_game.getInventory();

    pitemlist cat = NULL;
        for(pitemlist q = allItems; q!=NULL; q = q->next) {
            int id = q->val.getId();
            if(id>=sel*10 && (id<(sel+1)*10 || sel==4)) {
                if(inv->isPossessed(q->val.upgradesFrom())) 
                    cat = addItem(cat, q->val), n++;
            }
                
        }

    bool open = true;
    while(open){
        box(WeaponWin, 0, 0);

        mvwprintw(WeaponWin, 1, 33, "[%s]", category);

        

        Item chosen;
        int i = 0;
        for (pitemlist q = cat; q != NULL; i++, q=q->next){ // costruisco il menu
            if (i == highlights) {
                wattron(WeaponWin, A_REVERSE);
                chosen = q->val;
            }
            char itemname[20];
            q->val.getName(itemname);
            mvwprintw(WeaponWin, i+3, 32, itemname);
            wattroff(WeaponWin, A_REVERSE);
        }
        if (i == highlights) wattron(WeaponWin, A_REVERSE);
        mvwprintw(WeaponWin,i+4, 32, "Back");
        wattroff(WeaponWin, A_REVERSE);

        choice = wgetch(WeaponWin);

        switch(choice){ // mi muovo nel menu
            case KEY_UP:
                highlights--;
                if (highlights == -1) highlights = 0;
                break;
            case KEY_DOWN:
                highlights++;
                if (highlights == n) highlights = n-1;
                break;
            case 'o':
                open = false;
                wclear(WeaponWin);
                break;
            case 10:
                if (highlights == n-1) {
                    wclear(WeaponWin);
                    open = false;
                }
                else {
                    if(need2clear) clearSelect(WeaponWin);
                    OpenChoiceShop(WeaponWin, chosen);
                    if(wasGood) clearSelect(WeaponWin,32,55);
                    open = !wasGood;
                }
                break;
            default:
                break;
        }
    }
    wasGood = false;
}

void open_shop(WINDOW * shopWin){
    wclear(shopWin);
    box(shopWin, 0, 0);
    keypad(shopWin, true);
    nodelay(shopWin, TRUE);

    // n lunghezza shop
    int n = 5;
    char oggetti[n][20] = {"Spade", "Archi", "Scudi", "Pozioni", "Armature"};
    int choice;
    int highlights = 0;
    

    bool open = true;
    while (open){
        box(shopWin, 0, 0);
        mvwprintw(shopWin, 1, 2, "Negozio oggetti:");
        for (int i = 0; i < n; i++){ // costruisco il menu
            if (i == highlights) wattron(shopWin, A_REVERSE);
            mvwprintw(shopWin, i+3, 3, "%s", oggetti[i]);
            wattroff(shopWin, A_REVERSE);
        }
        choice = wgetch(shopWin);

        switch(choice){ // mi muovo nel menu
            case KEY_UP:
                highlights--;
                if (highlights == -1) highlights = 0;
                break;
            case KEY_DOWN:
                highlights++;
                if (highlights == n) highlights = n-1;
                break;
            case 'o':
                open = false;
                wclear(shopWin);
                break;
            case 10:
                openWeapon(shopWin, highlights, oggetti[highlights]);
                break;
            default:
                break;
        }
    }
}