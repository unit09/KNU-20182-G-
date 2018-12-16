#include "tetris.h"

int score = 0;
int level = 1;

int scoreEvent(int gain) {
	int i;
	int delay;

	if (gain == -1) {
		level = 1;
		score = 0;
		return 500;
	}

	for (i = 1; i <= gain; i++)
		score += i;
	if (score >= 5)
		level = 2;
	if (score >= 10)
		level = 3;
	if (score >= 20)
		level = 4;
	if (score >= 30)
		level = 5;

	delay = 600 - (level * 100);
	return delay;
}