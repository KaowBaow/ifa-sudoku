#include "display.h"
#include "sudoku.h"
#include <bits/types.h>
#include <stdio.h>
#include <curses.h>
#include <sys/cdefs.h>


int main(void){
    // Initialisierung der einzelnen fenster
    WINDOW * mainwin, * board, * stats_window;

    // Bei Error nach sterr schreiben und sicher abbrechen
    if ((mainwin = initscr()) == NULL){
        fprintf(stderr, "Fenster konte nicht gestartet werden.\n");
        exit_curses(1);
    }

    init_color_sceem();

    // timer Starten
    time_t time_started, time_now;
    time_started = time(NULL);

    // Intialisierung des Gamestates
    struct Stats stats;
    stats.time_started = time_started;
    stats.max_mistakes = 3;
    stats.mistakes = 0;


    // test set
    char fields[9][9] = {
        {'1', '2', '3', '4', '5', '6', '7', '8', '9'},
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
    
    // Größe des Sudokufeldes
    int width = 37,
        height = 19;
    /**
     * Sudoku-Feld
     * Parent ,Höhe, ,Weite, Y Offset ,X Offset
     */
    board = subwin(mainwin, height, width, 0, 0);
    // keypad aktivieren
    noecho();
    keypad(board, TRUE);

    // Status-Fenster rechts neben Feld
    stats_window = subwin(mainwin, 10, 9, 0, width + 1);


    // Starten der Spieldarstellung
    print_game(fields, mainwin, board, stats_window, stats);


    //refresh();


    // Setzt Zeit, wie Lange gewrtet wird bis getch() -1 zurückgibt
    halfdelay(10);

    // Key-Input
    int ch;
    // Loop bis zum manuellen abbruch
    while ((ch = getch()) != 'q'){
        // Userinput verarbeiten
        use_input(ch, mainwin, board, stats_window);
        refresh_timer(stats_window, time_started);
    }

    // Beenden des Programms
    delwin(board);
    delwin(mainwin);
    endwin();
    refresh();

    return 0;
}

