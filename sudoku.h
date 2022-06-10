#include <time.h>
#include <stdlib.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Stats{
    int time_started;
    int time_elapes;
    int mistakes;
    int available_tips;
    // enum "LOW" "MEDIUM" "HARD"
    char difficulty[6];
    int max_mistakes;
};

void random_grid(int (*fields)[9]);
struct Stats getStats();


void index_to_position( int index_y, int index_x, int *position_y, int *position_x);
void position_to_index(int position_y, int position_x, int *index_y, int *index_x);
void print_mistakes(WINDOW *, struct Stats);
void print_board(int fields[9][9], WINDOW * field);
void print_game(int fields[9][9], WINDOW * mainwin, WINDOW * board, WINDOW * stats_window, struct Stats stats);
void use_input(int ch, WINDOW * mainwin, WINDOW * board, WINDOW * stats_win, int *y_player, int * x_player);
void refresh_timer(WINDOW * stats_window, int time_started);
void init_color_sceem();
void reverse_position(WINDOW *window, int y_position, int x_position, int direction);
//void debug(WINDOW * stats_window, char message[20]);
