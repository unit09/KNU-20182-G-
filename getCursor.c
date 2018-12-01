#include <stdio.h>
#include <curses.h>

typedef struct cursor{
	int x;
	int y;
}cur; 
//
cur getCursor(void){

	initscr();
	cur temp;
//	move(10,20);
	
	getyx(stdscr,temp.x,temp.y); //STDSCR 상태 커서를 받을 수있음(real screen 에 나오기 전에 buffer 상태)
					
//	printf("%d %d\n", temp.x, temp.y);
	endwin();

	return temp;
}
/* test
int main(void){

	cur temp;

	temp=getCursor();

	printf("%d %d\n", temp.x, temp.y);

	return 0;
}
*/







