#include "sudoku.h"
#include <bits/types.h>
#include <stdio.h>
#include <curses.h>
#include <sys/cdefs.h>


int main(void){
    // Initialisierung der einzelnen fenster
    WINDOW * mainwin, * childwin;
    int ch;


    // Randparameter definieren
    int width = 37,
        height = 19,
        rows = 25,
        cols = 80;

    //int x = (cols - width) / 2;
    //int y = (rows - height) / 2;

    // Bei Error nach sterr schreiben und sicher abbrechen
    if ((mainwin = initscr()) == NULL){
        fprintf(stderr, "Error initialising ncurses.\n");
        exit_curses(1);
    }


    // neues untergeortnetes Fenster
    childwin = subwin(mainwin, height, width, 0, 0);
    box(childwin,0,0);
    // keypad aktivieren
    noecho();
    keypad(mainwin, TRUE);

    char fields[9][9] = {
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'1', '2', '3', '4', '5', '6', '7', '8', '9'},
        {'1', '2', '3', '4', '5', '6', '7', '8', '9'},
        {'1', '2', '3', '4', '5', '6', '7', '8', '9'},
        {'1', '2', '3', '4', '5', '6', '7', '8', '9'},
        {'1', '2', '3', '4', '5', '6', '7', '8', '9'},
        {'1', '2', '3', '4', '5', '6', '7', '8', '9'},
        {'1', '2', '3', '4', '5', '6', '7', '8', '9'},
        {'1', '2', '3', '4', '5', '6', '7', '8', '9'},
    };
    //random_grid(&fields);


    print_board(fields, childwin);

    refresh();

    // Loop bis zum manuellen abbruch
    while ((ch = getch()) != 'q'){
        switch(ch){
            case KEY_UP:
                //if (y>0)
                //    --y;
                break;
            case KEY_DOWN:
                //if (y < (rows - height))
                //    ++y;
                break;
            case KEY_LEFT:
                //if (x > 0)
                //    --x;
                break;
            case KEY_RIGHT:
                //if (x < (cols - width))
                //    ++x;
                break;
            case KEY_HOME:
                //x = 0;
                //y = 0;
                break;
            default:
                mvwaddstr(childwin, 1, 4, "default");

        }
        // mvwin(childwin, y, x);
        wrefresh(childwin);
    }

    // Beenden des Programms
    delwin(childwin);
    delwin(mainwin);
    endwin();
    refresh();

    return 0;
}
