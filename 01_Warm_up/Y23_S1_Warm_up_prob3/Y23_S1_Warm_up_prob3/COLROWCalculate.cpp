#include <iostream>

#define ROW 5		//가로줄 행
#define COL 4		//세로줄 열
#define MAXCOUNT 50

int num[COL][ROW];
int duplicateNum[COL][ROW];//임시저장

using namespace std;

bool bAscend = false;
bool bDescend = false;
bool bDubble = false;	
bool bMax = false;
bool bMin = false;
bool bFirstRow = false;
bool bRandomSort = false;
bool bRandomInput = false;

void makeFalse();
void dupNum(); //버퍼에 저장
void returnNum();//되돌리기
void swap(int& a, int& b);//스왑 함수

void ascend(); //2차원 배열 오름차순 정렬
void descend();
void even();
void odd();
void max();
void min();
void FirstRow();
void RandomSort();
void RandomInput();

int main()
{
	//랜덤값 삽입
	RandomInput();
	char input;

	while (true)
	{
		std::cout << "명령어 : ";
		std::cin >> input;

		switch (input)
		{
		case 'a':
			ascend();
			break;

		case 'd':
			descend();
			break;

		case 'e':
			even();
			break;

		case 'o':
			odd();
			break;

		case 'm':
			max();
			break;

		case 'n':
			min();
			break;

		case 'p':
			FirstRow();
			break;

		case 'r':
			RandomSort();
			break;

		case 's':
			RandomInput();
			break;

		case'q':
			return 0;

		default:
			break;
		}
	}
	
	return 0;
}

void makeFalse()
{
	bAscend = false;
	bDescend = false;
	bDubble = false;
	bMax = false;
	bMin = false;
	bFirstRow = false;
	bRandomSort = false;
	bRandomInput = false;
}

void dupNum()//버퍼
{
	for (int i = 0; i < COL; i++)//세로줄
	{
		for (int j = 0; j < ROW; j++)//가로줄
		{
			duplicateNum[i][j] = num[i][j];
		}
	}
}

void returnNum()//되돌리기
{
	for (int i = 0; i < COL; i++)//세로줄
	{
		for (int j = 0; j < ROW; j++)//가로줄
		{
			num[i][j] = duplicateNum[i][j];
		}
	}

	//출력
	for (int i = 0; i < COL; i++)//세로줄
	{
		for (int j = 0; j < ROW; j++)//가로줄
		{
			std::cout << num[i][j] << " ";
		}
		std::cout << endl;
	}
}

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}

void ascend()
{
	if (bAscend == true)
	{//한번 더 눌렀으면
		returnNum();
		bAscend = false;
		return;
	}

	makeFalse();
	bAscend = true;
	dupNum();//임시저장

	//행을 따라 오름차순
	for (int i = 0; i < COL * ROW; i++)
	{
		for (int j = 0; j < COL * ROW; j++)
		{
			if (num[i / ROW][i % ROW] < num[(j / ROW)][(j % ROW)])	//앞 숫자가 뒤보다 높을 때 바꿈
				swap(num[i / ROW][i % ROW], num[j / ROW][j % ROW]);
		}
	}

	//출력
	for (int i = 0; i < COL; i++)//세로줄
	{
		for (int j = 0; j < ROW; j++)//가로줄
		{
			std::cout << num[i][j] << " ";
		}
		std::cout << endl;
	}
	
}

void descend()
{
	if (bDescend == true)
	{//한번 더 눌렀으면
		returnNum();
		bDescend = false;
		return;
	}

	makeFalse();
	bDescend = true;
	dupNum();//임시저장

	//열을 따라 내림차순
	for (int repeat = 0; repeat < COL * ROW; repeat++)
	{
		for (int i = 0; i < COL * ROW; i++)
		{
			for (int j = 0; j < COL * ROW; j++)
			{
				if (i % ROW > j % ROW)
					if (num[i / ROW][i % ROW] < num[j / ROW][j % ROW])
						swap(num[i / ROW][i % ROW], num[j / ROW][j % ROW]);
				if (i % ROW == j % ROW)
					if (i / ROW < j / ROW)
					{
						if (num[i / ROW][i % ROW] < num[j / ROW][j % ROW])
							swap(num[i / ROW][i % ROW], num[j / ROW][j % ROW]);
					}
					else if (i / ROW > j / ROW)
						if (num[i / ROW][i % ROW] > num[j / ROW][j % ROW])
							swap(num[i / ROW][i % ROW], num[j / ROW][j % ROW]);
				if (i % ROW < j % ROW)
					if (num[i / ROW][i % ROW] > num[j / ROW][j % ROW])
						swap(num[i / ROW][i % ROW], num[j / ROW][j % ROW]);
			}
		}
	}
	

	//출력
	for (int i = 0; i < COL; i++)//세로줄
	{
		for (int j = 0; j < ROW; j++)//가로줄
		{
			std::cout << num[i][j] << " ";
		}
		std::cout << endl;
	}
}

