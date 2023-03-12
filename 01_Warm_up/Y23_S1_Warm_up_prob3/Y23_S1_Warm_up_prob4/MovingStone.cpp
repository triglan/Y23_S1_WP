#pragma warning(disable:4996)

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <Windows.h>
#include <conio.h>


using namespace std;

#define ROW 3
#define COL 3

#define BLANK 0
#define OStone 1
#define XStone 2
#define HStone 3
#define AStone 4
#define SStone 5

int board[COL][ROW] = { 0 };

typedef struct{
	int x, y;
	char stone;
	bool overlapped;
}player;

player p1;
player p2;

int player1Turn = true;

char player1Input = 0;
char player2Input = 0;

void printBoard();
void randomStone();
void rand1PStone();
void rand2PStone();
void clearStone();
void crashP1Stone();
void crashP2Stone();

int main()
{
	clearStone();
	printBoard();

	char key = 0;
	while (true)
	{
		if (player1Turn == true)
		{
			if (kbhit())
			{
				key = getch();
				switch (key)
				{
				case 'w':
					p1.y -= 1;
					player1Turn = false;

					crashP1Stone();
					
					break;
				case 's':
					p1.y += 1;
					player1Turn = false;

					crashP1Stone();
					
					break;
				case 'a':
					p1.x -= 1;
					player1Turn = false;

					crashP1Stone();
					
					break;
				case 'd':
					p1.x += 1;
					player1Turn = false;

					crashP1Stone();
					
					break;

				case 'e':
					clearStone();

					break;

				case 'q':
					return 0;

				default:
					break;
				}
				if (p1.x < 0)
				{
					rand1PStone();
					p1.x = ROW - 1;
				}
				if (p1.x >= ROW)
				{
					rand1PStone();
					p1.x = 0;
				}
				if (p1.y < 0)
				{
					rand1PStone();
					p1.y = COL - 1;
				}

				if (p1.y >= COL)
				{
					rand1PStone();
					p1.y = 0;
				}
			}
		}
		else
		{
			if (kbhit())
			{
				key = getch();
				switch (key)
				{
				case 'i':
					p2.y -= 1;
					player1Turn = true;

					crashP2Stone();

					break;
				case 'k':
					p2.y += 1;
					player1Turn = true;

					crashP2Stone();

					break;
				case 'j':
					p2.x -= 1;
					player1Turn = true;

					crashP2Stone();

					break;
				case 'l':
					p2.x += 1;
					player1Turn = true;

					crashP2Stone();

					break;

				case 'e':
					clearStone();

					break;

				case 'q':
					return 0;

				default:
					break;
				}
				if (p2.x < 0)
				{
					p2.x = ROW - 1;
					rand2PStone();
				}
				if (p2.x >= ROW)
				{
					p2.x = 0;
					rand2PStone();
				}
				if (p2.y < 0)
				{
					p2.y = COL - 1;
					rand2PStone();
				}
				if (p2.y >= COL)
				{
					p2.y = 0;
					rand2PStone();
				}
			}

		}
			key = 0;
			std::system("cls");
			printBoard();
			std::cout << endl << "프로그램 리셋 : e" << endl << "나가기 : q";
			Sleep(50);
	}
	return 0;
}
void printBoard()
{
	for (int y = 0; y < COL; y++)
	{
		std::cout << "-----------------------------------------" << std::endl;
		for (int x = 0; x < ROW; x++)
		{
			if (y == p1.y && x == p1.x && p1.overlapped == false)
				std::cout << "| " << p1.stone << " ";
			else if (y == p2.y && x == p2.x && p2.overlapped == false)
				std::cout << "| " << p2.stone << " ";
			else //(board[y][x] == BLANK)
					std::cout << "|   ";
		}
		std::cout << "|   " << std::endl;
	}

	std::cout << "-----------------------------------------" << std::endl;
}

void clearStone()
{
	randomStone();	//돌에 입력

	p1.x = 0;
	p1.y = 0;

	p2.x = ROW - 1;	//가로 행
	p2.y = COL - 1;	//세로 열

	p1.overlapped = false;
	p2.overlapped = false;
}

void randomStone()
{
	rand1PStone();
	rand2PStone();
}

void rand1PStone()
{
	int randStone = 0;
	while (true)
	{
		randStone = rand() % 5 + 1;
		if (randStone == OStone && 'o' != p2.stone)
		{
			p1.stone = 'o';
			break;
		}
		else if (randStone == XStone && 'x' != p2.stone)
		{
			p1.stone = 'x';
			break;
		}
		else if (randStone == HStone && '#' != p2.stone)
		{
			p1.stone = '#';
			break;
		}
		else if (randStone == AStone && '@' != p2.stone)
		{
			p1.stone = '@';
			break;
		}
		else if (randStone == SStone && '*' != p2.stone)
		{
			p1.stone = '*';
			break;
		}
	}
}

void rand2PStone()
{
	int randStone = 0;
	while (true)
	{
		randStone = rand() % 5 + 1;
		if (randStone == OStone && 'o' != p1.stone)
		{
			p2.stone = 'o';
			break;
		}
		else if (randStone == XStone && 'x' != p1.stone)
		{
			p2.stone = 'x';
			break;
		}
		else if (randStone == HStone && '#' != p1.stone)
		{
			p2.stone = '#';
			break;
		}
		else if (randStone == AStone && '@' != p1.stone)
		{
			p2.stone = '@';
			break;
		}
		else if (randStone == SStone && '*' != p1.stone)
		{
			p2.stone = '*';
			break;
		}
	}
}

void crashP1Stone()
{
	if(p1.y == p2.y && p1.x == p2.x)
	{//움직인 돌의 모양이 나타나고 비프소리를 내고 다음 돌이 움직이면 바뀐 모양으로
		p2.overlapped = true;	//2p 오버랩이 켜져서 2p 그림은 안그려짐
		Beep(1000, 100);			//Beep 소리
	}
	if (p1.overlapped == true)
	{
		rand1PStone();
		p1.overlapped = false;
	}
}

void crashP2Stone()
{
	if (p1.y == p2.y && p1.x == p2.x)
	{//움직인 돌의 모양이 나타나고 비프소리를 내고 다음 돌이 움직이면 바뀐 모양으로
		p1.overlapped = true;	//2p 오버랩이 켜져서 2p 그림은 안그려짐
		Beep(1000, 100);			//Beep 소리
	}
	if (p2.overlapped == true)
	{
		rand2PStone();
		p2.overlapped = false;
	}
}