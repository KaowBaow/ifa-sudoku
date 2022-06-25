#include <time.h>
#include "lib/include/ncursesw/curses.h"
#include <stdlib.h>
#include <string.h>
#include<unistd.h>
//logic
#define SIZE 9
void sudokuErorr(char *s,int i,int j);
void checkSudoku(int a[SIZE][SIZE]);

// Stats
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
struct Stats getStats();

struct menu_choice{
    char display[12];
    int highlighted;
};
// Anzahl der Menuoptionen
#define CHOICES 4
int select_choice(struct menu_choice choices[CHOICES], struct Stats *stats);


// Globale Display Funktionen
void init_color_sceem();
void print_welcome_screen();
void print_timer(WINDOW * stats_win, int time_started);
void print_menu(WINDOW* main_win, struct Stats *stats);
void print_game(int fields[9][9], WINDOW * main_win, WINDOW * board_win, WINDOW * stats_win, struct Stats stats);
void print_board(int fields[9][9], WINDOW * board_win);
void print_affected(WINDOW* board_win, int index_y, int index_x);

void random_grid(int (*fields)[9]);

int strs_equal(char *str1, char *str2);

void reverse_position(WINDOW *win, int y_position, int x_position, int direction);

void use_input(int ch, WINDOW * main_win, WINDOW * board_win, WINDOW * stats_win, int *y_player, int * x_player, struct Stats *stats);

void index_to_position( int index_y, int index_x, int *position_y, int *position_x);
void position_to_index(int position_y, int position_x, int *index_y, int *index_x);

void change_difficulty(struct Stats *stats, int val);
