#include "sudoku.h"
#include <curses.h>
#include <unistd.h>
#include <string.h>

// Private Funktionen
void print_tips(WINDOW * stats_window, struct Stats stats);
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
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
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
void print_board(int fields[9][9], WINDOW * field){
    int index_y,index_x;
    int position_x, position_y;
    char *val;

    // Loop über alle Felder
    for(index_y = 0; index_y < 9; ++index_y){
        for(index_x = 0; index_x < 9; ++index_x){
            //val = fields[index_x][index_y];
            index_to_position(index_y, index_x, &position_y, &position_x);
            sprintf(val, "%d", fields[index_x][index_y]);


            mvwaddstr(field, position_y, position_x, val);
            //mvwaddstr(field, position_y, position_x, &fields[index_y][index_x]);
        }
    }
}

/**
 * Funktion zur ermittlung der Position der einzelnen Zahlen
 */
void index_to_position( int index_y, int index_x, int *position_y, int *position_x){
    *position_x = (4 * (index_x + 1)) - 2;
    *position_y = (2 * (index_y)) + 1;
}
/**
 * Funktion zur ermittlung der Position der einzelnen Zahlen
 */
void position_to_index(int position_y, int position_x, int *index_y, int *index_x){
    *index_y = (position_y - 1) / 2;
    *index_x = (position_x - 2) / 4;
}



/**
 * Malt die Linien des Sudokufeldes
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


    // obere Knotenpunkte
    mvaddch(0,12, ACS_TTEE);
    mvaddch(0,24, ACS_TTEE);

    //knotenpunkte links
    mvaddch(6,0, ACS_LTEE);
    mvaddch(12,0, ACS_LTEE);

    //knotenpunkte rechts
    mvaddch(6,36, ACS_RTEE);
    mvaddch(12,36, ACS_RTEE);

    // untere Knotenpunkte
    mvaddch(18,12, ACS_BTEE);
    mvaddch(18,24, ACS_BTEE);

    // Kreuzungen
    mvaddch(6,12, ACS_PLUS);
    mvaddch(6,24, ACS_PLUS);
    mvaddch(12,12, ACS_PLUS);
    mvaddch(12,24, ACS_PLUS);
}

/**
 * Erstellt Spiel View mit Sudoku Feld und Steuerungserklährung
 */
void print_game(int fields[9][9], WINDOW * mainwin, WINDOW * board, WINDOW * stats_window, struct Stats stats){

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

void refresh_timer(WINDOW *stats_window, int time_started){
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
void print_stats(WINDOW *stats_window, struct Stats stats){
    int h_align = 2;
    mvwaddstr(stats_window, 1, h_align, "Zeit");

    refresh_timer(stats_window, stats.time_started);

    mvwaddstr(stats_window, 4, h_align, "Fehler");
    print_mistakes(stats_window, stats);


    mvwaddstr(stats_window, 7, h_align, "Tips");

    print_tips(stats_window, stats);
    //wrefresh(stats_window);
}

/**
 * Zeigt, wie viele Fehler bereits gemacht wurden
 * TODO: Farbe funktioniert bis jetzt nicht
 * Im Board funktioniert sie...
 */
void print_mistakes(WINDOW *window, struct Stats stats){
    // Formatiert den zu zeigenden Status
    char str_mistakes[22];
    sprintf(str_mistakes, "%d/%d", stats.mistakes, stats.max_mistakes);


    //getyx()
    
    if(stats.mistakes == 0){
        attron(COLOR_PAIR(2));
    }else if (stats.mistakes >= stats.max_mistakes - 1){
        attron(COLOR_PAIR(4));
    }else{
        attron(COLOR_PAIR(3));
    }
    
    int beg_y, beg_x, 
        offset_y = 5,
        offset_x = 3;

    getbegyx(window, beg_y,beg_x);
    mvprintw(beg_y + offset_y, beg_x + offset_x, "%s", str_mistakes);
    attroff(COLOR_PAIR(2));
}

void print_tips(WINDOW *window, struct Stats stats){
    mvwprintw(window, 8, 4, "%d", stats.available_tips);
}

/**
 * Stellt das ausgewählte Feld auf negativ
 */
void reverse_position(WINDOW *window, int y_position, int x_position, int direction){
    int ch;
    ch = mvinch(y_position, x_position);
    if (direction == 1){
        attron(A_REVERSE);
    }
    mvprintw(y_position, x_position, "%c", ch);
    attroff(A_REVERSE);
}

void welcome_screen(){
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

struct menu_choice{
    char display[12];
    int highlighted;
};


/**
 * gibt zurück, welcher menu_choice ausgewählt wurde
 */
int get_choice(struct menu_choice choices[4]){

    int i;
    for (i = 0; i < 4; i++)
        if (choices[i].highlighted)
            return i;

    return -1;
}

int select_choice(struct menu_choice choices[4], struct Stats *stats){
    // Welcher Menu-Index wurde selected ?
    int selected = get_choice(choices);
    
    int done = 0;
    switch(selected){
        // Start
        case 0:
            // Normaler starten in ein neues Spiel
            random_grid(stats->fields);
            done = 1;
            break;
        // Laden
        case 1:
            done = 0;
            break;

        // LVL
        case 2:
            done = 0;
            break;
        // Schließen
        case 3:
            done = 0;
            break;
        default:
            done = -1;
    }
    return done;
}


/**
 * Darstellung der Menuoptionen
 */
void print_options(WINDOW *win, struct Stats *stats){
    keypad(win, TRUE);
    // ein array aus menu choices
    struct menu_choice choices[4] ={
        {"Start", 1},
        {"Laden", 0},
        {"LVL", 0},
        {"Schliessen", 0},
    };


    int done = 0;
    // input
    int ch = -1;
    // y_pos des loops
    int y_pos;
    // Array iterator
    int i;
    // curser Position
    int c_pos = 0;
    do{
        for (i = 0; i < 4; i++){
            y_pos = 2 + (2 * i);
            if (choices[i].highlighted)
                wattron(win, A_REVERSE);

            mvwaddstr(win, y_pos, 5, choices[i].display);
            wattroff(win, A_REVERSE);
        }
        mvwprintw(win, 10, 5, "%d", c_pos);
        mvwprintw(win, 12, 5, "%d", ch);
        mvwprintw(win, 14, 5, "%d", done);

        // auf input warten
        ch = getch();
        refresh();

        switch(ch){
            //case 65:
            //case KEY_UP:
            case 'w':
                // highlight entfernen
                choices[c_pos].highlighted = 0;
                if (c_pos > 0){
                    c_pos--;
                }
                break;
            //case 64:
            //case 79:
            //case KEY_DOWN:
            //case 27:
            case 's':
                // highlight entfernen
                choices[c_pos].highlighted = 0;
                if (c_pos < 3){
                    c_pos++;
                }
                break;

            case 'a':
                change_difficulty(stats, -1);
                break;
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

        choices[c_pos].highlighted = 1;

        clear();
        // Vorläufiger breakout
        if (done)
            break;

    } while(1);

}


void print_menu(WINDOW * main_win, struct Stats *stats){
    WINDOW *menu_win;
    menu_win = subwin(main_win, 19, 37, 0, 0);

    box(menu_win,0,0);
    // Options loop
    print_options(menu_win, stats);

    mvwaddstr(main_win, 5, 5, "TEST");
    refresh();
    
    clear();
}