void even()
{
	if (bDubble == true)
	{//한번 더 눌렀으면
		returnNum();
		bDubble = false;
		return;
	}

	makeFalse();
	bDubble = true;
	dupNum();//임시저장



	//출력
	for (int i = 0; i < COL; i++)//세로줄
	{
		for (int j = 0; j < ROW; j++)//가로줄
		{
			if(num[i][j] % 2 == 0)	//짝수면
				std::cout << num[i][j] << " ";
			else
				std::cout << "0" << " ";
		}
		std::cout << endl;
	}
}

void odd()
{
	if (bDubble == true)
	{//한번 더 눌렀으면
		returnNum();
		bDubble = false;
		return;
	}

	makeFalse();
	bDubble = true;
	dupNum();//임시저장



	//출력
	for (int i = 0; i < COL; i++)//세로줄
	{
		for (int j = 0; j < ROW; j++)//가로줄
		{
			if (num[i][j] % 2 == 1)	//홀수면
				std::cout << num[i][j] << " ";
			else
				std::cout << "0" << " ";
		}
		std::cout << endl;
	}
}

void max()
{
	if (bMax == true)
	{//한번 더 눌렀으면
		returnNum();
		bMax = false;
		return;
	}

	makeFalse();
	bMax = true;
	dupNum();//임시저장

	int Max = 0;

	for (int i = 0; i < COL; i++)//세로줄
	{
		for (int j = 0; j < ROW; j++)//가로줄
		{
			if (num[i][j] > Max)
				Max = num[i][j];
		}
	}

	for (int i = 0; i < COL; i++)//세로줄
	{
		for (int j = 0; j < ROW; j++)//가로줄
		{
			if(num[i][j] == Max)
				std::cout << num[i][j] << " ";
			else
				std::cout << "0  ";
		}
		std::cout << endl;
	}

}

void min()
{
	if (bMin == true)
	{//한번 더 눌렀으면
		returnNum();
		bMin = false;
		return;
	}

	makeFalse();
	bMin = true;
	dupNum();//임시저장

	int min = 5000;

	for (int i = 0; i < COL; i++)//세로줄
	{
		for (int j = 0; j < ROW; j++)//가로줄
		{
			if (num[i][j] < min)
				min = num[i][j];
		}
	}

	for (int i = 0; i < COL; i++)//세로줄
	{
		for (int j = 0; j < ROW; j++)//가로줄
		{
			if (num[i][j] == min)
				std::cout << num[i][j] << " ";
			else
				std::cout << "0  ";
		}
		std::cout << endl;
	}
}

void FirstRow()
{
	if (bFirstRow == true)
	{//한번 더 눌렀으면
		returnNum();
		bFirstRow = false;
		return;
	}

	makeFalse();
	bFirstRow = true;
	dupNum();//임시저장

	int FRow[COL] = { 0 };

	//1행에 저장
	for (int i = 0; i < COL; i++)//세로줄
	{
		for (int j = 0; j < ROW; j++)//가로줄
		{
			FRow[i] += num[i][j];
		}
	}

	//출력
	for (int i = 0; i < COL; i++)//세로줄
	{
		for (int j = 0; j < ROW; j++)//가로줄
		{
			if (j == 0)
				std::cout << FRow[i] << " ";
			else
				std::cout << num[i][j] << " ";
		}
		std::cout << endl;
	}
}

void RandomSort()
{
	if (bRandomSort == true)
	{//한번 더 눌렀으면
		returnNum();
		bRandomSort = false;
		return;
	}

	makeFalse();
	bRandomSort = true;
	dupNum();//임시저장

	int newRand = rand() % 2;
	int temp;

	for (int repeat = 0; repeat < COL * ROW; repeat++)
	{
		for (int i = 0; i < COL; i++)//세로줄
		{
			for (int j = 0; j < ROW; j++)//가로줄
			{
				newRand = rand() % 2;
				if (newRand == 1)	// newRand값이 1이면 서로 스왑 아니면 스왑x
				{
					temp = num[i / ROW][i % ROW];
					num[i / ROW][i % ROW] = num[j / ROW][j % ROW];
					num[j / ROW][j % ROW] = temp;
				}
			}
		}
	}

	//출력
	for (int i = 0; i < COL; i++)//세로줄
	{
		for (int j = 0; j < ROW; j++)//가로줄
		{
			std::cout << num[i][j] << " ";
		}
		std::cout << endl;
	}
}

void RandomInput()
{
	if (bRandomInput == true)
	{//한번 더 눌렀으면
		returnNum();
		bRandomInput = false;
		return;
	}

	makeFalse();
	bRandomInput = true;
	dupNum();//임시저장

	for (int i = 0; i < COL * ROW; i++)
	{
		num[i / ROW][i % ROW] = (rand() % MAXCOUNT) + 1;
		for (int j = 0; j < i; j++)
		{
			if (num[i / ROW][i % ROW] == num[j / ROW][j % ROW]) {
				i--;
				break;
			}
		}
	}

	for (int i = 0; i < COL; i++)//세로줄
	{
		for (int j = 0; j < ROW; j++)//가로줄
		{
			std::cout << num[i][j] << " ";
		}
		std::cout << endl;
	}
}

