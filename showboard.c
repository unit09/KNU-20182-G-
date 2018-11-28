#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#define BD_H 20
#define BD_W 16

#define BD_X 2
#define BD_Y 7

#define DELAY 100

int board[BD_H][BD_W] = {0, };
int static score = 0;

// 지금은 모듈별로 테스트를 하기위해 main 함수로 되어있지만 
// 개발이 진행되면 show_board함수가 된다.
int main(){
	int i, j;

	// board 초기화 0:빈공간 1:블록있음 2:| 3:=
	// 이 부분은 이후 main함수 혹은 별도의 초기화 함수에 위치하게 된다.
	for(i = 0; i < BD_H; i++){
		for(j = 0; j < BD_W; j++){
			if(j == 0 || j == (BD_W-1)){
				board[i][j] = 2;
			}
			if(i == (BD_H-1)){
				if(j == 0 || j == (BD_W-1))
					board[i][j] = 4;
				else
					board[i][j] = 3;
			}
			/*else
				board[i][j] = 0;*/
		}
	}

	board[BD_H-2][1] = 1;
	board[BD_H-2][2] = 1;
	board[BD_H-2][3] = 1;
	board[BD_H-2][4] = 1;
	board[BD_H-3][4] = 1;

	initscr();

	clear();

	move(BD_X, BD_Y);
	
	for(i = 0; i < BD_H; i++){
		for(j = 0; j < BD_W; j++){
			move(BD_X+i, BD_Y+j);
			if(board[i][j] == 0)
				addch(' ');
			else if(board[i][j] == 1)
				addch('o');
			else if(board[i][j] == 2)
				addch('|');
			else if(board[i][j] == 3)
				addch('=');
			else if(board[i][j] == 4)
				addch(' ');
		}
	}

	move(10, 40);
	printw("SCORE : %d", score);
	
	move(LINES-1, 0);	

	refresh();

	getch();

	endwin();

}
