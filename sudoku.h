#include <curses.h>
#include <stdlib.h>
#include <time.h>

void fill_position(int index_x, int index_y, int *position_x, int *position_y);
void print_board(char fields[9][9], WINDOW * field);
void random_grid(char (*fields)[9][9]);
