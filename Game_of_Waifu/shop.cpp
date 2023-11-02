#include "shop.hpp"

// void buy(){
//     // Controlla se hai abbastanza soldi, se ce li hai te li toglie
// }

// void inspectshop(){
//     // Informazioni su tipo di oggetto, effetto, danni, cure ecc...
// }

// void openchoiceshop(int k, string obj[]){
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
// }

void openWeapon(WINDOW * WeaponWin, int n){
    // if (n==0) inserisci spade
    // else if (n==1) inserisci archi
    // else if (n==2) inserisci bacchette
    // else if (n==3) inserisci scudi
    // else if (n==4) inserisci consumabili
}

void open_shop(WINDOW * shopWin){
    int syMax, sxMax;

    box(shopWin, 0, 0);
    keypad(shopWin, true);
    nodelay(shopWin, TRUE);

    // n lunghezza shop
    int n = 5;
    int select = 0;
    string oggetti[n] = {"spade", "archi", "bacchette", "scudi", "consumabili"};
    int choice;
    int highlights = 0;

    bool open = true;
    while (open){
        box(shopWin, 0, 0);
        for (int i = 0; i < n; i++){ // costruisco il menu
            if (i == highlights) wattron(shopWin, A_REVERSE);
            mvwprintw(shopWin, i+1, 2, "%s", oggetti[i].c_str());
            wattroff(shopWin, A_REVERSE);
        }
        choice = wgetch(shopWin);

        switch(choice){ // mi muovo nel menu
            case KEY_UP:
                highlights--, select--;
                if (highlights == -1) highlights = 0, select = 0;
                break;
            case KEY_DOWN:
                highlights++, select++;
                if (highlights == n) highlights = n-1, select = n-1;
                break;
            case 'p':
                open = false;
                wclear(shopWin);
                break;
            case 10:
                openWeapon(shopWin, n);
                break;
            default:
                break;
        }
    }
}
