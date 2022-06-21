#include "sudoku.h"


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
