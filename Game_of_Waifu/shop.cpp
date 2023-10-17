#include "shop.hpp"

void buy(){
    // Controlla se hai abbastanza soldi, se ce li hai te li toglie
}

void inspectshop(){
    // Informazioni su tipo di oggetto, effetto, danni, cure ecc...
}

void openchoiceshop(int k, string obj[]){
    int syMax, sxMax;
    getmaxyx(stdscr, syMax, sxMax);
    WINDOW *choiceWin = newwin(syMax-(syMax/10)-2, sxMax-(sxMax/10)-2, syMax/20+2, sxMax/20+1);
    box(choiceWin, 0, 0);
    keypad(choiceWin, true);
    nodelay(choiceWin, TRUE);

    mvwprintw(choiceWin, 1, 2, "Hai selezionato: %s", obj[k]);

    int n = 3;
    string azioni[n] = {"compra", "ispeziona", "annulla"};
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
            case 'p':
                open = false;
                break;
            default:
                break;
        }
        if (choice == 10){ // quando premo invio
            if (select == 0) buy();
            else if (select == 1) inspectshop();
            break;
        }
    }
}

void openspade(){
    int syMax, sxMax;
    getmaxyx(stdscr, syMax, sxMax);

    WINDOW *shopWin = newwin(syMax-(syMax/10)-2, sxMax-(sxMax/10)-2, syMax/20+2, sxMax/20+1);
    box(shopWin, 0, 0);
    keypad(shopWin, true);
    nodelay(shopWin, TRUE);
    int inyMax, inxMax;
    getmaxyx(shopWin, inyMax, inxMax);

    // n lunghezza lista di spade
    int n = 4;
    int select = 0;
    string oggetti[n] = {"spada1", "spada2", "spada3", "back"};
    int choice;
    int highlights = 0;

    bool open = true;
    while (open){
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
                break;
            default:
                break;
        }
        
        if (choice == 10){ // quando premo invio
            if(select == n-1){open_shop(); break;} 
            openchoiceshop(select, oggetti);
            break;
        }
    }
}

void openarchi(){
    int syMax, sxMax;
    getmaxyx(stdscr, syMax, sxMax);

    WINDOW *shopWin = newwin(syMax-(syMax/10)-2, sxMax-(sxMax/10)-2, syMax/20+2, sxMax/20+1);
    box(shopWin, 0, 0);
    keypad(shopWin, true);
    nodelay(shopWin, TRUE);
    int inyMax, inxMax;
    getmaxyx(shopWin, inyMax, inxMax);

    // n lunghezza lista di spade
    int n = 4;
    int select = 0;
    string oggetti[n] = {"a1", "a2", "a3", "back"};
    int choice;
    int highlights = 0;

    bool open = true;
    while (open){
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
                break;
            default:
                break;
        }
        
        if (choice == 10){ // quando premo invio
            if(select == n-1){open_shop(); break;} 
            openchoiceshop(select, oggetti);
            break;
        }
    }
}

void openbacchette(){
    int syMax, sxMax;
    getmaxyx(stdscr, syMax, sxMax);

    WINDOW *shopWin = newwin(syMax-(syMax/10)-2, sxMax-(sxMax/10)-2, syMax/20+2, sxMax/20+1);
    box(shopWin, 0, 0);
    keypad(shopWin, true);
    nodelay(shopWin, TRUE);
    int inyMax, inxMax;
    getmaxyx(shopWin, inyMax, inxMax);

    // n lunghezza lista di spade
    int n = 4;
    int select = 0;
    string oggetti[n] = {"b1", "b2", "b3", "back"};
    int choice;
    int highlights = 0;

    bool open = true;
    while (open){
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
                break;
            default:
                break;
        }
        
        if (choice == 10){ // quando premo invio
            if(select == n-1){open_shop(); break;} 
            openchoiceshop(select, oggetti);
            break;
        }
    }
}

void openscudi(){
    int syMax, sxMax;
    getmaxyx(stdscr, syMax, sxMax);

    WINDOW *shopWin = newwin(syMax-(syMax/10)-2, sxMax-(sxMax/10)-2, syMax/20+2, sxMax/20+1);
    box(shopWin, 0, 0);
    keypad(shopWin, true);
    nodelay(shopWin, TRUE);
    int inyMax, inxMax;
    getmaxyx(shopWin, inyMax, inxMax);

    // n lunghezza lista di spade
    int n = 4;
    int select = 0;
    string oggetti[n] = {"sc1", "sc2", "sc3", "back"};
    int choice;
    int highlights = 0;

    bool open = true;
    while (open){
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
                break;
            default:
                break;
        }
        
        if (choice == 10){ // quando premo invio
            if(select == n-1){open_shop(); break;} 
            openchoiceshop(select, oggetti);
            break;
        }
    }
}

void openconsumabili(){
    int syMax, sxMax;
    getmaxyx(stdscr, syMax, sxMax);

    WINDOW *shopWin = newwin(syMax-(syMax/10)-2, sxMax-(sxMax/10)-2, syMax/20+2, sxMax/20+1);
    box(shopWin, 0, 0);
    keypad(shopWin, true);
    nodelay(shopWin, TRUE);
    int inyMax, inxMax;
    getmaxyx(shopWin, inyMax, inxMax);

    // n lunghezza lista di spade
    int n = 4;
    int select = 0;
    string oggetti[n] = {"c1", "c2", "c3", "back"};
    int choice;
    int highlights = 0;

    bool open = true;
    while (open){
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
                break;
            default:
                break;
        }
        
        if (choice == 10){ // quando premo invio
            if(select == n-1){open_shop(); break;} 
            openchoiceshop(select, oggetti);
            break;
        }
    }
}

void open_shop(){
    int syMax, sxMax;
    getmaxyx(stdscr, syMax, sxMax);

    WINDOW *shopWin = newwin(syMax-(syMax/10)-2, sxMax-(sxMax/10)-2, syMax/20+2, sxMax/20+1);
    box(shopWin, 0, 0);
    keypad(shopWin, true);
    nodelay(shopWin, TRUE);
    int inyMax, inxMax;
    getmaxyx(shopWin, inyMax, inxMax);

    // n lunghezza shop
    int n = 5;
    int select = 0;
    string oggetti[n] = {"spade", "archi", "bacchette", "scudi", "consumabili"};
    int choice;
    int highlights = 0;

    bool open = true;
    while (open){
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
                break;
            default:
                break;
        }
        
        if (choice == 10){ // quando premo invio
            if (select == 0) openspade();
            else if (select == 1) openarchi();
            else if (select == 2) openbacchette();
            else if (select == 3) openscudi();
            else if (select == 4) openconsumabili();
            break;
        }
    }
}