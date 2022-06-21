#include "sudoku.h"

/**
 *  generieren einer neuen StatsStruct
*/
struct Stats getStats(){
    struct Stats stats = {
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
void change_difficulty(struct Stats *stats, int val){
    // Von high oder low in die mitte schalten
    if ((strs_equal("LOW", stats->difficulty) && val > 0) || (strs_equal("HIGH", stats->difficulty) && val < 0)){
        sprintf(stats->difficulty, "MED");
        return;
    }
    // Von Medium high oder runterschalten
    if (strs_equal("MED", stats->difficulty)){
        if (val < 0)
            sprintf(stats->difficulty, "LOW");

        else if(val > 0)
            sprintf(stats->difficulty, "HIGH");
    }
}

/**
 *Verpacken der strcmpfunktion da diese sehr verwirrend ist
 */
int strs_equal(char *str1, char *str2){
    if (strcmp(str1, str2) == 0){
        return 1;
    }else{
        return 0;
    }
}
