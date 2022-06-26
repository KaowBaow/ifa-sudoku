#include "sudoku.h"


int main(void)
{
    // Initialisierung der einzelnen Fenster
    WINDOW * main_win, * board_win, * stats_win;

    // Bei Error nach sterr schreiben und sicher abbrechen
    if ((main_win = initscr()) == NULL)
    {
        fprintf(stderr, "Fenster konte nicht gestartet werden.\n");
        exit(1);
    }

    // getippte chars tauchen nicht auf dem Bildschirm auf
    noecho();
    // curser unsichtbar machen
    curs_set(0);
    // Farben einstellen
    init_color_sceem();

    // Begrüst den Spieler
    print_welcome_screen();

    // Intialisierung des Gamestates
    struct Stats stats = getStats();

    print_menu(main_win, &stats);

    // Timer starten
    stats.time_started = time(NULL);

    // Größe des Sudokufeldes
    int width = 37, height = 19;

    // Sudoku-Feld     Parent,   Höhe,   Weite, Y Offset, X Offset
    board_win = subwin(main_win, height, width, 0,        0);
    // Mousesupport für board_win Aktivieren TODO funktioniert absolut nicht
    keypad(main_win, TRUE);
    keypad(board_win, TRUE);

    // Status-Fenster rechts neben Feld
    stats_win = subwin(main_win, 13, 9, 0, 38);


    // Starten der Spieldarstellung
    print_game(stats.fields, main_win, board_win, stats_win, stats);


    // Setzt Zeit, wie lange gewartet wird bis getch() -1 zurückgibt
    halfdelay(10); // 10 -> 1 Sekunde

    // Key-Input
    int ch;

    // Startposition des Spielers
    int y_player = 1, x_player = 2;
    // Loop bis zum manuellen Abbruch durch Drücken von 'q'
    while ((ch = getch()) != 'q')
    {
        // Userinput verarbeiten
        use_input(ch, main_win, board_win, stats_win, &y_player, &x_player, &stats);
        // Timer neu schreiben
        print_timer(stats_win, stats.time_started);
    }

    // Beenden des Programms
    delwin(board_win);
    delwin(main_win);
    endwin();
    clear();
    refresh();

    return 0;
}


//bitte kommentar löschen
