#include <iostream>
#include <cstdlib>
#include <ctime>

#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4

using namespace std;

int oper[4] = { 0 };

int Operating(int operate, int a, int b);
void PrintOperate(int oper);

int main()
{
	
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 4; i++)
	{
		oper[i] = rand() % 4 + 1;
	}

	int num[5] = { 0 };
	int temp[5] = { 0 };

	
	while (true)
	{
		num[0] = 0; 
		num[1] = 0;
		num[2] = 0;
		num[3] = 0;
		num[4] = 0;

		
		cout << "a, b, c, d, e의 값을 입력해 주세요 : ";
		std::cin >> num[0] >> num[1] >> num[2] >> num[3] >> num[4];
		if (num[0] > 0 && num[0] < 100 && num[1]>0 && num[1] < 100 && num[2]>0 && num[2] < 100 && num[3]>0 && num[3] < 100 && num[4]>0 && num[4] < 100)
			break;
		else
		{
			std::cout << "잘못된 값, 다시 입력해 주세요." << std::endl;
			cin.ignore();
			continue;
		}
	}
	cout << "연산자 : ";

	oper[0] = ADD;
	oper[1] = DIV;
	oper[2] = SUB;
	oper[3] = MUL;

	PrintOperate(oper[0]);
	PrintOperate(oper[1]);
	PrintOperate(oper[2]);
	PrintOperate(oper[3]);
	cout << endl;
	int result = 0;
	char order = 0;
	bool quit = true;

	while (quit)
	{
		for (int i = 0; i < 5; i++)
		{
			temp[i] = num[i];
		}
		result = 0;

		cout << "명령어를 입력해 주세요(1, 2, 3, 4) : ";
		cin >> order;


		switch (order)
		{
		case '1':
			

		for (int i = 0; i < 4; i++)
		{//곱셈 나눗셈 먼저
			if (oper[i] == MUL || oper[i] == DIV)
			{
				temp[i + 1] = Operating(oper[i], temp[i], temp[i + 1]);
				temp[i] = 0;
			}
		}

		for (int i = 0; i < 3; i++)
		{//덧뺼셈
			//초기값 먼저 0이면 for루프 다돌아서 i++
			if (temp[i] != 0)
				result = temp[i];

			if (oper[i] == ADD)
			{//+이면
				while (true)
				{
					if (temp[i + 1] != 0)
					{//초기값 뒤 숫자가 0이 아니면
						result += temp[i + 1];
						break;
					}
					else if (oper[i] != SUB)//뺄셈이면
						break;
					else//0이면 i++로 0이 아닌 값을 찾을 때까지 검사
						i++;
				}
			}

			if (oper[i] == SUB)
			{//-이면
				while (true)
				{
					if (temp[i + 1] != 0)
					{//초기값 뒤 숫자가 0이 아니면
						result -= temp[i + 1];
						break;
					}
					else if (oper[i] != SUB)//뺄셈이면
						break;
					else//0이면 i++로 0이 아닌 값을 찾을 때까지 검사
						i++;
				}
			}

			i++;
		}
		cout << "Result : " << result << endl;
			break;

		case '2':
			//초기값 넣기
			result = temp[0];
			//앞에서부터 계산
			for (int i = 0; i < 4; i++)
			{
				if (oper[i] == ADD)
					result = result + temp[i + 1];
				else if (oper[i] == SUB)
					result = result - temp[i + 1];
				else if (oper[i] == MUL)
					result = result * temp[i + 1];
				else if (oper[i] == DIV)
					result = result / temp[i + 1];
				else
					cout << "OPERATING_ERROR" << endl;

			}
			cout << "Result : " << result << endl;
			break;

		case '3':
			//초기값 넣기
			result = temp[4];
			//뒤에서부터 계산
			for (int i = 3; i >= 0; i--)
			{
				if (oper[i] == ADD)
					result = result + temp[i];
				else if (oper[i] == SUB)
					result = result - temp[i];
				else if (oper[i] == MUL)
					result = result * temp[i];
				else if (oper[i] == DIV)
					result = result / temp[i];
				else
					cout << "OPERATING_ERROR" << endl;

			}
			cout << "Result : " << result << endl;
			break;

		case '4':

			cout << "a, b, c, d, e의 값을 입력해 주세요 : ";
			while (true)
			{
				cin.ignore();
				std::cin >> num[0] >> num[1] >> num[2] >> num[3] >> num[4];
				if (num[0] > 0 && num[0] < 100 && num[1]>0 && num[1] < 100 && num[2]>0 && num[2] < 100 && num[3]>0 && num[3] < 100 && num[4]>0 && num[4] < 100)
					break;
				else
				{
					std::cout << "잘못된 값, 다시 입력해 주세요." << std::endl;
					continue;
				}
			}
			cout << "연산자 : ";

			for (int i = 0; i < 4; i++)
			{
				oper[i] = rand() % 4 + 1;
			}

			PrintOperate(oper[0]);
			PrintOperate(oper[1]);
			PrintOperate(oper[2]);
			PrintOperate(oper[3]);

			cout << endl;

			break;

		case'q':
			quit = false;
			cin.ignore();
			return 0;

		default:
			std::cout << "잘못된 값, 다시 입력해 주세요." << std::endl;
			cin.ignore();
			break;
		}
	}
}

void PrintOperate(int oper)
{
	if (oper == ADD)
		cout << "+";
	if (oper == SUB)
		cout << "-";
	if (oper == MUL)
		cout << "*";
	if (oper == DIV)
		cout << "/";
}

int Operating(int operate, int a, int b)
{
	if (operate == ADD)
		return a + b;
	else if (operate == SUB)
		return a - b;
	else if (operate == MUL)
		return a * b;
	else if (operate == DIV)
		return a / b;
	else
		cout << "OPERATING_ERROR" << endl;
	return 0;
}