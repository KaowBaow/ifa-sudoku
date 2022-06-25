#include "sudoku.h"


void sudoku_error(WINDOW * board_win, char *type,int row,int col)
{
    int i, pos_y, pos_x;
    int ch;

    wattron(board_win, COLOR_PAIR(4));

    if (strs_equal("row", type)){
        // über alle indexe der Reihe loopen
        for(i = 0; i < SIZE; i++){
            // position finden und char kriegen
            index_to_position(row, i, &pos_y, &pos_x);
            ch = mvwinch(board_win, pos_y, pos_x);
            
            // den char in rot wieder hin schreiben
            mvwaddch(board_win, pos_y, pos_x, ch);

        }
    }else if(strs_equal("col", type)){
        // über alle indexe der Spalte loopen
        for(i = 0; i < SIZE; i++){
            // position finden und char kriegen
            index_to_position(col, i, &pos_y, &pos_x);
            ch = mvwinch(board_win, pos_y, pos_x);
            
            // den char in rot wieder hin schreiben
            mvwaddch(board_win, pos_y, pos_x, ch);

        }
    }
    wattroff(board_win, COLOR_PAIR(2));
    wrefresh(board_win);
}

int check_sudoku(WINDOW * board_win, int a[SIZE][SIZE])
{
    int i, j;
    int si, sj, flag;
    int err = 0;


    /*
       Prüfung der Zeilen
       wir prüfen jede Zelle in jeder Zeile.
       Wir beginnen mit einem Flag 0x0000.
       wenn 1 gefunden wird, wird das nullte Bit des Flags gesetzt.
       wenn 2 gefunden wird, wird das erste Bit gesetzt und so weiter.
       Wenn alle Ziffern 1 bis 9 vorhanden sind, ist der Wert des Flags
       0x01FF.
       Wenn das Flag 0x01FF ist, nachdem eine Zeile durchlaufen wurde,
       hat die Zeile alle Ziffern 1 bis 9.
       Wenn das Flag nach dem Durchlaufen einer Zeile nicht 0x01FF ist,
       ist die Zeile nicht korrekt ausgefüllt.
       Dann rufen wir die Funktion sudokuError() auf.
       Die selbe Logik kommt bei Spalten und den kleinen Quadraten zum einsatzt.
    */
    for(i=0; i<SIZE; i++)
    {
        flag=0x0000;
        for(j=0; j<SIZE; j++)
        {
            flag|=1<<(a[i][j]-1);
        }
        if(flag!=0x01FF)
        {
            sudoku_error(board_win, "row",i,j-1);
            err = -1;
        }
    }

    /*
       Prüfung von Spalten
       Das Flag steht für eine Spalte.
       */
    for(j=0; j<SIZE; j++)
    {
        flag=0x0000;
        for(i=0; i<SIZE; i++)
        {
            flag|=1<<(a[i][j]-1);
        }
        if(flag!=0x01FF)
        {
            sudoku_error(board_win, "col",i-1,j);
            err = -1;
        }
    }
    /*
       Überprüfung von Quadraten (3x3)
       Das flag steht für ein Quadrat.
       */
    for(si=0; si<3; si++)
    {
        for(sj=0; sj<3; sj++)
        {
            flag=0x0000;
            for(i=0; i<3; i++)
            {
                for(j=0; j<3; j++)
                    flag|=1<<(a[si*3+i][sj*3+j]-1);

            }
            if(flag!=0x01FF)
            {
                sudoku_error(board_win, "square",si*3+i-1,sj*3+j-1);
                err = -1;
            }
        }
    }
    return err;
}
