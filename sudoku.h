#include <time.h>
#include <stdlib.h>
#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Stats{
    time_t time_started;
    time_t time_elapes;
    int mistakes;
    int max_mistakes;
    int available_tips;
    // enum "LOW" "MED" "HARD"
    char difficulty[6];
    int fields[9][9];
};

void random_grid(int (*fields)[9]);
struct Stats getStats();


int strs_equal(char *str1, char *str2);


void use_input(int ch, WINDOW * mainwin, WINDOW * board, WINDOW * stats_win, int *y_player, int * x_player, struct Stats *stats);
// Display
void refresh_timer(WINDOW * stats_window, int time_started);
void init_color_sceem();
void reverse_position(WINDOW *window, int y_position, int x_position, int direction);
//void debug(WINDOW * stats_window, char message[20]);
void welcome_screen();
void index_to_position( int index_y, int index_x, int *position_y, int *position_x);
void position_to_index(int position_y, int position_x, int *index_y, int *index_x);
void print_mistakes(WINDOW *window, struct Stats);
void print_board(int fields[9][9], WINDOW * field);
void print_game(int fields[9][9], WINDOW * mainwin, WINDOW * board, WINDOW * stats_window, struct Stats stats);
void print_menu(WINDOW* main_win, struct Stats *stats);
void change_difficulty(struct Stats *stats, int val);
void print_difficulty(WINDOW* stats_win, char difficulty[6]);

void changeMode(wchar_t c)
void insert(char val);
void pencil(char val);
