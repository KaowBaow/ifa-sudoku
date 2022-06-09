#include <bits/types.h>
#include <stdio.h>
#include <curses.h>
#include <sys/cdefs.h>
#include <time.h>
#include <unistd.h>
#include "sudoku.h"


int main(void){
    // Initialisierung der einzelnen fenster
    WINDOW * mainwin, * board, * stats_window;

    // Bei Error nach sterr schreiben und sicher abbrechen
    if ((mainwin = initscr()) == NULL){
        fprintf(stderr, "Fenster konte nicht gestartet werden.\n");
        exit_curses(1);
    }
    //init_color_sceem();
    //printw("\n _____           _       _          \n/  ___|         | |     | |         \n\\ `--. _   _  __| | ___ | | ___   _ \n`--. \\ | | |/ _` |/ _ \\| |/ / | | |\n/\\__/ / |_| | (_| | (_) |   <| |_| |\n\\____/ \\__,_|\\__,_|\\___/|_|\\_\\__,_|");
    //refresh();
    //sleep(5);



    // timer Starten
    time_t time_started, time_now;
    time_started = time(NULL);


    // Intialisierung des Gamestates
    struct Stats stats = getStats();
    stats.time_started = time_started;


    // test set
    /**
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
    */
    char fields[9][9];
    random_grid(&fields);
    
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
    curs_set(0);
    //keypad(board, TRUE);

    // Status-Fenster rechts neben Feld
    stats_window = subwin(mainwin, 10, 9, 0, width + 1);
    init_color_sceem();


    // Starten der Spieldarstellung
    print_game(fields, mainwin, board, stats_window, stats);


    //refresh();



    // Setzt Zeit, wie Lange gewrtet wird bis getch() -1 zurückgibt
    halfdelay(10);

    // Key-Input
    int ch, y_curs, x_curs;
    int y_player = 1;
    int x_player = 2;
    // Loop bis zum manuellen abbruch
    while ((ch = getch()) != 'q'){
        // Etabliert pointer zu Koordinaten
        getyx(mainwin, y_curs, x_curs);
        // Abspeichern der Position
        // Userinput verarbeiten
        use_input(ch, mainwin, board, stats_window, &y_player, &x_player);
        refresh_timer(stats_window, time_started);

    }

    // Beenden des Programms
    delwin(board);
    delwin(mainwin);
    endwin();
    refresh();
    sleep(5);
    clear();

    return 0;
}

