#include "shop.hpp"

void OpenChoiceShop(WINDOW * chWin, Item item){
//     int syMax, sxMax;
//     getmaxyx(stdscr, syMax, sxMax);
//     WINDOW *choiceWin = newwin(syMax-(syMax/10)-2, sxMax-(sxMax/10)-2, syMax/20+2, sxMax/20+1);
//     box(choiceWin, 0, 0);
//     keypad(choiceWin, true);
//     nodelay(choiceWin, TRUE);

//     mvwprintw(choiceWin, 1, 2, "Hai selezionato: %s", obj[k]);

//     int n = 3;
//     string azioni[n] = {"compra", "ispeziona", "annulla"};
//     int highlights = 0, select = 0, choice;

//     bool open = true;
//     while(open){
//         for (int i = 0; i < n; i++){ // costruisco il menu
//             if (i == highlights) wattron(choiceWin, A_REVERSE);
//             mvwprintw(choiceWin, i+3, 2, "%s", azioni[i].c_str());
//             wattroff(choiceWin, A_REVERSE);
//         }
//         choice = wgetch(choiceWin);

//         switch(choice){ // mi muovo nel menu
//             case KEY_UP:
//                 highlights--, select--;
//                 if (highlights == -1) highlights = 0, select = 0;
//                 break;
//             case KEY_DOWN:
//                 highlights++, select++;
//                 if (highlights == n) highlights = n-1, select = n-1;
//                 break;
//             case 'p':
//                 open = false;
//                 break;
//             default:
//                 break;
//         }
//         if (choice == 10){ // quando premo invio
//             if (select == 0) buy();
//             else if (select == 1) inspectshop();
//             break;
//         }
//     }
}

void openWeapon(WINDOW * WeaponWin, int sel, char category[]){
    // if (sel==0) inserisci spade
    // else if (sel==1) inserisci archi
    // else if (sel==2) inserisci bacchette
    // else if (sel==3) inserisci scudi
    // else if (sel==4) inserisci consumabili

    int wXmax, wYmax;
    getmaxyx(WeaponWin, wYmax, wXmax);

    // n quante armi sono nella lista + 1 (per annulla)
    int n = 1;
    //string oggetti[n] = {"o1", "o2", "o3", "o4", "annulla"};
    int choice;
    int highlights = 0;

    Inventory * inv = current_game.getInventory();

    pitemlist cat = NULL;
    for(pitemlist q = allItems; q!=NULL; q = q->next) {
        int id = q->val.getId();
        if(id>=sel*10 && id<(sel+1)*10) {
            bool okay = false;
            //if(q->val.upgradesFrom()>0)
                okay = inv->isPossessed(q->val.upgradesFrom());

            if(okay) cat = addItem(cat, q->val), n++;
            
        }
            
    }

    bool open = true;
    while (open){
        box(WeaponWin, 0, 0);

        mvwprintw(WeaponWin, 1, 33, "[%s]", category);

        int i = 0;
        for (pitemlist q = cat; q != NULL; i++, q=q->next){ // costruisco il menu
            if (i == highlights) wattron(WeaponWin, A_REVERSE);
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
                OpenChoiceShop(WeaponWin, Item());
                break;
            default:
                break;
        }
    }
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