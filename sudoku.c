#include <curses.h>
#include "sudoku.h"



int move_up(int *y_player);
int move_down(int *y_player);
int move_left(int *x_player);
int move_right(int *x_player);

/**
 * Füllt das Feld volkommen Random
 * TODO: Führt bei Benutzen zu einem Segmentation Fault
 */
void random_grid(char (*fields)[9][9]){
    // Initialisieren des Random-Seeds
    time_t t;
    srand((unsigned) time(&t));

    // neues Feld erschaffen und darüber loopen
    char new_field[9][9];
    int row, col;
    for(row = 0; row < 9; ++row){
        for(col = 0; col < 9; ++col){
            // Zufällige Zahl zwischen 1-9
            new_field[row][col] = (rand() % 9) + 1;
        }
    }
    fields = &new_field;
}

void use_input(
        int ch,
        WINDOW * mainwin, WINDOW * board, WINDOW * stats_window,
        int *y_player, int *x_player
        ){
    int success;
    reverse_position(board, *y_player, *x_player, 0);
    
    switch(ch){
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
            success = -1;
            break;

        case 't':
            //tip
            success = -1;
            break;

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
