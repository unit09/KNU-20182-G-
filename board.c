#include <pthread.h>
#include <termios.h>
#include <sys/time.h>

#include "tetris.h"

#define DELAY 500	//level1: 500 -> 400 -> 300 -> 200 -> 100(final)

void *screen(void *);
void showboard();
int rotation(int);
void moveA(int);
int set_ticker(int);

int board[BD_H][BD_W] = {0, };
int score = 0;
int num;	// 현재 블록의 번호 (모양)
int shape = 0;	// 현재 블록의 모양 (회전 상태)
cur current;

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
	
	current.x = BLOCK_X;
	current.y = BLOCK_Y;
	num = createBlock();

	while(1){
		c = getchar();
		if(c == 'Q') break;
		
		switch(c){
			case 'f':
				shape = rotation(num, shape);
				break;
			case 'a':
				getBlock(temp, num, shape);
				if(vaildMove(temp, -1, 0) == 0)
					current.x--;
					break;
			case 'd':
				getBlock(temp, num, shape);
				if(vaildMove(temp, 1, 0) == 0)
					current.x++;
				break;
			case 's':
				getBlock(temp, num, shape);
				check = vaildMove(temp, 0, 1);
				if(check == 0)
					current.y++;
				else if(check == 2){
					play = 0;
					setBlock();
					removeLine();
					break;
				
				}
		}
	}
	endwin();
}

void *screen(void *no){
	initscr();
	curs_set(0);

	signal(SIGALRM, moveA);
	set_ticker(DELAY);

	while(1){
		clear();
		showboard();
		paintBlock(current, num, shape);

		move(LINES-1, COLS-1);

		refresh();
	}
}

void moveA(int signum){
	int temp[4][4];
	int check;

	signal(SIGALRM, moveA);
	

	getBlock(temp, num, shape);
	check = vaildMove(temp, 0, 1);
	if(check == 0)
		current.y++;
	else if(check == 2){
		setBlock();
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

int set_ticker(int n_msecs){
	struct itimerval new_timeset;
	long n_sec, n_usecs;

	n_sec = n_msecs/1000;
	n_usecs = (n_msecs%1000) * 1000L;

	new_timeset.it_interval.tv_sec = n_sec;
	new_timeset.it_interval.tv_usec = n_usecs;
	new_timeset.it_value.tv_sec = n_sec;
	new_timeset.it_value.tv_usec = n_usecs;

	return setitimer(ITIMER_REAL, &new_timeset, NULL);
}

int vaildMove(int temp[][4], int x, int y){
	int i, j;
	cur now;

	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if(temp[i][j] == 1){
				now = current;
				now.x += j + x;
				now.y += i + y;
				now = getCursor(now);
				if(board[now.y][now.x] != 0){
					if(y > 0) return 2;
					else return 1;
				}
			}				
		}
	}

	return 0;
}

cur getCursor(cur temp){	// 원하는 위치를 보드에서의 위치로 변환
	temp.x -= BD_X;
	temp.y -= BD_Y;

	return temp;
}

void setBlock(){
	int temp[4][4];
	int i, j;
	cur now;
	
	getBlock(temp, num, shape);
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			if(temp[i][j] == 1){
				now = current;
				now.x += j;
				now.y += i;
				now = getCursor(now);
				board[now.y][now.x] = 1;
			}				
		}
	}
	shape = 0;
}
