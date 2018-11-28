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

#define DELAY 1

int board[BD_H][BD_W] = {0, };
int score = 0;

void showboard();
int createBlock();
void moveBlock(int, int, int, int);
int rotation(int);

int main(){
	int i, j;
	int ro_x, ro_y, num, shape = 0;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);

	for(i = 0; i < BD_H; i++){
		for(j = 0; j < BD_W; j++){
			if(j == 0 || j == (BD_W-1)){
				board[i][j] = 2;
			}
			if(i == (BD_H-1)){
				if(j == 0 || j == (BD_W-1))
					board[i][j] = 0;
				else
					board[i][j] = 3;
			}
		}
	}

	ro_x = BLOCK_X;
	ro_y = BLOCK_Y;
	num = createBlock();

	initscr();

	while(1){
		clear();

		showboard();
		moveBlock(ro_x, ro_y, num, shape);

		move(LINES-1, COLS-1);

		refresh();
		sleep(DELAY);
		ro_y++;
		shape = rotation(shape);
	}

	endwin();
}

void showboard(){
	int i, j;

	move(BD_Y, BD_X);
	
	for(i = 0; i < BD_H; i++){
		for(j = 0; j < BD_W; j++){
			move(BD_Y+i, BD_X+j);
			if(board[i][j] == 0)
				addch(' ');
			else if(board[i][j] == 1)
				addch('O');
			else if(board[i][j] == 2)
				addch('|');
			else if(board[i][j] == 3)
				addch('=');
			else if(board[i][j] == 4)
				addch('O');
		}
	}

	move(10, 40);
	printw("SCORE : %d", score);
	
	move(13, 40);
	printw("QUIT : ctrl + c");
}

int rotation(int shape){
	//회전이 가능한지도 체크해야함 그걸 위해 ro_x와 ro_y를 받아와야함
	shape++;
	if(shape >= 4){
		shape = 0;
	}

	return shape;			
}
