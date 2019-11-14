#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define LEFT 75 // ����Ű ����
#define RIGHT 77 // ����Ű ������
#define UP 72 // ����Ű ����
#define DOWN 80 // ����Ű �Ʒ���
#define SPACE 32 // 

void init(void);
void title_draw(void);

int key; // Ű����� ���� �Է¹��� ��

int main(void)
{
	init();
	title_draw();
}

void init(void) // �ܼ�â�� ũ�� �� Ŀ�� 
{
	system("mode con cols=70 lines=35 | title Earthworm_game");

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


void title_draw(void) // Ÿ��Ʋ �׸���
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
