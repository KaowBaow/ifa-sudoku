#include "sudoku.h"

// Private Funktionen
void fill_fields(struct Stats *stats, int fields[SIZE * SIZE]);

/*
 * Schaut in der Statistik welche schwierigkeitsgrad ausgewählt wurde und sucht ein ensprechendes
 * Sudoku aus
 */
void get_difficulty(struct Stats *stats)
{
    if (strs_equal(stats->difficulty, "LOW")){
        // Leichtes Sudoku
        int fields[SIZE * SIZE] = {
            5, 8, 6, 0, 3, 1, 0, 7, 0,
            2, 0, 7, 8, 6, 0, 5, 1, 3,
            0, 1, 0, 7, 0, 5, 2, 0, 6,
            0, 2, 8, 0, 0, 4, 3, 6, 1,
            6, 0, 4, 9, 1, 3, 7, 2, 0,
            0, 3, 1, 6, 2, 0, 0, 9, 5,
            4, 0, 5, 0, 8, 2, 0, 3, 7,
            1, 7, 0, 4, 9, 6, 8, 0, 2,
            0, 6, 2, 3, 5, 0, 1, 0, 9
        };
        /*
         * Mock zum effizenten testen
        int fields[SIZE * SIZE] = {
            5, 8, 6, 2, 3, 1, 9, 7, 4,
            2, 4, 7, 8, 6, 0, 5, 1, 3,
            3, 1, 9, 7, 4, 5, 2, 8, 6,
            9, 2, 8, 5, 7, 4, 3, 6, 1,
            6, 5, 4, 9, 1, 3, 7, 2, 8,
            7, 3, 1, 6, 2, 8, 4, 9, 5,
            4, 9, 5, 1, 8, 2, 6, 3, 7,
            1, 7, 3, 4, 9, 6, 8, 5, 2,
            8, 6, 2, 3, 5, 7, 1, 0, 9
        };
        */
        fill_fields(stats, fields);
    }else if(strs_equal(stats->difficulty, "MED")){
        int fields[SIZE * SIZE] = {
            3, 0, 0, 5, 0, 0, 9, 0, 8,
            0, 9, 2, 0, 4, 8, 0, 3, 0,
            5, 0, 6, 9, 3, 0, 4, 0, 1,
            0, 3, 1, 0, 9, 7, 5, 6, 0,
            2, 0, 0, 8, 1, 0, 0, 4, 9,
            0, 5, 9, 0, 0, 3, 0, 8, 0,
            9, 0, 0, 6, 0, 1, 7, 0, 3,
            1, 0, 5, 0, 8, 4, 0, 9, 6,
            0, 2, 3, 7, 5, 0, 8, 0, 0
        };
        fill_fields(stats, fields);
    }else if(strs_equal(stats->difficulty, "HIGH")){
        int fields[SIZE * SIZE] = {
            6, 0, 0, 0, 1, 9, 7, 0, 0,
            0, 0, 0, 0, 0, 0, 2, 0, 0,
            0, 0, 0, 0, 0, 0, 3, 1, 9,
            0, 0, 0, 4, 0, 0, 0, 0, 1,
            3, 0, 0, 0, 0, 2, 9, 0, 0,
            0, 0, 0, 0, 8, 5, 0, 2, 0,
            9, 0, 0, 0, 0, 0, 0, 6, 5,
            0, 0, 5, 3, 4, 8, 0, 0, 0,
            8, 0, 7, 0, 0, 0, 0, 0, 0
        };
        fill_fields(stats, fields);
    }else{
        exit(1);
    }
}

/*
 * Beschreibt
 */
void fill_fields(struct Stats *stats, int fields[SIZE * SIZE]){
    int i = 0, y, x;
    for (y = 0; y < SIZE; y++){
        for (x = 0; x < SIZE; x++){
            stats->fields[x][y] = fields[i];
            stats->starting_fields[x][y] = fields[i];
            i++;
        }
    }
}
