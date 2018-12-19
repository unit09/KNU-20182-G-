#include <pthread.h>
#include <termios.h>
#include <sys/time.h>

#include "tetris.h"

void *screen(void *);
void showboard();
void moveA(int);
int set_ticker(int);
void setBlock();
void removeLine();
void downLine(int);
void nextBlock(int);
void gameover();
int getscore();

int board[BD_H][BD_W] = {0, };
int play = 0;	// 1 = play, 0 = not start or system wait, 2 = pause, 3 = gameover
int delay = 500;	//level1: 500

int num;	// 현재 블록의 번호
int shape = 0;	// 현재 블록의 회전상태
cur current;	// 현재 블록의 위치
int next;	// 다음 블록의 번호

int main(){
	int i, j;
	char c;
	int check;
	int temp[4][4];
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

	initscr();
	//crmode();
	//noecho();
	curs_set(0);
	clear();
	move(3, 5);
	printw("TETRIS");
	move(5, 5);
	printw("Start with Press S");
	move(7, 5);
	printw("Quit with Press Q");
	move(10, 5);
	printw("Move : A(Left) D(Right), Quick : S, Rotation : F");
	refresh();	

	while(1){
		c = getchar();
		if(c == 'S'){
			play = 1; 
			break;
		}
		if(c == 'Q'){
			endwin();
			exit(0);
		}
	}

	if(pthread_create(&screen_thread, NULL, screen, (void*)NULL)){
		perror("pthread_create");
		exit(1);
	}

	current.x = BLOCK_X;
	current.y = BLOCK_Y;
	num = createBlock();
	next = createBlock();

	while(1){
		c = getchar();
		if(c == 'Q') break;
		if(c == 'p'){
			if(play == 2)
				play = 1;
			else if(play == 1)
				play = 2;
		}
		if(c == 'R'){
			play = 0;
			for(i = 0; i < BD_H - 1; i++){
				for(j = 1; j < BD_W - 1; j++){
					board[i][j] = 0;
				}
			}
			scoreEvent(-1);
			current.x = BLOCK_X;
			current.y = BLOCK_Y;
			num = createBlock();
			next = createBlock();
			play = 1;
		}

		if(play == 1){
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
						gameover();
						if(play != 3){
							current.x = BLOCK_X;
							current.y = BLOCK_Y;
							num = next;
							next = createBlock();
							play = 1;
						}
					}
					break;
			}
		}
	}

	endwin();
}

void *screen(void *no){
	signal(SIGALRM, moveA);
	set_ticker(delay);

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
	
	if(play == 1){
		getBlock(temp, num, shape);
		check = vaildMove(temp, 0, 1);
		if(check == 0)
			current.y++;
		else if(check == 2){
			play = 0;
			setBlock();
			removeLine();
			gameover();
			if(play != 3){
				current.x = BLOCK_X;
				current.y = BLOCK_Y;
				num = next;
				next = createBlock();
				play = 1;
			}
		}
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
		}
	}

	showScore();
	move(16, 40);
	if(play == 2)
		printw("PAUSE");
	else if(play == 3)
		printw("GAME OVER");

	nextBlock(next);
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

void removeLine(){
	int i, j;
	int check = 0;
	int gain = 0;
	int delay2;

	for(i = 0; i < BD_H-1; i++){
		for(j = 1; j < BD_W-1; j++){
			if(board[i][j] == 1) check++;
		}
		if(check == BD_W-2){
			for(j = 1; j < BD_W-1; j++){
				board[i][j] = 0;
			}
			gain++;
			downLine(i);
		}
		check = 0;	
	}
	delay2 = scoreEvent(gain);
	if(delay2 != delay)
		set_ticker(delay2);
}

void downLine(int col){
	int i, j;

	for(i = col; i > 0; i--){
		for(j = 1; j < BD_W-1; j++ ){
			board[i][j] = board[i-1][j];
		}
	}

	for(j = 1; j < BD_W-1; j++){
		board[0][j] = 0;
	}
}

void nextBlock(int num){
	int i, j;
	int temp[4][4];
	
	getBlock(temp, num, 0);
	
	move(BD_Y, BD_X + BD_W + 2);
	printw("* NEXT * ");
	for(i = 0; i < 4; i++){
		move(BD_Y + 1 + i, BD_X + BD_W + 2);
		addstr("* ");
		for(j = 0; j < 4; j++){
			if(temp[i][j] == 0)
				addch(' ');
			else
				addch('O');
		}
		addstr(" *");
	}
	move(BD_Y + 5, BD_X + BD_W + 2);
	printw(" ****** ");
}

void gameover(){
	int i;

	for(i = BLOCK_X - BD_X; i < BLOCK_X - BD_X + 4; i++){
		if(board[0][i] == 1){
			play = 3;
			timer = time(NULL);
			t = localtime(&timer);
			fp = fopen("score.txt", "a");
			if(!fp){
				perror("fopen");
				exit(2);
			}
			fprintf(fp, "%d-%d-%d %d:%d:%d %d점\n", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, getscore());
			break;
		}
	}
}
