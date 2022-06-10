CC=gcc
CFLAGS=-lncurses -g -lm -std=c99
DEPS= sudoku.h
OBJ=main.o sudoku.o display.o

sudoku: $(OBJ)
	$(CC)  -o sudoku $(OBJ) $(CFLAGS) -w


debug: $(OBJ)
	$(CC) -o debug $(OBJ) $(CFLAGS) -Wall
