#include "sudoku.h"


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

    // Horizontale Linien
    mvhline(6, 1, ACS_HLINE, 35);
    mvhline(12, 1, ACS_HLINE, 35);

    // Vertikale Linien
    mvvline(1, 12, ACS_VLINE, 17);
    mvvline(1, 24, ACS_VLINE, 17);
}

/**
 * Funktion zur ermittlung der Position der einzelnen Zahlen
 */
void fill_position( int index_x, int index_y, int *position_x, int *position_y){
    *position_x = (4 * (index_x + 1)) - 2;
    *position_y = (2 * (index_y)) + 1;
}

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
    for(row = 0; 0 < 9; ++row){
        for(col = 0; 0 < 9; ++col){
            // Zufällige Zahl zwischen 1-9
            new_field[row][col] = (rand() % 9) + 1;
        }
    }
    fields = &new_field;
}
