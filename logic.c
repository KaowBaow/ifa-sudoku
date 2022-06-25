#include "sudoku.h"


void report(char *s,int i,int j)
{
printf("\nThe sudoku is INCORRECT");
printf("\nin %s. Row:%d,Column:%d",s,i+1,j+1);
//getch();
exit(0);
}

void checkSudoku(int a[i][j]){
/*++++++++++++++++++
checking rows
+++++++++++++++++++
we check each cell in each row.
We start with a flag 0x0000.
if 1 is found zeroth bit of flag is set.
if 2 is found, first bit is set
and so on.
If all digits 1 to 9 are present, flag's value
will be 0x01FF.
If flag is 0x01FF after traversing a row,
the row has all numbers 1 to 9.
So, it is correct.
If the flag is not 0x01FF after traversing a row,
the row is incorrectly filled.
Then we call report() function
*/
for(i=0;i<9;i++)
    {
    flag=0x0000;
    for(j=0;j<9;j++)
        flag|=1<<(a[i][j]-1);
    if(flag!=0x01FF)
        report("row",i,j-1);
    }

/*++++++++++++++++++
checking columns
+++++++++++++++++++
Just like row checking.
The flag is for a column.
*/
for(j=0;j<9;j++)
    {
    flag=0x0000;
    for(i=0;i<9;i++)
        flag|=1<<(a[i][j]-1);
    if(flag!=0x01FF)
        report("col",i-1,j);
    }
/*++++++++++++++++++
checking Squares (3x3)
+++++++++++++++++++
Just like row checking.
The flag is for a square.
*/
for(si=0;si<3;si++)
    {
    for(sj=0;sj<3;sj++)
        {
        flag=0x0000;
        for(i=0;i<3;i++)
            {
            for(j=0;j<3;j++)
                flag|=1<<(a[si*3+i][sj*3+j]-1);

            }
        if(flag!=0x01FF)
                report("square",si*3+i-1,sj*3+j-1);
        }
    }
printf("\nThe sudoku is correct");
}
