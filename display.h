#include <curses.h>
#include <stdlib.h>
#include <time.h>

struct Stats{
    int time_started;
    int time_elapes;
    int mistakes;
    int max_mistakes;
    int available_tips;
    // enum "LOW" "MEDIUM" "HARD"
    char difficulty[6];
};

void print_mistakes(WINDOW *, struct Stats);
void fill_position(int index_x, int index_y, int *position_x, int *position_y);
void print_board(char fields[9][9], WINDOW * field);
void random_grid(char (*fields)[9][9]);
void print_game(char fields[9][9], WINDOW * mainwin, WINDOW * board, WINDOW * stats_window, struct Stats stats);
void use_input(int ch, WINDOW * mainwin, WINDOW * board, WINDOW * stats_win);
void refresh_timer(WINDOW * stats_window, int time_started);
void init_color_sceem();
//void debug(WINDOW * stats_window, char message[20]);

