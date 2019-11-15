#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define LEFT 75 // 방향키 왼쪽
#define RIGHT 77 // 방향키 오른쪽
#define UP 72 // 방향키 위쪽
#define DOWN 80 // 방향키 아래쪽
#define ENTER 13 // 엔터키 (확인버튼)

void init(void);
void title_draw(void);
int menu_draw(void);
int key_control(void);
void gotoxy(int x, int y);
void info_draw(void);

int key; // 키보드로 부터 입력받은 값

int main(void)
{
	int menu_code;
	
	init();
	while (1)
	{
		title_draw();
		menu_code = menu_draw();

		if (menu_code == 0)
		{
			printf("a");
		}
		else if (menu_code == 2)
		{
			info_draw();
		}
		else if (menu_code == 4)
		{
			break;
		}
		menu_code = 5;
		system("cls");
	}

	gotoxy(30, 24);
	printf("게임 종료!");
	_getch();

	return 0;

}

void init(void) // 콘솔창의 크기 와 커서 
{
	
	system("mode con cols=63 lines=28 | title Escape Game");
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

}

void gotoxy(int x, int y)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


void title_draw(void) // 타이틀 그리기
{
	printf("\n\n");
	printf("  _____    _    ____ _____ _   ___        _____  ____  __  __ \n");
	printf(" | ____|  / \\  |  _ \\_   _| | | \\ \\      / / _ \\|  _ \\|  \\/  |\n");
	printf(" |  _|   / _ \\ | |_) || | | |_| |\\ \\ /\\ / / | | | |_) | |\\/| |\n");
	printf(" | |___ / ___ \\|  _ < | | |  _  | \\ V  V /| |_| |  _ <| |  | |\n");
	printf(" |_____/_/   \\_\\_| \\_\\|_| |_| |_|  \\_/\\_/  \\___/|_| \\_\\_|  |_|\n");
	printf("                   ____    _    __  __ _____                  \n");
	printf("                  / ___|  / \\  |  \\/  | ____|                 \n");
	printf("                 | |  _  / _ \\ | |\\/| |  _|                   \n");
	printf("                 | |_| |/ ___ \\| |  | | |___                  \n");
	printf("                  \\____/_/   \\_\\_|  |_|_____|                 \n");

}

int key_control(void)
{
	key = 0; // 키값을 초기화
	while (1)
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == 224)
			{
				key = _getch();
				switch (key)
				{
				case 72:
					return UP;
					break;
				case 75:
					return LEFT;
					break;
				case 77:
					return RIGHT;
					break;
				case 80:
					return DOWN;
					break;
				default:
					break;
				}
			}
			else
			{
				if (key == 13)
					return ENTER;
			}
			
		}
	}
}

int menu_draw(void) // 메뉴를 그리는 함수
{
	int x = 30;
	int y = 16;

	gotoxy(x - 2, y);
	printf("> 게임시작");
	gotoxy(x, y + 2);
	printf("조작방법");
	gotoxy(x, y + 4);
	printf("  종료  ");
	
	while (1)
	{
		int n = key_control();
		switch (n)
		{
			case UP:
			{
				if (y > 16)
				{
					gotoxy(x - 2, y);
					printf(" ");
					gotoxy(x - 2, y-2);
					printf(">");
					y -= 2;
				}
				break;
			}
			case DOWN:
			{
				if (y < 20)
				{
					gotoxy(x - 2, y);
					printf(" ");
					gotoxy(x - 2, y+2);
					printf(">");
					y += 2;
				}
				break;
			}
			case ENTER:
			{
				return y - 16;  // 0 2 4 중 하나를 리턴해줌
			}
		}
	}
}

void info_draw(void)
{
	system("cls");
	printf("not yet");
	
	while (1)
	{
		if (key_control() == ENTER)
		{
			break;
		}
	}
}