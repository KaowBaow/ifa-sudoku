#include <bits/types.h>
#include <stdio.h>
#include <curses.h>
#include <sys/cdefs.h>
#include <time.h>
#include <unistd.h>
#include "sudoku.h"


int main(void)
{
    // Initialisierung der einzelnen fenster
    WINDOW * mainwin, * board, * stats_window, * menu_win;

    // Bei Error nach sterr schreiben und sicher abbrechen
    if ((mainwin = initscr()) == NULL)
    {
        fprintf(stderr, "Fenster konte nicht gestartet werden.\n");
        exit_curses(1);
    }

    // getippte chars tauchen nicht auf dem Bildschirm auf
    noecho();
    // curser unsichtbar machen
    curs_set(0);
    // würde ich gerne in welcome_screen auslagern ist dann aber buggy
    init_color_sceem();

    // Begrüst den Spieler
    welcome_screen();

    // Intialisierung des Gamestates
    struct Stats stats = getStats();
    stats.time_started = time(NULL);

    print_menu(mainwin, &stats);

    // Größe des Sudokufeldes
    int width = 37, height = 19;

    // Sudoku-Feld
    // Parent,  Höhe,   Weite, Y Offset, X Offset
    board = subwin(mainwin, height, width, 0,        0);
    // Mousesupport für board Aktivieren TODO funktioniert absolut nicht
    keypad(mainwin, TRUE);
    keypad(board, TRUE);
    //keypad(stats_window, TRUE);


    // Status-Fenster rechts neben Feld
    stats_window = subwin(mainwin, 13, 9, 0, board->_maxx + 2);
    //init_color_sceem();


    // Starten der Spieldarstellung
    print_game(stats.fields, mainwin, board, stats_window, stats);


    // Setzt Zeit, wie Lange gewrtet wird bis getch() -1 zurückgibt
    halfdelay(10);

    // Key-Input
    int ch, y_curs, x_curs;
    int y_player = 1;
    int x_player = 2;
    // Loop bis zum manuellen abbruch
    while ((ch = getch()) != 'q')
    {
        // Etabliert pointer zu Koordinaten
        getyx(mainwin, y_curs, x_curs);
        // Abspeichern der Position
        // Userinput verarbeiten
        use_input(ch, mainwin, board, stats_window, &y_player, &x_player, &stats);
        refresh_timer(stats_window, stats.time_started);
    }

    // Beenden des Programms
    delwin(board);
    delwin(mainwin);
    endwin();
    clear();
    refresh();

    return 0;
}
