#include "sudoku.h"

int strs_equal(char *str1, char *str2);

// Private Funktionen
void print_tips(WINDOW * stats_window, struct Stats stats);
void print_lines(WINDOW * board, WINDOW * stats_window);
void print_controls(WINDOW * window, int board_height);
void print_stats(WINDOW * stats_window, struct Stats stats);
void print_mistakes(WINDOW *win, struct Stats);
void print_difficulty(WINDOW* stats_win, char difficulty[6]);

/**
 * Startet Farbe
 * Definiert verschiedene Color Szenarien
 */
void init_color_sceem()
{
    // prüft ob das Terminal die Farbe ändern kann
    if (!(can_change_color() && has_colors()))
    {
        mvaddstr(6, 1, "NOCOLOR");
    }
    start_color();
    // Normal
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    // Good
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    // Warning
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    // Altert
    init_pair(4, COLOR_RED, COLOR_BLACK);
}


/**
 * Funktion zum Aufzeichnen des Boards
 * @input int fields[9][9] Momentan noch ungenutzt
 * @field WINDOW * Das Sudoku Feld
 */
void print_board(int fields[9][9], WINDOW * field)
{
    int index_y,index_x;
    int position_x, position_y;
    char *val;

    // Loop über alle Felder
    for(index_y = 0; index_y < 9; ++index_y)
    {
        for(index_x = 0; index_x < 9; ++index_x)
        {
            //val = fields[index_x][index_y];
            index_to_position(index_y, index_x, &position_y, &position_x);
            sprintf(val, "%d", fields[index_x][index_y]);


            mvwaddstr(field, position_y, position_x, val);
            //mvwaddstr(field, position_y, position_x, &fields[index_y][index_x]);
        }
    }
}

/**
 * Funktion zur Ermittlung der Position der einzelnen Zahlen
 */
void index_to_position( int index_y, int index_x, int *position_y, int *position_x)
{
    *position_x = (4 * (index_x + 1)) - 2;
    *position_y = (2 * (index_y)) + 1;
}

/**
 * Funktion zur Ermittlung der Position der einzelnen Zahlen
 */
void position_to_index(int position_y, int position_x, int *index_y, int *index_x)
{
    *index_y = (position_y - 1) / 2;
    *index_x = (position_x - 2) / 4;
}

/**
 * Malt die Linien des Sudokufeldes
 */
void print_lines(WINDOW * board_win, WINDOW * stats_win)
{
    // Erstellt einen Rahmen um die Input-Fenster
    // 2. und 3. Parameter zur angabe der Rand-Chars
    box(board_win,0,0);
    box(stats_win, 0, 0);
    // Horizontale Linien
    mvwhline(board_win, 6, 1, ACS_HLINE, 35);
    mvwhline(board_win, 12, 1, ACS_HLINE, 35);

    // Vertikale Linien
    mvwvline(board_win, 1, 12, ACS_VLINE, 17);
    mvwvline(board_win, 1, 24, ACS_VLINE, 17);



    // Knotenpunkte oben
    mvwaddch(board_win, 0, 12, ACS_TTEE);
    mvwaddch(board_win, 0, 24, ACS_TTEE);

    // Knotenpunkte links
    mvwaddch(board_win, 6, 0, ACS_LTEE);
    mvwaddch(board_win, 12, 0, ACS_LTEE);

    // Knotenpunkte rechts
    mvwaddch(board_win, 6, 36, ACS_RTEE);
    mvwaddch(board_win, 12, 36, ACS_RTEE);

    // Knotenpunkte unten
    mvwaddch(board_win, 18, 12, ACS_BTEE);
    mvwaddch(board_win, 18, 24, ACS_BTEE);

    // Kreuzungen
    mvwaddch(board_win, 6, 12, ACS_PLUS);
    mvwaddch(board_win, 6, 24, ACS_PLUS);
    mvwaddch(board_win, 12, 12, ACS_PLUS);
    mvwaddch(board_win, 12, 24, ACS_PLUS);
}

/**
 * Erstellt Spiel View mit Sudoku Feld und Steuerungserklährung
 */
