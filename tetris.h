#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

//board size
#define BD_H 18
#define BD_W 16
//board position
#define BD_X 7
#define BD_Y 4
//block initial position
#define BLOCK_X 13
#define BLOCK_Y 1

typedef struct cursor{
	int x;
	int y;
}cur; 

int createBlock();
void paintBlock(cur, int, int);
void getBlock(int[][4], int, int);
cur getCursor(cur);
int rotation(int, int);
int vaildMove(int[][4], int, int);
int scoreEvent(int);
void showScore();
