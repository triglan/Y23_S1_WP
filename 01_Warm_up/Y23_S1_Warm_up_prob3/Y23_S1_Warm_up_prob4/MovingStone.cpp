#include <iostream>
#include <Windows.h>

#define ROW 10
#define COL 10

#define BLANK 0
#define OStone 1
#define XStone 2
#define HStone 3
#define AStone 4
#define SStone 5

int board[COL][ROW] = { 0 };


void printBoard();

int main()
{
	printBoard();
}

void printBoard()
{
	for (int y = 0; y < COL; y++)
	{
		std::cout << "--------------------------------------" << std::endl;
		for (int x = 0; x < ROW; x++)
		{
			if (board[y][x] == BLANK)
				std::cout << "|   ";
		}
		std::cout << std::endl;
	}
}