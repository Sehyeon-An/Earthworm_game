#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define LEFT 75 // ����Ű ����
#define RIGHT 77 // ����Ű ������
#define UP 72 // ����Ű ����
#define DOWN 80 // ����Ű �Ʒ���
#define ENTER 13 // ����Ű (Ȯ�ι�ư)
#define TOTAL 1823 // �׵θ� ���� ����ǥ ũ��  1823 = (y)*76 + x (y�ִ밡 75, x�ִ밡 23) 
#define MAP 1725 // �������� ���� ��ġ ��ǥ ũ�� 1725 =75*23

int prey_x;
int prey_y;

void init(void); // �ܼ�â�� ũ��� Ŀ��
void title_draw(void); // �ʱ� ȭ�� ����
int menu_draw(void); // �޴��� �׸��� �Լ�
int key_control(void); // Ű �� ��ȯ �Լ�
void gotoxy(int x, int y); // Ŀ�� ��ǥ �Լ�
void info_draw(void); // ���� ��� ����Լ�
void game_level(void); // ������ �̵��ӵ� ���� �Լ�
void game_background(void); // ���� ��׶��� ���� �Լ�(���� 51/���� 26)
int select_level();
int body_number;
int key; // Ű����� ���� �Է¹��� ��
int speed = 0; //������ ���ǵ� ����(Sleep�Լ� �Ķ����)

unsigned char total_size[TOTAL];
// �浹�� �����ϱ� ���� �ʿ��� �迭 
// �����ϸ� '1' �������� ������ '0'
unsigned int head_tail_remove[MAP];
//  head_point�� tail_point�� �����ͷ� ����ϸ� �ش� ��ġ���� �����. 

int head_point;
//���̸� ������ 1++ ,�����Ͱ� ����Ű�� �迭 ���� ���̸� ���� ����� ��ġ�� ���. 
int tail_point;
//�������� ������ ��Ÿ���� �������� �������ֱ� ���� ������
//�����̰� �����϶����� point_tail�� ����Ű�� �κп� ����� ���� ��ǥ

