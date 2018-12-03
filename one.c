//file : one.c
//description : 커서 투명화, 커서 세팅, 디텍트 함수

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

int BLK[][4][4] = { //** 블록은 모양별로 숫자 행렬로 표현된다. 4행 4열로 표현되며 4개의 회전모양을 갖는다.





			               /*■



					  ■ ■ ■*/



	{



{ 0,0,0,0 },



{ 1,0,0,0 },



{ 1,1,1,0 },



{ 0,0,0,0 } },



	{



{ 0,0,1,0 },



{ 0,0,1,0 },



{ 0,1,1,0 },



{ 0,0,0,0 } },



	{



{ 1,1,1,0 },



{ 0,0,1,0 },



{ 0,0,0,0 },



{ 0,0,0,0 } },



	{



{ 1,1,0,0 },



{ 1,0,0,0 },



{ 1,0,0,0 },



{ 0,0,0,0 } },



/* 두번째블록



         ■



      ■ ■ ■    */



	{



{ 0, 0, 0, 0 },



{ 0, 0, 1, 0 },



{ 1, 1, 1, 0 },



{ 0, 0, 0, 0 } },



{



{ 0, 1, 1, 0 },



{ 0, 0, 1, 0 },



{ 0, 0, 1, 0 },



{ 0, 0, 0, 0 } },



{



{ 1, 1, 1, 0 },



{ 1, 0, 0, 0 },



{ 0, 0, 0, 0 },



{ 0, 0, 0, 0 } },



{



{ 1, 0, 0, 0 },



{ 1, 0, 0, 0 },



{ 1, 1, 0, 0 },



{ 0, 0, 0, 0 } },







/* 세번째블록



   ■



 ■ ■ ■    */



	{



{ 0, 0, 0, 0 },



{ 0, 1, 0, 0 },



{ 1, 1, 1, 0 },



{ 0, 0, 0, 0 } },



{



{ 0, 0, 0, 0 },



{ 0, 1, 0, 0 },



{ 1, 1, 0, 0 },



{ 0, 1, 0, 0 } },



{



{ 0, 0, 0, 0 },



{ 0, 0, 0, 0 },



{ 1, 1, 1, 0 },



{ 0, 1, 0, 0 } },



{



{ 0, 0, 0, 0 },



{ 0, 1, 0, 0 },



{ 0, 1, 1, 0 },



{ 0, 1, 0, 0 } },







/* 네번째블록







■ ■ ■ ■  */



	{



{ 0, 1, 0, 0 },



{ 0, 1, 0, 0 },



{ 0, 1, 0, 0 },



{ 0, 1, 0, 0 } },



{



{ 0, 0, 0, 0 },



{ 0, 0, 0, 0 },



{ 1, 1, 1, 1 },



{ 0, 0, 0, 0 } },



{



{ 0, 1, 0, 0 },



{ 0, 1, 0, 0 },



{ 0, 1, 0, 0 },



{ 0, 1, 0, 0 } },



{



{ 0, 0, 0, 0 },



{ 0, 0, 0, 0 },



{ 1, 1, 1, 1 },



{ 0, 0, 0, 0 } },







/* 다섯번째블록







■ ■



■ ■     */



	{



{ 1, 1, 0, 0 },



{ 1, 1, 0, 0 },



{ 0, 0, 0, 0 },



{ 0, 0, 0, 0 } },



{



{ 1, 1, 0, 0 },



{ 1, 1, 0, 0 },



{ 0, 0, 0, 0 },



{ 0, 0, 0, 0 } },



{



{ 1, 1, 0, 0 },



{ 1, 1, 0, 0 },



{ 0, 0, 0, 0 },



{ 0, 0, 0, 0 } },



{



{ 1, 1, 0, 0 },



{ 1, 1, 0, 0 },



{ 0, 0, 0, 0 },



{ 0, 0, 0, 0 } },











/* 여섯번째블록



  ■ ■



■ ■     */



	{



{ 0, 0, 0, 0 },



{ 0, 1, 1, 0 },



{ 1, 1, 0, 0 },



{ 0, 0, 0, 0 } },



{



{ 0, 1, 0, 0 },



{ 0, 1, 1, 0 },



{ 0, 0, 1, 0 },



{ 0, 0, 0, 0 } },



{



{ 0, 0, 0, 0 },



{ 0, 1, 1, 0 },



{ 1, 1, 0, 0 },



{ 0, 0, 0, 0 } },



{



{ 0, 1, 0, 0 },



{ 0, 1, 1, 0 },



{ 0, 0, 1, 0 },



{ 0, 0, 0, 0 } },







/* 일곱번째블록







■ ■



  ■ ■   */



	{



{ 0, 0, 0, 0 },



{ 1, 1, 0, 0 },



{ 0, 1, 1, 0 },



{ 0, 0, 0, 0 } },



{



{ 0, 0, 1, 0 },



{ 0, 1, 1, 0 },



{ 0, 1, 0, 0 },



{ 0, 0, 0, 0 } },



{



{ 0, 0, 0, 0 },



{ 1, 1, 0, 0 },



{ 0, 1, 1, 0 },



{ 0, 0, 0, 0 } },



{



{ 0, 0, 1, 0 },



{ 0, 1, 1, 0 },



{ 0, 1, 0, 0 },



{ 0, 0, 0, 0 } },







};//블록 모양


