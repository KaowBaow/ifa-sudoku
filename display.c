#include "display.h"
#include <curses.h>

// Private Funktionen können noch verschoben werden
void print_lines(WINDOW * board, WINDOW * stats_window);
void print_controls(WINDOW * window, int board_height);
void print_stats(WINDOW * stats_window, struct Stats stats);

/**
 * Startet Farbe
 * Definiert verschiedene Color Szenarien
 */
void init_color_sceem(){
    // prüft ob das Terminal die Farbe ändern kann
    if (!(can_change_color() && has_colors())){
        mvaddstr(6, 1, "NOCOLOR");
    }
    start_color();
    // Normal
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    // Good
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
    // Warning
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    // Altert
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
}

/**
 * Funktion zum Aufzeichnen des Boards
 * @input int fields[9][9] Momentan noch ungenutzt
 * @field WINDOW * Das Sudoku Feld
 */
void print_board(char fields[9][9], WINDOW * field){
    int index_y,index_x;
    int position_x, position_y;

    // Loop über alle Felder
    for(index_y = 0; index_y < 9; ++index_y){
        for(index_x = 0; index_x < 9; ++index_x){
            fill_position(index_x, index_y, &position_x, &position_y);

            mvwaddstr(field, position_y, position_x, "0");
            //mvwaddstr(field, position_y, position_x, &fields[index_y][index_x]);
        }
    }
}

/**
 * Funktion zur ermittlung der Position der einzelnen Zahlen
 */
void fill_position( int index_x, int index_y, int *position_x, int *position_y){
    *position_x = (4 * (index_x + 1)) - 2;
    *position_y = (2 * (index_y)) + 1;
}


/**
 * Malt die Linien des Sudokufeldes
 * TODO: hier fehlen noch die Chars für die Knotenpunkte
 */
void print_lines(WINDOW * board, WINDOW * stats_window){
    // Erstellt einen Rahmen um die Input-Fenster
    // 2. und 3. Parameter zur angabe der Rand-Chars
    box(board,0,0);
    box(stats_window, 0, 0);
    // Horizontale Linien
    mvhline(6, 1, ACS_HLINE, 35);
    mvhline(12, 1, ACS_HLINE, 35);

    // Vertikale Linien
    mvvline(1, 12, ACS_VLINE, 17);
    mvvline(1, 24, ACS_VLINE, 17);
}

/**
 * Erstellt Spiel View mit Sudoku Feld und Steuerungserklährung
 */
void print_game(char fields[9][9], WINDOW * mainwin, WINDOW * board, WINDOW * stats_window, struct Stats stats){

    print_lines(board, stats_window);
    print_board(fields, board);
    int board_height = 19;
    print_controls(mainwin, board_height);

    print_stats(stats_window, stats);
}

/**
 * Schreibt ein Feld mit Controls
 */
void print_controls(WINDOW * window,int board_height){
    int first_line = board_height + 1;
    mvwaddstr(window, first_line, 2, "KEYPAD WASD oder Maus zum Auswaehlen der Felder");
    mvwaddstr(window, first_line + 1, 2, "q - abbrechen");
    mvwaddstr(window, first_line + 2, 2, "m - Menu");
    mvwaddstr(window, first_line + 3, 2, "Leertaste - Speichern");
}

void refresh_timer(WINDOW * stats_window, int time_started){
    int time_now = time(NULL);
    int time_elapsed = time_now - time_started;
    int minutes = (int)(time_elapsed / 60);
    int seconds = time_elapsed - (minutes * 60);

    // Wenn der Displaystring beim Umspringen auf eine neue Minute kleiner wird.
    // TODO: alternativ Sekunden immer 2-Stellig darstellen
    if (seconds == 0)
        mvwaddstr(stats_window, 2, 2, "     ");

    // Erstellen und formatieren der anzuzeigenden Zeit
    char timer_display[5];
    sprintf(timer_display, "%d:%d", minutes, seconds);
    mvwaddstr(stats_window, 2, 2, timer_display);
    wrefresh(stats_window);
}

void use_input(int ch, WINDOW * mainwin, WINDOW * board, WINDOW * stats_window){
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
        }
        //mvwaddstr(board, 1, 4, "default");

        // mvwin(board, y, x);
        //wrefresh(board);
        //wrefresh(stats_window);
}

/**
 * Zeigt den Status des Spiels
 */
void print_stats(WINDOW * stats_window, struct Stats stats){
    int h_align = 2;
    mvwaddstr(stats_window, 1, h_align, "Zeit");

    // TODO: muss noch Display_Info implementieren
    refresh_timer(stats_window, stats.time_started);

    mvwaddstr(stats_window, 4, h_align, "Fehler");
    print_mistakes(stats_window, stats);

    wrefresh(stats_window);
}

/**
 * Zeigt, wie viele Fehler bereits gemacht wurden
 * TODO: Farbe funktioniert bis jetzt nicht
 */
void print_mistakes(WINDOW * window, struct Stats stats){
    char str_mistakes[5];
    sprintf(str_mistakes, "%d/%d", stats.mistakes, stats.max_mistakes);


    //getyx()
    
    if(stats.mistakes == 0){
        attron(COLOR_PAIR(2));
    }else if (stats.mistakes >= stats.max_mistakes - 1){
        attron(COLOR_PAIR(4));
    }else{
        attron(COLOR_PAIR(3));
    }
    mvwaddstr(window, 5, 2, str_mistakes);
    //mvprintw(1, 1, "HELLO");
    mvwprintw(window, 1, 1, "HELLO");
    attroff(COLOR_PAIR(2));
}

/*
   hat irgendein Stackoverflow problem
void debug(WINDOW * stats_window, char message[20]){

    int y_position = stats_window->_yoffset;
    sprintf(message, "%d", y_position);
    mvwaddstr(stats_window, y_position, 3, message);
}
*/