int main(void)
{
	int menu_code;
	int x;//���� �������� ��ġ
	int y;// ���� �������� ��ġ
	int save_x; // �������� ���븦 �������ֱ� ���� �ӽ� ���� ����
	int save_y;
	unsigned char chr; // ����Ű�� Ű���� �ޱ����� ����

	init();
	while (1)
	{

		save_x = 3;
		save_y = 2;
		head_point = 1;
		tail_point = 0;
		body_number = 1;
		chr = 99;
		memset(total_size, 0, TOTAL);
		memset(head_tail_remove, 0, MAP);
		head_tail_remove[0] = 76*2+3; // �ʱ� save_x =3 save_y =2�� �ϱ� ����. 
		title_draw();
		menu_code = menu_draw();

		if (menu_code == 0) //���� ����
		{
			//printf("11/16 ��ȴ� ���ϴ� ^^7");
			game_level();

		}
		else if (menu_code == 2) // ���� ����
		{
			info_draw();
		}
		else if (menu_code == 4) // ���� ����
		{
			break;
		}
		else menu_code = 5;
		system("cls");
		game_background();
		prey_x = (rand() % 35) * 2 + 3;
		prey_y = (rand() % 22) + 2;
		gotoxy(prey_x, prey_y);
		printf("��");
		x = 3;  // �������� ���� ���� ��ǥ�� ��Ÿ��
		y = 2;
		gotoxy(x, y);
		printf("��");
		while (1) {
			if (kbhit() != 0) {  //�ƹ�Ű�� �Է¹޾����� if���� ������
				chr = getch();
				if (chr == 0 || chr == 0xe0) {
					chr = getch();
				}
			}
			if (chr == UP) { //����Ű '��' �Է¹�����
				y -= 1;
				if (y < 2) {
					system("cls"); // ȭ���� ������ �����
					gotoxy(30, 10);
					printf("GAME OVER\n");
					break;
				}
			}
			else if (chr == DOWN) { //����Ű '��' �Է¹�����
				y += 1;
				if (y > 23) {
					system("cls");
					gotoxy(30, 10);
					printf("GAME OVER\n");
					break;
				}
			}
			else if (chr == LEFT) { //����Ű '��' �Է¹�����
				x -= 2; // �׸�� Ư������(2byte)�̹Ƿ� ���δ� 2ĭ�� �̵��ؾ���
				if (x < 3) {
					system("cls");
					gotoxy(30, 10);
					printf("GAME OVER\n");
					break;
				}
			}
			else if (chr == RIGHT) { //����Ű '��' �Է¹�����
				x += 2;
				if (x > 75) {
					system("cls");
					gotoxy(30, 10);
					printf("GAME OVER\n");
					break;
				}
			}

			if (x == prey_x && y == prey_y)
			{
				head_tail_remove[head_point] = (y) * 76 + x; // �������� ���븦 ����ǥ������ �߰�
				head_point++;

				total_size[(y) * 76 + x] = 1; //���� ��ǥ �߰�(1�� ������ �ִٴ� ǥ��, 0�� ������ ���ٴ� ǥ��)
				body_number++;

				prey_x = (rand() % 35) * 2 + 3;
				prey_y = (rand() % 22) + 2;
				gotoxy(prey_x, prey_y);
				printf("��");

				continue;
			}
				save_y = head_tail_remove[tail_point] / 76;  //�ӽ�����
				save_x = head_tail_remove[tail_point] % 76;
				//if (save_x == 0)save_x = 75;
				gotoxy(save_x, save_y);
				printf("%c%c", 0x00, 0x00);
				total_size[head_tail_remove[tail_point]] = 0; //�����̰� ������ ��ǥ�� ���� �������� �����Ƿ� ������ǥ���� ����
				tail_point++;
				//if (point_tail >= 1656)point_tail = 0;

				//������ �Ӹ��� ���� �������� ������ �Ӹ��� ������ �׷��ֱ� ���� �ڵ���
				head_tail_remove[head_point] = (y) * 76 + x;
				if (total_size[head_tail_remove[head_point]] == 0) { //������ �Ӹ��� ���� ���� ������ ������ ���� ���
					total_size[head_tail_remove[head_point]] = 1;
				}
				else {     //������ �Ӹ��� ������ǥ�� ������ ����, gameover��
					system("cls");
					gotoxy(30, 10);
					printf("GAME OVER\n");
					break;

				}
				head_point++;
				//if (head_point >= 1656)point_head = 0;


				gotoxy(x, y);
				printf("��"); //������ �Ӹ��� �׸���


				Sleep(speed); // ������ ���ǵ� ����
		}
	}

	gotoxy(28, 24);
	printf("���� ����!");
	_getch();

	return 0;

}

void init(void) // �ܼ�â�� ũ��� Ŀ�� 
{

	system("mode con cols=100 lines=35 | title Escape Game"); // �ӽ� ũ��
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

}

void gotoxy(int x, int y)
{
	//HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Pos = { x - 1,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}


void title_draw(void) // Ÿ��Ʋ �׸���
{
	printf("\n\n");
	printf("    _____    _    ____ _____ _   ___        _____  ____  __  __ \n");
	printf("   | ____|  / \\  |  _ \\_   _| | | \\ \\      / / _ \\|  _ \\|  \\/  |\n");
	printf("   |  _|   / _ \\ | |_) || | | |_| |\\ \\ /\\ / / | | | |_) | |\\/| |\n");
	printf("   | |___ / ___ \\|  _ < | | |  _  | \\ V  V /| |_| |  _ <| |  | |\n");
	printf("   |_____/_/   \\_\\_| \\_\\|_| |_| |_|  \\_/\\_/  \\___/|_| \\_\\_|  |_|\n\n");
	printf("                     ____    _    __  __ _____                  \n");
	printf("                    / ___|  / \\  |  \\/  | ____|                 \n");
	printf("                   | |  _  / _ \\ | |\\/| |  _|                   \n");
	printf("                   | |_| |/ ___ \\| |  | | |___                  \n");
	printf("                    \\____/_/   \\_\\_|  |_|_____|                 \n");

}

int key_control(void) // Ű���� �޴��Լ�
{
	key = 0; // Ű���� �ʱ�ȭ
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

int menu_draw(void) // �޴��� �׸��� �Լ�
{
	int x = 28;
	int y = 16;

	gotoxy(x - 2, y);
	printf("> ���� ����");
	gotoxy(x, y + 2);
	printf("���� ���");
	gotoxy(x, y + 4);
	printf("  ����  ");

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
				gotoxy(x - 2, y - 2);
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
				gotoxy(x - 2, y + 2);
				printf(">");
				y += 2;
			}
			break;
		}
		case ENTER:
		{
			return y - 16;  // 0 2 4 �� �ϳ��� ��������
		}
		}
	}
}

