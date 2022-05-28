#include "sudoku.h"

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
