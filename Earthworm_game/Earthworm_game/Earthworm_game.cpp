
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define LEFT 75 // 방향키 왼쪽
#define RIGHT 77 // 방향키 오른쪽
#define UP 72 // 방향키 위쪽
#define DOWN 80 // 방향키 아래쪽
#define ENTER 13 // 엔터키 (확인버튼)
#define TOTAL 1583 // 테두리 포함 맵좌표 크기  1583 = (y)*66 + x (y최대가 65, x최대가 23) 
#define MAP 1495 // 지렁이의 몸통 위치 좌표 크기 1495 =65*23
#define COL 65
#define ROW  23

//int prey_x;
//int prey_y;

int rand_x[3] = { 0 }; //난수생성하여 gotoxy로 커서 이동시켜서 먹이 놓기 위한것
int rand_y[3] = { 0 };
int buffer_x[3] = { 0 };
int buffer_y[3] = { 0 };

void init(void); // 콘솔창의 크기와 커서
void title_draw(void); // 초기 화면 구현
int menu_draw(void); // 메뉴를 그리는 함수
int key_control(void); // 키 값 반환 함수
void gotoxy(int x, int y); // 커서 좌표 함수
void info_draw(void); // 게임 방법 출력함수
void game_level(void); // 지렁이 이동속도 조절 함수
void game_background(void); // 게임 백그라운드 구현 함수
void eat_star(void); // 먹이를 먹는 함수
int select_level(); // 게임 레벨 선택 함수
void scoreRecord(); // 점수
void game_loop(void); //게임루프
void game_over(void); // 게임 오버 함수
int body_number;
int key; // 키보드로 부터 입력받은 값
int speed = 0; //지렁이 스피드 조절(Sleep함수 파라미터)
int playing; // 플레이 상태 1=플레이 0=플레이안함
int len_earthworm = 0;
int game_score = 0;
int best_score = 0;

unsigned char total_size[ROW + 1][COL + 1];
// 충돌을 감지하기 위해 필요한 배열 
// 존재하면 '1' 존재하지 않으면 '0'
unsigned int head_tail_remove[COL * ROW];
//  head_point와 tail_point를 포인터로 사용하며 해당 위치값을 기록함. 

int head_point;
//먹이를 먹으면 1++ ,포인터가 가리키는 배열 값에 먹이를 먹은 당시의 위치를 기록. 
int tail_point;
//지렁이의 꼬리를 나타내며 지나가면 삭제해주기 위한 포인터
//지렁이가 움직일때마다 point_tail이 가리키는 부분에 저장된 맵의 좌표

int main(void)
{
	int menu_code = 10;
	int playing = 1;

	init();
	while (1)
	{

		system("color 04");
		title_draw();
		menu_code = menu_draw();

		if (menu_code == 0) //게임 시작
		{
			game_level();
			game_loop();

		}
		else if (menu_code == 2) // 게임 정보
		{
			info_draw();
		}
		else if (menu_code == 4) // 게임 종료
		{
			break;
		}
		else menu_code = 5;
	}

}


void init(void) // 콘솔창의 크기와 커서 
{

	system("mode con cols=90 lines=23 | title Earthworm game");
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
	FILE* file;
	fopen_s(&file, "best_score.dat", "rt");
	if (file == 0)
	{
		best_score = 0;
	}
	else
	{
		fscanf_s(file, "%d", &best_score);
		fclose(file);
	}
}


