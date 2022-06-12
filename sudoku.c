#include <curses.h>
#include "sudoku.h"



int move_up(int *y_player);
int move_down(int *y_player);
int move_left(int *x_player);
int move_right(int *x_player);

/**
 * Füllt das Feld volkommen Random
 */
void random_grid(int (*fields)[9]){
    // Initialisieren des Random-Seeds
    time_t t;
    srand((unsigned) time(&t));

    // neues Feld erschaffen und darüber loopen
    //char new_field[9][9];
    int row, col;
    for(row = 0; row < 9; ++row){
        for(col = 0; col < 9; ++col){
            // Zufällige Zahl zwischen 1-9
            fields[row][col] = (rand() % 9) + 1;
        }
    }
}

void use_input(
        int ch,
        WINDOW * mainwin, WINDOW * board, WINDOW * stats_window,
        int *y_player, int *x_player, struct Stats *stats
        ){
    int success;

    // Das Highlighting an der Selektierten Stelle entfernen
    reverse_position(board, *y_player, *x_player, 0);
    
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
            print_menu(mainwin, stats);
            // board resetten
            print_game(stats->fields, mainwin, board, stats_window, *stats);
            success = 1;
            break;

        case 't':
            //tip
            success = -1;
            break;

        // kriege ich in meinem setup nicht aufgefangen
        case KEY_MOUSE:
            success = 5;


        case KEY_HOME:
        default:
            success = 0;
            break;
    }
    reverse_position(board, *y_player, *x_player, 1);
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

    int index_y, index_x;
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
 *  generieren einer neuen StatsStruct
*/
struct Stats getStats(){
    struct Stats stats;
    stats.mistakes = 0;
    stats.max_mistakes = 3;
    stats.available_tips = 1;
    sprintf(stats.difficulty, "LOW");
    return stats;
}

// TODO Ändert noch nicht die Inputstats ab
void change_difficulty(struct Stats *stats, int val){
    // Von high oder low in die mitte schalten
    if ((strcmp("LOW", stats->difficulty) && val > 0) || (strcmp("HIGH", stats->difficulty) && val < 0)){
            sprintf(stats->difficulty, "MED");
    }
    // Von Medium high oder runterschalten
    if (strcmp("MED", stats->difficulty)){
        if (val < 0)
            sprintf(stats->difficulty, "LOW");
        else if(val > 0)
            sprintf(stats->difficulty, "HIGH");

    }
}