void info_draw(void) // �������� 
{
	system("cls");
	gotoxy(1, 3);
	printf("                              [��Ģ]\n\n");
	printf("    * �����̴� ���� �Ӹ��� ���ϰ� �ִ� �������� ��� �̵��մϴ�.\n");
	printf("      �÷��̾��� �������� �Ӹ��� ���� ������ �ٲܼ� �ֽ��ϴ�.\n");
	printf("    * �����̴� ���̳� �ڽ��� �� �Ϻο� ������ �׽��ϴ�.\n");
	printf("    * �����̴� ���̸� ���������� ���� ������ϴ� \n");
	printf("    * �������� ���̸� �÷�������!!\n\n\n\n");
	printf("                            [���� ���]\n\n");
	printf("    * [��] - �������� ���� ������ �������� �ٲ� �� �ֽ��ϴ�. \n");
	printf("    * [��] - �������� ���� ������ ���������� �ٲ� �� �ֽ��ϴ�. \n");
	printf("    * [��] - �������� ���� ������ �������� �ٲ� �� �ֽ��ϴ�. \n");
	printf("    * [��] - �������� ���� ������ �Ʒ������� �ٲ� �� �ֽ��ϴ�. \n\n\n\n");
	printf("    * Enter - ������  \n");


	while (1) // ENTER�� �Է¹����� ����ȭ������ ���ư��ϴ�.
	{
		if (key_control() == ENTER)
		{
			break;
		}
	}
}

void game_level(void) // ������ ���̵� ����
{
	int n = 0;
	system("cls");
	gotoxy(1, 1);
	printf("\n\n                          [���̵� ����]\n\n");
	printf("\n\n    * ������ ���̵��� �����ϰ� EnterŰ�� ��������. (1~5)\n\n");
	printf("    * ���̵��� �ö󰥼��� �������� �̵� �ӵ��� �����մϴ�!! \n\n");
	n = select_level();
	switch (n)
	{
	case 0:
		speed = 200;
		printf("0");
		break;
	case 5:
		speed = 175;
		printf("5");
		break;
	case 10:
		speed = 150;
		break;
	case 15:
		speed = 125;
		break;
	case 20:
		speed = 100;
		break;
	default:
		speed = 150;
		break;
	}
	n = 5;
	system("cls");
}

void game_background(void) // �������� ���� ���̴� 75,���� ���̴� 23
{
	system("cls");
	int i;

	gotoxy(1, 1);
	printf("��������������������-��������������������");
	for (int i = 2; i <= 24; i++)
	{
		gotoxy(1, i);
		printf("��");
	}
	for (int j = 2; j <= 24; j++)
	{
		gotoxy(76, j);
		printf("��");
	}
	gotoxy(1, 25);
	printf("��������������������-��������������������");
	//scanf_s("%d", &i); //  �׳� ȭ�� ������Ű����.....

}
int select_level()
{
	int x = 19;
	int y = 15;

	gotoxy(x, y);
	printf("���̵� :��   ��   ��   ��   ��");
	x += 8; // x = 27
	y += 2; // y = 16
	gotoxy(x, y);
	printf("��");
	while (1)
	{
		int n = key_control();
		switch (n)
		{
		case RIGHT:
		{
			if (x < 47)
			{
				gotoxy(x, y);
				printf(" ");
				gotoxy(x + 1, y);
				printf(" ");
				gotoxy(x + 5, y);
				printf("��");
				x += 5;
			}
			break;
		}
		case LEFT:
		{
			if (x > 28)
			{
				gotoxy(x, y);
				printf(" ");
				gotoxy(x + 1, y);
				printf(" ");
				gotoxy(x - 5, y);
				printf("��");
				x -= 5;
			}
			break;
		}
		case ENTER:
		{
			return x - 27; // 0,5,10,15,20,25 ����
		}
		}
	}
}