#include "inventory.hpp"

void equip(){
    // SE l'oggetto non è gia equipaggiato, si seleziona con quale sostituirlo tra i 3 equipaggiati
    // Quello rimosso torna nell'inventario
}

void inspect(){
    // Informazioni su tipo di oggetto, effetto, danni, cure ecc...
}

void sell(){
    // oggetto rimosso dall'inventario e soldi aggiunti al player
    // prima chiedi se sei sicuro di voler vendere (bisognerebbe poter vedere il valore prima)
}
Inventory * inv;

void openchoice(WINDOW * choiceWin, int pos){
    int syMax, sxMax;
    getmaxyx(choiceWin, syMax, sxMax);
    // WINDOW *choiceWin = newwin(syMax-(syMax/10)-2, sxMax-(sxMax/10)-2, syMax/20+2, sxMax/20+1);
    box(choiceWin, 0, 0);
    keypad(choiceWin, true);
    nodelay(choiceWin, TRUE);


    int n = 3;
    char actions[n][20] = {"", "", "Back"};

    Item item;
    int b = -(pos+1)/3;
    if(pos>=0) item = (inv->getInventoryItem(pos))->val;
    else item = inv->getBarItem(b,pos+3*(b+1));

    if(pos>=0) {
        strcpy(actions[0],"Equip ");
        if(item.getBar()) strcat(actions[0], "to ARMOR");
        else strcat(actions[0], "to HOTBAR");

    } else strcpy(actions[0],"Unequip");

    sprintf(actions[1], "Sell for %d$", item.getPrice()/2);
    int highlights = 0, select = 0, choice;

    char itemname[20];
    item.getName(itemname);
    //char idk[10]; sprintf(idk, " %d",pos); strcat(itemname, idk);
    mvwprintw(choiceWin, 1, 57, "Hai selezionato: %s", itemname);

    char stats[CATEGORIES][20] = {"Bonus Health", "Atk. Damage", "Resistence", "Luck"};
    int mod = 0, row = 0;
    while(mod<CATEGORIES) {
        double val = item.getModifier(mod);
        if(val!=0) {
            mvwprintw(choiceWin, 3+row, 57, " * %.1f %s", val, stats[mod]);
            row++;
        }
        mod++;
    }

    char desc[60];
    item.getDesc(desc);
    mvwprintw(choiceWin, 13, 56, "\"%s\"", desc);

    bool open = true;
    while(open){
        for (int i = 0; i < n; i++){ // costruisco il menu
            if (i == highlights) wattron(choiceWin, A_REVERSE);
            mvwprintw(choiceWin, i+4+row, 57, "%s", actions[i]);
            wattroff(choiceWin, A_REVERSE);
        }
        choice = wgetch(choiceWin);

        switch(choice){ // mi muovo nel menu
            case KEY_UP:
                highlights--, select--;
                if (highlights == -1) highlights = 0, select = 0;
                break;
            case KEY_DOWN:
                highlights++, select++;
                if (highlights == n) highlights = n-1, select = n-1;
                break;
            case 'i':
                open = false;
                wclear(choiceWin);
                break;
            case 10:
                open = false;
                if (select == 0) {
                    if(pos>=0) inv->equip(pos);
                    else inv->unequip(b,pos+3*(b+1));
                    current_game.UpState();
                }
                else if (select == 1) {
                    current_game.setMoney(current_game.getMoney()+item.getPrice()/2);
                    if(pos>=0) inv->remove(pos);
                    else {
                        inv->setBarItem(b, pos+3*(b+1), Item());
                        current_game.UpState();
                    }
                    
                }
                wclear(choiceWin);
                break;
            default:
                break;
        }
    }
}


