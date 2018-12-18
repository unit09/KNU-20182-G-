#include <stdio.h>
#include <stdlib.h>
#include "tetris.h"

//라인 함수

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