void rm_Cursor(void) // 커서를 안 보이게 한다.
{

	curs_set(0);
}

void st_Cursor(int x, int y) // 커서의 위치를 매개변수로 받아 옮긴다.
{
	move(y,x); // int move( 열, 행)
}


int Detect (int rotation, int move_x, int move_y)//보드상 1인지 아닌지 확인하는 함수
{
	int x, y;
	int ARR_X, ARR_Y;
	getyx( stdscr, y, x); 
	// int getsyx(window pointer, int y, int x) 
	// 가상 화면의 커서를 y와 x에 저장하거나 커서를 지정한다. 
	
	ARR_X = x + move_x;
	ARR_Y = y + move_y;

	ARR_X = (ARR_X - 5 )/2; //BD_X = 5
	ARR_Y = ARR_Y - 3; //BD_Y = 3

	for (y=0; y<4; y++)
	{
		for(x=0;x<4;x++)
		{
			if((BLK[rotation][y][x] == 1) && BD[ARR_Y+y][ARR_X+x] ==1)
				return 1;
		}

	}

	return 0;
}

//벽돌생성
void show_BLK(int rotation) //특정한 모양의 블럭을 해당 커서 위치에 생성하라, 라는 함수
{
	int cursor_x, cursor_y;
	int x, y;

	getyx(stdscr, cursor_y, cursor_x);

	int P;

	P = Detect(rotation, 0, 0);

	if(P == 0)
	{
		for(y=0 ; y<4 ; y++)
		{
			for(x=0 ; x<4 ; x++)
			{
				st_Cursor(cursor_x + (x*2), cursor_y + y);
				if(BLK[rotation][y][x] == 1)
					printf("■ ");
			}
		}
	}

	st_Cursor(cursor_x, cursor_y);

	
}

void remove_BLK(int rotation, int move_x, int move_y)
{
	int P;
	int cursor_x, cursor_y;
	int x, y;

	getyx(stdscr, cursor_y, cursor_x);
	P = Detect(rotation, move_x, move_y);

	if(P == 0) //겹치지 않으면 현재 커서위치 블럭을 지운다.
	{
		for(y=0; y<4; y++)
		{
			for(x=0; x<4; x++)
			{
				st_Cursor(cursor_x + (2*x), cursor_y + y);

				if(BLK[rotation][y][x] == 1)
					printf(" "); //블럭삭제
			}
		}

		st_Cursor(cursor_x + move_x, cursor_y + move_y); //커서이동

	}

}


void Board_Cognition(int n, int move_x, int move_y)//보드 인식 함수
{
	int x, y;
	int cursor_x, cursor_y;
	getyx(stdscr, cursor_y, cursor_x);

	int ARR_X = cursor_x + move_x; //콘솔좌표열
	int ARR_Y = cursor_y + move_y; //콘솔좌표행

	ARR_X = (ARR_X - 5)/2; //BD_X = 5  //콘솔좌표 배열열 변환값
	ARR_Y = ARR_Y - 3; //BD_Y = 3   //콘솔좌표 배열행 변환값 

 	//보드판에서 블록이동시 1인식
	
	for(y=0 ; y<4 ; y++)
	{
		for(x=0; x<4 ; x++)
		{
			if(BLK[n][y][x] == 1)
			{
				BD[ARR_Y + y][ARR_X + x] = 1;
			}
		}
	}


	return;

}


void Array_Down(int col) //배열 블록 옮김
{
	int y, x;


	for ( y = col ; y >= 0 ; y--)
	{
		for( x = 1 ; x <= 10 : x++ )
		{
			BD[y][x] = BD[y-1][x];//해당 y줄보다 한줄 전 줄의 1들을 밑으로 내린다.
		}
	}

	//BD배열 0행에 0삽입
	//위의 반복문에서 보드 0행의 값은 변하지 않으므로 여기서 0으로 따로 초기화해준다.
	
	for ( x = 1 ; x <= 10 ; x++ )
		BD[0][x] = 0;

	/*BD배열 1값 전체 출력*/
	//네모 아닌 부분은 빈칸으로 리셋
	for ( y = 1 ; y <= 19 ; y++ )
	{
		for ( x = 1 ; x <= 10 ; x++ )
		{
			st_Cursor((BOARD_X) + (x*2) + 1, y + BD_Y);

			if ( BD[y][x] == 1)
				printf("■ ");

			else
				printf(" ");
		}
	}
}




