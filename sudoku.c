#include <curses.h>
#include "sudoku.h"



int move_up(int *y_player);
int move_down(int *y_player);
int move_left(int *x_player);
int move_right(int *x_player);

/**
 * Füllt das Feld volkommen Random

void random_grid(int (*fields)[9])
{
    // Initialisieren des Random-Seeds
    time_t t;
    srand((unsigned) time(&t));

    // neues Feld erschaffen und darüber loopen
    //char new_field[9][9];
    int row, col;
    for(row = 0; row < 9; ++row)
    {
        for(col = 0; col < 9; ++col)
        {
            // Zufällige Zahl zwischen 1-9
            fields[row][col] = (rand() % 9) + 1;
        }
    }
}
*/

    int grid_easy[9][9] =
    {
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

    int grid_normal[9][9] =
    {
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

    int grid_hard[9][9] =
    {
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


void use_input(
    int ch,
    WINDOW * mainwin, WINDOW * board, WINDOW * stats_window,
    int *y_player, int *x_player, struct Stats *stats
)
{
    int success;

    // Das Highlighting an der Selektierten Stelle entfernen
    reverse_position(board, *y_player, *x_player, 0);

    switch(ch)
    {
    // Bewegung in alles Richtungen
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
        print_menu(mainwin, stats);
        // board resetten
        print_game(stats->fields, mainwin, board, stats_window, *stats);
        success = 1;
        break;

    case 't':
        //tip
        success = -1;
        break;

    // kriege ich in meinem setup nicht aufgefangen
    case KEY_MOUSE:
        success = 5;

// change input mode with c
    case 99:
        if (mode == 'i')
        {
            changeMode('p');
        }
        else
        {
            changeMode('i');
        }
        break;
    default:
        if ((ch > '0' && ch <= '9') || ch == ' ')
        {
            window.select(ch);
            if (mode == 'i')
            {
                insert(ch);
            }
            else if (mode == 'p')
            {
                pencil(ch);
            }
        }



    case KEY_HOME:
    default:
        success = 0;
        break;
    }
    void Game::changeMode(wchar_t c)
    {
        std::string s;
        switch (c)
        {
        case L'i':
            s = "Input mode";
            mode = c;
            break;
        case L'p':
            s = "Pencil mode";
            mode = c;
            break;
        case L'g':
            s = "Go";
            mode = c;
            break;
        }
        window.changeMode(s);
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

// Bewegung oder Aktion hat funktioniert
    mvprintw(16, 40, "S:%d", success);

    mvprintw(15, 40, "K:%d", ch);
    mvprintw(17, 40, "Y:%d", *y_player);
    mvprintw(18, 40, "X:%d", *x_player);

    int index_y, index_x;
    position_to_index(*y_player, *x_player, &index_y, &index_x);

    mvprintw(17, 45, "Yi:%d", index_y);
    mvprintw(18, 45, "Xi:%d", index_x);
}


int move_up(int *y_player)
{
    if (*y_player >= 3)
    {
        *y_player -= 2;
        return 0;
    }
    else
    {
        return -1;
    }
}

int move_down(int *y_player)
{
    if (*y_player <= 15)
    {
        *y_player += 2;
        return 0;
    }
    else
    {
        return -1;
    }
}
int move_left(int *x_player)
{
    if (*x_player >= 6)
    {
        *x_player -= 4;
        return 0;
    }
    else
    {
        return -1;
    }
}
int move_right(int *x_player)
{
    if (*x_player <= 30)
    {
        *x_player += 4;
        return 0;
    }
    else
    {
        return -1;
    }
}

/**
 *  generieren einer neuen StatsStruct
*/
struct Stats getStats()
{
    struct Stats stats =
    {
        0,    // time_started
        0,    // time_elapsed
        0,    // mistakes
        3,    // max_mistakes
        2,    // available_tipes
        "LOW" // difficulty
    };
    return stats;
}

/**
 * Ändert bei val < 0 die Schwierigkeit runter und bei val > 0 hoch
 */
void change_difficulty(struct Stats *stats, int val)
{
    // Von high oder low in die mitte schalten
    if ((strs_equal("LOW", stats->difficulty) && val > 0) || (strs_equal("HIGH", stats->difficulty) && val < 0))
    {
        sprintf(stats->difficulty, "MED");
        return;
    }
    // Von Medium high oder runterschalten
    if (strs_equal("MED", stats->difficulty))
    {
        if (val < 0)
            sprintf(stats->difficulty, "LOW");

        else if(val > 0)
            sprintf(stats->difficulty, "HIGH");
    }
}

/**
 *Verpacken der strcmpfunktion da diese sehr verwirrend ist
 */
int strs_equal(char *str1, char *str2)
{
    if (strcmp(str1, str2) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