void title_draw(void) // 타이틀 그리기
{
	system("cls");
	printf("\n\n");
	printf("               _____    _    ____ _____ _   ___        _____  ____  __  __ \n");
	printf("              | ____|  / \\  |  _ \\_   _| | | \\ \\      / / _ \\|  _ \\|  \\/  |\n");
	printf("              |  _|   / _ \\ | |_) || | | |_| |\\ \\ /\\ / / | | | |_) | |\\/| |\n");
	printf("              | |___ / ___ \\|  _ < | | |  _  | \\ V  V /| |_| |  _ <| |  | |\n");
	printf("              |_____/_/   \\_\\_| \\_\\|_| |_| |_|  \\_/\\_/  \\___/|_| \\_\\_|  |_|\n\n");
	printf("                                ____    _    __  __ _____                  \n");
	printf("                               / ___|  / \\  |  \\/  | ____|                 \n");
	printf("                              | |  _  / _ \\ | |\\/| |  _|                   \n");
	printf("                              | |_| |/ ___ \\| |  | | |___                  \n");
	printf("                               \\____/_/   \\_\\_|  |_|_____|                 \n");

}

int key_control(void) // 키값을 받는함수
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
	int x = 40;
	int y = 16;

	gotoxy(x - 2, y);
	printf("> 게임 시작");
	gotoxy(x, y + 2);
	printf("게임 방법");
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
			return y - 16;  // 0 2 4 중 하나를 리턴해줌
		}
		}
	}
}

void info_draw(void) // 게임정보 
{
	system("cls");
	gotoxy(1, 3);
	printf("                                      [규칙]\n\n");
	printf("            * 지렁이는 현재 머리가 향하고 있는 방향으로 계속 이동합니다.\n");
	printf("              플레이어의 조작으로 머리의 진행 방향을 바꿀수 있습니다.\n");
	printf("            * 지렁이는 벽이나 자신의 몸 일부에 닿으면 죽습니다.\n");
	printf("            * 지렁이는 먹이를 먹을때마다 몸이 길어집니다 \n");
	printf("            * 지렁이의 길이를 늘려보세요!!\n\n\n\n");
	printf("                                    [조작 방법]\n\n");
	printf("            * [↑] - 지렁이의 진행 방향을 위쪽으로 바꿀 수 있습니다. \n");
	printf("            * [→] - 지렁이의 진행 방향을 오른쪽으로 바꿀 수 있습니다. \n");
	printf("            * [←] - 지렁이의 진행 방향을 왼쪽으로 바꿀 수 있습니다. \n");
	printf("            * [↓] - 지렁이의 진행 방향을 아래쪽으로 바꿀 수 있습니다. \n\n\n\n");
	printf("            * Enter - 나가기  \n");


	while (1) // ENTER을 입력받으면 메인화면으로 돌아갑니다.
	{
		if (key_control() == ENTER)
		{
			break;
		}
	}
}