void print_game(int fields[9][9], WINDOW * mainwin, WINDOW * board, WINDOW * stats_window, struct Stats stats)
{

    print_lines(board, stats_window);
    print_board(fields, board);
    print_controls(mainwin, 19);

    print_stats(stats_window, stats);
}

/**
 * Schreibt ein Feld mit Controls
 */
void print_controls(WINDOW * window,int board_height)
{
    int first_line = board_height + 1;
    mvwaddstr(window, first_line, 2, "KEYPAD WASD oder Maus zum Auswaehlen der Felder");
    mvwaddstr(window, first_line + 1, 2, "q - abbrechen");
    mvwaddstr(window, first_line + 2, 2, "m - Menu");
    mvwaddstr(window, first_line + 3, 2, "Leertaste - Speichern");
}

void print_timer(WINDOW *stats_window, int time_started)
{
    int time_now = time(NULL);
    int time_elapsed = time_now - time_started;
    int minutes = (int)(time_elapsed / 60);
    int seconds = time_elapsed - (minutes * 60);

    // Wenn der Displaystring beim Umspringen auf eine neue Minute kleiner wird.
    // TODO: alternativ Sekunden immer 2-Stellig darstellen
    if (seconds == 0)
        mvwaddstr(stats_window, 2, 2, "     ");

    // Erstellen und formatieren der anzuzeigenden Zeit
    char timer_display[22];
    sprintf(timer_display, "%d:%d", minutes, seconds);
    mvwaddstr(stats_window, 2, 2, timer_display);
    wrefresh(stats_window);
}

/**
 * Zeigt den Status des Spiels
 * Refresht alle Module des Status Fensters
 */
void print_stats(WINDOW *stats_window, struct Stats stats)
{
    int h_align = 2;
    mvwaddstr(stats_window, 1, h_align, "Zeit");
    print_timer(stats_window, stats.time_started);

    mvwaddstr(stats_window, 4, h_align, "Fehler");
    print_mistakes(stats_window, stats);

    mvwaddstr(stats_window, 7, h_align, "Tips");
    print_tips(stats_window, stats);

    mvwaddstr(stats_window, 10, h_align, "LVL");
    print_difficulty(stats_window, stats.difficulty);
}

/**
 * Zeigt, wie viele Fehler bereits gemacht wurden
 * TODO: Farbe funktioniert bis jetzt nicht
 * Im Board funktioniert sie...
 */
void print_mistakes(WINDOW *window, struct Stats stats)
{
    // Formatiert den zuzeigenden Status
    char str_mistakes[22];
    sprintf(str_mistakes, "%d/%d", stats.mistakes, stats.max_mistakes);

    // noch keine Fehler
    if(stats.mistakes == 0)
    {
        wattron(window, COLOR_PAIR(2)); // grün

        // noch mehr als ein Fehler übrig
    }
    else if (stats.mistakes >= stats.max_mistakes - 1)
    {
        wattron(window, COLOR_PAIR(4)); // gelb

        // gleich vorbei
    }
    else
    {
        wattron(window, COLOR_PAIR(3)); // rot
    }

    int offset_y = 5,
        offset_x = 2;

    // Tatsächliches schreiben der Fehler
    mvwprintw(window, offset_y, offset_x, "%s", str_mistakes);
    // wieder auf normale Farbe schalten
    wattroff(window, COLOR_PAIR(2));
    wattroff(window, COLOR_PAIR(3));
    wattroff(window, COLOR_PAIR(4));
}

void print_tips(WINDOW *window, struct Stats stats)
{
    mvwprintw(window, 8, 2, "%d", stats.available_tips);
}

/**
 * Stellt das ausgewählte Feld auf negativ
 */
void reverse_position(WINDOW *window, int y_position, int x_position, int direction)
{
    int ch;
    ch = mvinch(y_position, x_position);
    if (direction == 1)
    {
        attron(A_REVERSE);
    }
    mvprintw(y_position, x_position, "%c", ch);
    attroff(A_REVERSE);
}

