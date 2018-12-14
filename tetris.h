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
#define BLOCK_Y 0

typedef struct cursor{
	int x;
	int y;
}cur; 

cur getCursor(void);
int createBlock();
void paintBlock(cur, int, int);
