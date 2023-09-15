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

void openchoice(int k, string obj[]){
    int syMax, sxMax;
    getmaxyx(stdscr, syMax, sxMax);
    WINDOW *choiceWin = newwin(syMax-(syMax/10)-2, sxMax-(sxMax/10)-2, syMax/20+2, sxMax/20+1);
    box(choiceWin, 0, 0);
    keypad(choiceWin, true);
    nodelay(choiceWin, TRUE);

    mvwprintw(choiceWin, 1, 2, "Hai selezionato: %s", obj[k]);

    int n = 4;
    string azioni[n] = {"equipaggia", "ispeziona", "vendi", "annulla"};
    int highlights = 0, select = 0, choice;

    bool open = true;
    while(open){
        for (int i = 0; i < n; i++){ // costruisco il menu
            if (i == highlights) wattron(choiceWin, A_REVERSE);
            mvwprintw(choiceWin, i+3, 2, "%s", azioni[i].c_str());
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
                break;
            default:
                break;
        }
        if (choice == 10){ // quando premo invio
            if (select == 0) equip();
            else if (select == 1) inspect();
            else if (select == 2) sell();
            break;
        }
    }
}

void open_inventory(){
    int syMax, sxMax;
    getmaxyx(stdscr, syMax, sxMax);

    WINDOW *invWin = newwin(syMax-(syMax/10)-2, sxMax-(sxMax/10)-2, syMax/20+2, sxMax/20+1);
    box(invWin, 0, 0);
    keypad(invWin, true);
    nodelay(invWin, TRUE);
    int inyMax, inxMax;
    getmaxyx(invWin, inyMax, inxMax);

    // gli oggetti nell'inventario saranno una lista, n la lunghezza della lista
    int n = 4;
    int select = 0;
    string oggetti[n] = {"spada lunga", "scudo di doran", "palle potenti", "freccia"};
    int choice;
    int highlights = 0;

    bool open = true;
    while (open){
        for (int i = 0; i < n; i++){ // costruisco il menu
            if (i == highlights) wattron(invWin, A_REVERSE);
            mvwprintw(invWin, i+1, 2, "%s", oggetti[i].c_str());
            wattroff(invWin, A_REVERSE);
        }
        choice = wgetch(invWin);

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
                break;
            default:
                break;
        }
        
        if (choice == 10){ // quando premo invio
            openchoice(select, oggetti);
            break;
        }
    }
}