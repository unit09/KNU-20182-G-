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
	num = createBlock();	//나중에 다른곳에도 추가되어야 함

	while(1){
		c = getchar();
		if(c == 'Q') break;
		switch(c){
			case 'f':
				shape = rotation(shape);
				break;
			case 'a':
				current.x--;
				break;
			case 'd':
				current.x++;
				break;
			case 's':
				current.y++;
				break;
		}
	}

	endwin();
}

void *screen(void *no){
	initscr();
	crmode();
	noecho();
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
	current.y++;
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

int rotation(int shape){
	//회전이 가능한지도 체크해야함 그걸 위해 ro_x와 ro_y를 받아와야함
	shape++;
	if(shape >= 4){
		shape = 0;
	}

	return shape;			
}

cur getCursor(void){
	cur temp;
	getyx(stdscr,temp.x,temp.y); //STDSCR 상태 커서를 받을 수있음(real screen 에 나오기 전에 buffer 상태)
	return temp;
}
