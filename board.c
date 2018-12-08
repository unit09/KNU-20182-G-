#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <pthread.h>
#include <termios.h>

//board size
#define BD_H 18
#define BD_W 16
//board position
#define BD_X 7
#define BD_Y 4
//block initial position
#define BLOCK_X 13
#define BLOCK_Y 0

#define DELAY 500

int board[BD_H][BD_W] = {0, };
int score = 0;

void *screen(void *);
void showboard();
int createBlock();
void moveBlock(int, int, int, int);
int rotation(int);

int ro_x, ro_y, num, shape = 0;

int main(){
	int i, j;
	char c;
	pthread_t screen_thread;
	
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, SIG_IGN);

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

	if(pthread_create(&screen_thread, NULL, screen, (void*)NULL)){
		perror("pthread_create");
		exit(1);
	}
	

	ro_x = BLOCK_X;
	ro_y = BLOCK_Y;
	num = createBlock();	//나중에 다른곳에도 추가되어야 함

	while(1){	// 모든 행동들이 한타임 느림, 행동을 했을때 즉시 적용되서 보이게 해야됨
		c = getchar();
		if(c == 'Q') break;
		switch(c){
			case 'f':
				shape = rotation(shape);
				break;
			case 'a':
				ro_x--;
				break;
			case 'd':
				ro_x++;
				break;
			case 's':
				ro_y++;	//되기는 하는데 너무 빠름 보이지 않을정도로...
				break;
		}
	}

	endwin();
}

void *screen(void *no){
	initscr();
	crmode();
	noecho();

	while(1){
		clear();
		showboard();
		moveBlock(ro_x, ro_y, num, shape);

		move(LINES-1, COLS-1);

		refresh();
		usleep(DELAY*1000);
		ro_y++;
	}
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
	printw("QUIT : Q");
}

int rotation(int shape){
	//회전이 가능한지도 체크해야함 그걸 위해 ro_x와 ro_y를 받아와야함
	shape++;
	if(shape >= 4){
		shape = 0;
	}

	return shape;			
}
