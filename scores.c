#include "tetris.h"

int score = 0;
int level = 1;

void showScore(){
	move(4, 40);
	printw("LEVEL : %d", level);

	move(6, 40);
	printw("SCORE : %d", score);
	
	move(8, 40);
	printw("QUIT : Q");

	move(10, 40);
	printw("PAUSE : p");

	move(12, 40);
	printw("RESTART : R");
}

int scoreEvent(int gain){
	int i;
	int delay;

	if(gain == -1){
		level = 1;
		score = 0;
		return 500;
	}

	for(i = 1; i <= gain; i++)
		score += i;
	if(score >= 5)
		level = 2;
	if(score >= 10)
		level = 3;
	if(score >= 20)
		level = 4;
	if(score >= 30)
		level = 5;

	delay = 600 - (level*100);
	return delay;
}

int getscore(){
	return score;
}
