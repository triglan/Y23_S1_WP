#include <iostream>

#define COL 5		//가로줄 행
#define ROW 4		//세로줄 열
#define MAXCOUNT 50
int num[ROW][COL];

using namespace std;


//2차원 배열 오름차순 정렬
void ascend();

int main()
{
	//랜덤값 삽입
	for (int i = 0; i < COL * ROW; i++)
	{
		num[i / ROW][i % COL] = rand() % MAXCOUNT + 1;
		for (int j = 0; j < i; j++)
		{
			if (num[i / ROW][i % COL] == num[j / ROW][j % COL]) {
				i--;
				break;
			}
		}
	}


	for (int i = 0; i < ROW; i++)//세로줄
	{
		for (int j = 0; j < COL; j++)//가로줄
		{
			std::cout << num[i][j] << " ";
		}
		std::cout << endl;
	}

	char input;

	while (true)
	{
		std::cout << "명령어 : ";
		std::cin >> input;

		switch (input)
		{
		case 'a':
			ascend();

		default:
			break;
		}
	}
	

}


void ascend()
{
	int temparr[COL * ROW] = { 0 };
	int multiple = ROW * COL;


	//temparr 대입
	for (int i = 0; i < ROW - 1; i++)//세로줄
	{
		for (int j = 0; j < COL - 1; j++)//가로줄
		{
			temparr[i * j + j] = num[i][j];
		}
	}

	//temparr 정렬
	int temp = 0;
	for (int i = 0; i < multiple - 1; i++)
	{
		for (int j = 0; j < multiple - 1; j++)
		{
			if (temparr[i] < temparr[j])	// 오른쪽 값이 왼쪽보다 크면 서로 위치 바꾸기
			{
				temp = temparr[i];
				temparr[i] = temparr[j];
				temparr[j] = temp;
			}
		}
	}

	//정렬값 원본에 삽입
	for (int i = 0; i < ROW; i++)//세로줄
	{
		for (int j = 0; j < COL; j++)//가로줄
		{
			num[i][j] = temparr[i * j + j];
		}
	}

	//출력
	for (int i = 0; i < ROW; i++)//세로줄
	{
		for (int j = 0; j < COL; j++)//가로줄
		{
			std::cout << num[i][j] << " ";
		}
		std::cout << endl;
	}
}