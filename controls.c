#include "sudoku.h"
#include <stdlib.h>

// Private Funktionen
int move_up(int *y_player);
int move_down(int *y_player);
int move_left(int *x_player);
int move_right(int *x_player);

int change_field(int index_y, int index_x, int ch, struct Stats *stats);
int char_to_num(int ch);

void use_input(
        int ch,
        WINDOW * main_win, WINDOW * board_win, WINDOW * stats_win,
        int *y_player, int *x_player, struct Stats *stats
        ){
    int success;
    int index_y;
    int index_x;

    // Das Highlighting an der Selektierten Stelle entfernen
    reverse_position(board_win, *y_player, *x_player, 0);
    
    switch(ch){
        // Bewegung in alles Richtungen
        case KEY_UP:
        case 65:
        case 'w':
            success = move_up(y_player);
            break;

        case KEY_DOWN:
        case 66:
        case 's':
            success = move_down(y_player);
            break;

        case KEY_LEFT:
        case 68:
        case 'a':
            success = move_left(x_player);
            break;

        case KEY_RIGHT:
        case 67:
        case 'd':
            success = move_right(x_player);
            break;

        case 'm':
            //menu
            print_menu(main_win, stats);
            // board resetten
            print_game(stats->fields, main_win, board_win, stats_win, *stats);
            success = 1;
            break;

        case 't':
            //tip
            success = -1;
            break;

        // kriege ich in meinem setup nicht aufgefangen
        case KEY_MOUSE:
            success = 5;

        // nicht schön aber selten
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            position_to_index(*y_player, *x_player, &index_y, &index_x);
            success = change_field(index_y, index_x, ch, stats);
            print_board(stats->fields, board_win);
            wrefresh(board_win);
            break;

        case KEY_HOME:
        default:
            success = 0;
            break;
    }
    reverse_position(board_win, *y_player, *x_player, 1);
    refresh();
    //mvwprintw(board, *y_player, *x_player, "P");
    mvprintw(15, 40, "          ");
    mvprintw(16, 40, "          ");
    mvprintw(17, 40, "          ");
    mvprintw(18, 40, "          ");
    mvprintw(20, 40, "          ");
    mvprintw(21, 40, "          ");

    // Bewegung oder Aktion hat funktioniert
    mvprintw(16, 40, "S:%d", success);

    mvprintw(15, 40, "K:%d", ch);
    mvprintw(17, 40, "Y:%d", *y_player);
    mvprintw(18, 40, "X:%d", *x_player);

    //int index_y, index_x;
    position_to_index(*y_player, *x_player, &index_y, &index_x);

    mvprintw(17, 45, "Yi:%d", index_y);
    mvprintw(18, 45, "Xi:%d", index_x);
}

int move_up(int *y_player){
    if (*y_player >= 3){
        *y_player -= 2;
        return 0;
    }else{
        return -1;
    }
}

int move_down(int *y_player){
    if (*y_player <= 15){
        *y_player += 2;
        return 0;
    }else{
        return -1;
    }
}

int move_left(int *x_player){
    if (*x_player >= 6){
        *x_player -= 4;
        return 0;
    }else{
        return -1;
    }
}

int move_right(int *x_player){
    if (*x_player <= 30){
        *x_player += 4;
        return 0;
    }else{
        return -1;
    }
}



/**
 * gibt zurück, welcher menu_choice ausgewählt wurde
 */
int get_choice(struct menu_choice choices[CHOICES]){

    int i;
    for (i = 0; i < CHOICES; i++)
        if (choices[i].highlighted)
            return i;

    return -1;
}

int select_choice(struct menu_choice choices[CHOICES], struct Stats *stats){
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
            // TODO: Funktion zum Laden von Spielständen einbauen
            done = 0;
            break;

        // LVL
        case 2:
            // Hier sollte eigentlich nichts großes passieren
            done = 0;
            break;
        // Schließen
        case 3:
            // clean exit
            exit(0);
            done = 0;
            break;
        default:
            // Error fall sollte eigentlich nicht auftreten
            done = -1;
    }
    return done;
}

/**
 * Ändert ein Feld ab
 */
int change_field(int index_y, int index_x, int ch, struct Stats *stats){
    int val = char_to_num(ch);

    //if (stats->fields[index_x][index_y] == 0){
        // TODO: if correct value
        stats->fields[index_x][index_y] = val;
        // TODO: else stats->mistakes += 1 && return -1
    //}
    
    return 0;
}

/**
 * Konvertiert ein Char-value zu der jeweiligen Nummer
 */
int char_to_num(int ch){
    return ch - 48;
}