void game_level(void) // 게임의 난이도 설정
{
	int n = 0;
	system("cls");
	gotoxy(1, 1);
	printf("\n\n                                      [난이도 선택]\n\n");
	printf("\n\n                * 게임의 난이도를 선택하고 Enter키를 누르세요. (1~5)\n\n");
	printf("                * 난이도가 올라갈수록 지렁이의 이동 속도가 증가합니다!! \n\n");
	n = select_level();
	switch (n)
	{
	case 0:
		speed = 200;
		break;
	case 5:
		speed = 175;
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

void game_background(void) // 게임판의 가로 길이는 75,세로 길이는 23
{
	system("cls");

	gotoxy(1, 1);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	for (int i = 2; i <= 23; i++)
	{
		gotoxy(1, i);
		printf("■");
	}
	for (int j = 2; j <= 23; j++)
	{
		gotoxy(65, j);
		printf("■");
	}
	gotoxy(1, 23);
	printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");

}
int select_level()
{
	int x = 27;
	int y = 15;

	gotoxy(x, y);
	printf("난이도 :①   ②   ③   ④   ⑤");
	x += 8; // x = 35
	y += 2; // y = 16
	gotoxy(x, y);
	printf("▲");
	while (1)
	{
		int n = key_control();
		switch (n)
		{
		case RIGHT:
		{
			if (x < 55)
			{
				gotoxy(x, y);
				printf(" ");
				gotoxy(x + 1, y);
				printf(" ");
				gotoxy(x + 5, y);
				printf("▲");
				x += 5;
			}
			break;
		}
		case LEFT:
		{
			if (x > 36)
			{
				gotoxy(x, y);
				printf(" ");
				gotoxy(x + 1, y);
				printf(" ");
				gotoxy(x - 5, y);
				printf("▲");
				x -= 5;
			}
			break;
		}
		case ENTER:
		{
			return x - 35; // 0,5,10,15,20,25 리턴
		}
		}
	}
}

void eat_star() {

	for (int a = 0; a < 3; a++) {
		buffer_x[a] = rand_x[a];
		buffer_y[a] = rand_y[a];
	}
	//prey_num = (rand() % 2 + 2);
	for (int count = 0; count < 3; count++) {
		rand_x[count] = ((rand() % 28)) * 2 + 3; //난수생성하여 먹잇감의 좌표를 얻음
		rand_y[count] = (rand() % 21) + 2;
		gotoxy(rand_x[count], rand_y[count]);
		printf("★");

	}
}

void scoreRecord() {
	len_earthworm = body_number;
	gotoxy(68, 8);
	printf("Length of 지렁이 : %d\n", len_earthworm);
	game_score = (body_number - 1) * (21000 / speed);
	gotoxy(68, 13);
	printf("최고 점수: %d\n", best_score);
	gotoxy(73, 18);
	printf("점수 : %d\n", game_score);
}

void game_loop(void)
{

	int x;//현재 지렁이의 위치
	int y;// 현재 지렁이의 위치
	int save_x; // 지렁이의 자취를 삭제해주기 위해 임시 저장 변수
	int save_y;
	unsigned char chr; // 방향키의 키값을 받기위한 변수

	save_x = 3;
	save_y = 2;
	head_point = 1;
	tail_point = 0;
	body_number = 1;
	chr = 99;
	memset(total_size, 0, TOTAL);
	memset(head_tail_remove, 0, MAP);
	head_tail_remove[0] = 66 * 2 + 3; // 초기 save_x =3 save_y =2로 하기 위해. 
	system("cls");
	system("color 02");
	game_background();
	scoreRecord();
	eat_star();
	x = 3;  // 지렁이의 최초 시작 좌표를 나타냄
	y = 2;
	playing = 1;
	gotoxy(x, y);
	printf("◑");
	while (playing)
	{
		scoreRecord();
		if (_kbhit() != 0) {  //아무키나 입력받았을시 if문을 실행함
			chr = _getch();
			if (chr == 0 || chr == 0xe0) {
				chr = _getch();
			}
		}
		if (chr == UP) { //방향키 '상' 입력받을시
			y -= 1;
			if (y < 2)
			{
				game_over();
			}
		}
		else if (chr == DOWN) { //방향키 '하' 입력받을시
			y += 1;
			if (y > 22)
			{
				game_over();
			}
		}
		else if (chr == LEFT) { //방향키 '좌' 입력받을시
			x -= 2; // 네모는 특수문자(2byte)이므로 가로는 2칸씩 이동해야함
			if (x < 3)
			{
				game_over();
			}
		}
		else if (chr == RIGHT) { //방향키 '우' 입력받을시
			x += 2;
			if (x > 63)
			{
				game_over();
			}
		}

		if ((x == rand_x[0]) && (y == rand_y[0]) || (x == rand_x[1]) && (y == rand_y[1]) || (x == rand_x[2]) && (y == rand_y[2]) || (x == buffer_x[0]) && (y == buffer_y[0]) || (x == buffer_x[1]) && (y == buffer_y[1]) || (x == buffer_x[2]) && (y == buffer_y[2])) { // 먹이를 먹었을 경우 
		// 난수를 사용하여 새로운 먹이를 맵에 표현
			if ((body_number) % 3 == 2) {//2,5,8 ---
				eat_star();
			}

			head_tail_remove[head_point] = (y) * 66 + x; // 지렁이의 자취를 맵좌표값으로 추가
			head_point++;

			total_size[y][x] = 1; //몸통 좌표 추가(1이 몸통이 있다는 표시, 0이 몸통이 없다는 표시)
			body_number++;
			//scoreRecord();

			if (body_number % 5 == 0) { // 길이가 늘어나면 속도룰 증가시킴. 
				speed -= 25;
				if (speed < 40)speed = 40;
				//body_number = 0;
			}

			continue;
		}
		save_y = head_tail_remove[tail_point] / 66;  //임시저장
		save_x = head_tail_remove[tail_point] % 66;
		//if (save_x == 0)save_x = 75;
		gotoxy(save_x, save_y);
		printf("%c%c", 0x00, 0x00);
		total_size[save_y][save_x] = 0; //지렁이가 지나간 좌표는 몸이 존재하지 않으므로 몸통좌표에서 삭제
		tail_point++;
		//if (point_tail >= 1656)point_tail = 0;

		//지렁이 머리가 가는 방향으로 지렁이 머리를 새로이 그려넣기 위한 코드임
		head_tail_remove[head_point] = (y) * 66 + x;
		if (total_size[head_tail_remove[head_point] / 66][head_tail_remove[head_point] % 66] == 0) { //지렁이 머리가 있을 곳에 지렁이 몸통이 없을 경우
			total_size[head_tail_remove[head_point] / 66][head_tail_remove[head_point] % 66] = 1;
		}
		else {     //지렁이 머리와 몸통좌표가 겹쳤을 경우로, gameover임

			game_over();
		}
		head_point++;
		//if (head_point >= 1656)point_head = 0;


		gotoxy(x, y);
		printf("◐"); //지렁이 머리를 그린다


		Sleep(speed); // 게임의 스피드 조절
	}
}

void game_over(void)
{
	system("cls");
	int now_x = 30;
	int now_y = 8;

	if (game_score > best_score)
	{
		FILE* file;
		fopen_s(&file, "best_score.dat", "wt");

		fprintf(file, "%d", game_score);
		fclose(file);

		gotoxy(now_x, now_y);
		printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
		gotoxy(now_x, now_y + 1);
		printf("▤    ★★★ BEST SCORE! ★★★   ▤  ");
		gotoxy(now_x, now_y + 2);
		printf("▤   *-----------------------*    ▤");
		gotoxy(now_x, now_y + 3);
		printf("▤   |  G A M E  O V E R..   |    ▤");
		gotoxy(now_x, now_y + 4);
		printf("▤   *-----------------------*    ▤");
		gotoxy(now_x, now_y + 5);
		printf("▤   YOUR SCORE: %6d           ▤", game_score);
		gotoxy(now_x, now_y + 6);
		printf("▤                                ▤");
		gotoxy(now_x, now_y + 7);
		printf("▤  Press Enter key to restart..  ▤");
		gotoxy(now_x, now_y + 8);
		printf("▤                                ▤");
		gotoxy(now_x, now_y + 9);
		printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");


	}
	else
	{
		gotoxy(now_x, now_y);
		printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
		gotoxy(now_x, now_y + 1);
		printf("▤                                ▤");
		gotoxy(now_x, now_y + 2);
		printf("▤   *-----------------------*    ▤");
		gotoxy(now_x, now_y + 3);
		printf("▤   |  G A M E  O V E R..   |    ▤");
		gotoxy(now_x, now_y + 4);
		printf("▤   *-----------------------*    ▤");
		gotoxy(now_x, now_y + 5);
		printf("▤   YOUR SCORE: %6d           ▤", game_score);
		gotoxy(now_x, now_y + 6);
		printf("▤   BEST SCORE: %6d           ▤", best_score);
		gotoxy(now_x, now_y + 7);
		printf("▤  Press Enter key to restart..  ▤");
		gotoxy(now_x, now_y + 8);
		printf("▤                                ▤");
		gotoxy(now_x, now_y + 9);
		printf("▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤▤");
	}


	while (1) // Enter 키를 입력받으면 종료
	{
		if (key_control() == ENTER)
		{
			playing = 0;
			break;
		}
	}

}