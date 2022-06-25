CC=gcc
CFLAGS=-lncurses -g -lm -std=c99
DEPS= sudoku.h
OBJ=main.o sudoku.o display.o controls.o stats.o logic.o difficulties.o
SRC=main.c sudoku.c display.c controls.c stats.c logic.c difficulties.c

sudoku: $(OBJ)
	$(CC)  -o sudoku $(OBJ) $(CFLAGS) -w


debug: $(OBJ)
	$(CC) -o debug $(SRC) $(CFLAGS) -Wall
