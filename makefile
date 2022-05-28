sudoku: main.c sudoku.c display.c
	gcc main.c display.c sudoku.c -o sudoku -lncurses