void print_welcome_screen()
{
    mvprintw(1, 3," _____           _       _          \n");
    mvprintw(2, 3,"/  ___|         | |     | |         \n");
    mvprintw(3, 3,"\\ `--. _   _  __| | ___ | | ___   _ \n");
    mvprintw(4, 3," `--. \\ | | |/ _` |/ _ \\| |/ / | | |\n");
    mvprintw(5, 3,"/\\__/ / |_| | (_| | (_) |   <| |_| |\n");
    mvprintw(6, 3,"\\____/ \\__,_|\\__,_|\\___/|_|\\_\\\\__,_|");
    mvprintw(8, 7, " Beliebige Taste druecken");
    getch();
    clear();
    //refresh();
}


/**
 * Darstellung der Menuoptionen
 * TODO: Sollte es noch mehr Choices geben?
 */
void print_options(WINDOW *win, struct Stats *stats)
{
    keypad(win, TRUE);
    // ein Array aus menu choices
    // ein Array aus menu choices
    struct menu_choice choices[CHOICES] =
    {
        {"Start", 1},
        {"Laden", 0},
        {"LVL", 0},
        {"Schliessen", 0},
    };

    // breakout
    int done = 0;
    // input
    int ch = -1;
    // y_pos des loops
    int y_pos;
    // Array iterator
    int i;
    // curser Position zwischen 0 und choices len -1
    int c_pos = 0;
    do
    {
        box(win, 0, 0);
        for (i = 0; i < CHOICES; i++)
        {
            y_pos = 2 + (2 * i);
            if (choices[i].highlighted)
                wattron(win, A_REVERSE);

            mvwaddstr(win, y_pos, 5, choices[i].display);

            // Bei lvl muss der Schwierigkeitsgrad hinter
            if (strs_equal(choices[i].display, "LVL"))
                mvwaddstr(win, y_pos, 9, stats->difficulty);

            wattroff(win, A_REVERSE);
        }
        mvwprintw(win, 10, 5, "%d", c_pos);
        mvwprintw(win, 12, 5, "%d", ch);
        mvwprintw(win, 14, 5, "%d", done);

        // auf input warten
        ch = getch();
        refresh();

        switch(ch)
        {
        //case 65:
        //case KEY_UP:
        case 'w':
            // highlight entfernen
            choices[c_pos].highlighted = 0;
            if (c_pos > 0)
            {
                c_pos--;
            }
            break;
        case 's':
            // highlight entfernen
            choices[c_pos].highlighted = 0;
            if (c_pos < CHOICES - 1)
            {
                c_pos++;
            }
            break;

        // Schwierigkeit runter
        case 'a':
            change_difficulty(stats, -1);
            break;
        // Schwierigkeit hoch
        case 'd':
            change_difficulty(stats, 1);
            break;

        case 'q':
            done = 1;
            break;

        case KEY_ENTER:
        case 10:
            // TODO ändert nichts ab
            done = select_choice(choices, stats);

        }

        // Aktuelle Position makieren
        choices[c_pos].highlighted = 1;

        clear();

    }
    while(done != 1);

}


/**
 * Darstellung des Menus
 */
void print_menu(WINDOW * main_win, struct Stats *stats)
{
    WINDOW *menu_win;
    menu_win = subwin(main_win, 19, 37, 0, 0);

    // Options loop
    print_options(menu_win, stats);

    mvwaddstr(main_win, 5, 5, "TEST");
    refresh();

    clear();
}

void print_difficulty(WINDOW* stats_win, char difficulty[6])
{
    if (strs_equal(difficulty, "LOW"))
        wattron(stats_win, COLOR_PAIR(2));

    else if (strs_equal(difficulty, "MED"))
        wattron(stats_win, COLOR_PAIR(3));

    else if (strs_equal(difficulty, "HIGH"))
        wattron(stats_win, COLOR_PAIR(4));

    mvwaddstr(stats_win, 11, 2, difficulty);

    wattroff(stats_win, COLOR_PAIR(2));
    wattroff(stats_win, COLOR_PAIR(3));
    wattroff(stats_win, COLOR_PAIR(4));
}