void open_inventory(WINDOW * invWin){
    wclear(invWin);
    int syMax, sxMax;
    getmaxyx(invWin, syMax, sxMax);

    box(invWin, 0, 0);
    keypad(invWin, true);
    nodelay(invWin, TRUE);

    // gli oggetti nell'inventario saranno una lista, n la lunghezza della lista
    //int n = 4;
    //string oggetti[n] = {"spada lunga", "scudo di doran", "palle potenti", "freccia"};
    inv = current_game.getInventory();
    int len, choice, highlights = 0, lastItem = 0, column = 1, page = 1;
    int maxPage;
    //if(len%(syMax-4)==0) maxPage--;
    //init_pair(3, 245, COLOR_BLACK);
    bool open = true;
    while (open){
        len = inv->calcLen();
        maxPage = (len/(syMax-4))+1;

        box(invWin, 0, 0);

        if(page <= 1) wattron(invWin, COLOR_PAIR(3));
        else if(column == 0) wattron(invWin, A_REVERSE);
        mvwprintw(invWin, 1, 1, "[<]");
        wattroff(invWin, COLOR_PAIR(3));
        wattroff(invWin, A_REVERSE);

        if(column == 1) wattron(invWin, A_REVERSE);
        mvwprintw(invWin, 1, 5, "Inventory (Page %d)",page);
        wattroff(invWin, A_REVERSE);

        if(page >= maxPage) wattron(invWin, COLOR_PAIR(3));
        else if(column == 2) wattron(invWin, A_REVERSE);
        mvwprintw(invWin, 1, 24, "[>]");
        wattroff(invWin, COLOR_PAIR(3));
        wattroff(invWin, A_REVERSE);

        //int hots = inv->firstSlot(0);
        Item chosen;
        if(column == 3) wattron(invWin, A_REVERSE);
        mvwprintw(invWin, 2, 33, "HOTBAR");
        wattroff(invWin, A_REVERSE);
        for(int i=0;i<3;i++) {
            char itemname[20];
            Item item = inv->getBarItem(0,i);
            item.getName(itemname);
            if(inv->getSelected() == i) {
                wattron(invWin, A_REVERSE);
                chosen = item;
            }
            mvwprintw(invWin, i+3, 32, "[%d] %s", i+1, itemname);
            wattroff(invWin, A_REVERSE);
        }
    

        //int armors = inv->firstSlot(1);
        //if(armors<0) wattron(invWin, COLOR_PAIR(3));
        if(column == 4) wattron(invWin, A_REVERSE);
        mvwprintw(invWin, 7, 33, "ARMOR");
        wattroff(invWin, A_REVERSE);

        for(int i=0;i<3;i++) {
            char itemname[20];
            Item item = inv->getBarItem(1,i);
            item.getName(itemname);
            if(item.getId()==0) wattron(invWin, COLOR_PAIR(3));
            if(i==highlights && column == 4) {
                wattron(invWin, A_REVERSE);
                chosen = item;
            }
            mvwprintw(invWin, i+8, 32, "- %s", itemname);
            wattroff(invWin, A_REVERSE);
            wattroff(invWin, COLOR_PAIR(3));
        }
        
        pitemlist l = inv->getInventoryItem(lastItem);
        int i = 0;
        while(l!=NULL && i<syMax-4) {
            char itemname[20];
            l->val.getName(itemname);
            if (i == highlights && column == 1) {
                wattron(invWin, A_REVERSE);
                chosen = l->val;
            }
            mvwprintw(invWin, i+3, 2, itemname);
            wattroff(invWin, A_REVERSE);

            i++;
            l = l->next;
        }

        choice = wgetch(invWin);
        bool doit = true, skip = false;
        switch(choice){ // mi muovo nel menu
            case KEY_UP:
            //SCORRE IN VERTICALE INVENTARIO/BARS
                if(column == 3) {
                    int s = inv->getSelected();
                    if(s>0) inv->setSelected(s-1);
                }
                    highlights--;
                    if (highlights == -1) highlights = 0;
                
                break;
            case KEY_DOWN:
                if(column == 3) {
                    int s = inv->getSelected();
                    if(s<2) inv->setSelected(s+1);
                }
                    highlights++;
                    if ((highlights == i && column == 1) || 
                    (highlights==3 && column >= 3)) 
                        highlights--;
                break;

            //SKIPPANO LA COLONNA DELLE FRECCETTE SE NON POSSONO ESSERE USATE
            case KEY_LEFT:
                if(column>0) {
                    if(column==1 && page == 1)
                        doit = false;
                    else if(column==3 && page==maxPage)
                        skip = true;
                } else doit = false;

                if(doit) {
                    column -= 1+skip;
                    highlights = 0;
                }
                break;
            case KEY_RIGHT:
                if(column<4) {
                    if(column==1 && page==maxPage)
                        skip = true;
                } else doit = false;

                if(doit) { 
                    column += 1+skip;
                    highlights = 0;
                } break;
            
            case 'i':
                open = false;
                wclear(invWin);
                break;
            case 10:
                //SCROLLANDO LE PAGINE DELL'IVENTARIO
                if(column==0) {
                    lastItem -= syMax-4;
                    page--;
                    if(page==1) column = 1;
                    wclear(invWin);
                } else if(column==2) {
                    lastItem += syMax-4;
                    page++;
                    if(page==maxPage) column = 1;
                    wclear(invWin);
                }
                // SE NON STAI SELEZIONANDO NELL'HOTBAR IL VUOTO ->
                else if(chosen.getId()>0 && (column != 1 || len>0)){
                    int pos;
                    if(column==1) pos = lastItem+highlights;
                    else pos = highlights-3*(column-2);
                    openchoice(invWin, pos);
                    highlights=0;
                } 

                break;
            default:
                int digit = choice-'0';
                if(digit >= 1 && digit <= 3) {
                    inv->setSelected(digit-1);
                    if(column == 3) highlights = digit-1;
                }
                    
                break;
        }
        if(column == 3)
            highlights = inv->getSelected();
    }
}