#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#define ADD 1
#define SUB 2
#define MUL 3
#define DIV 4

using namespace std;

int oper[4] = { 0 };

int Operating(int operate, int a, int b);

vector <int> v;

int main()
{
	//벡터에 랜덤 숫자
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 4; i++)
	{
		int random = rand() % 4 + 1;
		v.push_back(random);
	}

	int num[5] = { 0 };
	
	//벡터 출력 예제
	for (int i = 0; i < v.size(); i++)
	{
		cout << v.at(i) << " ";
	}
	cout << endl;


	cout << "a, b, c, d, e의 값을 입력해 주세요 : ";
	while (true)
	{
		std::cin >> num[0] >> num[1] >> num[2] >> num[3] >> num[4];
		if (num[0] > 0 && num[0] < 100 && num[1]>0 && num[1] < 100 && num[2]>0 && num[2] < 100 && num[3]>0 && num[3] < 100 && num[4]>0 && num[4] < 100)
			break;
		else
			std::cout << "잘못된 값, 다시 입력해 주세요." << std::endl;
	}

	int result = 0;
	int order = 0;
	while (true)
	{
		cout << "연산자 : " << oper[0] << oper[1] << oper[2] << oper[3] << endl;
		cout << "명령어를 입력해 주세요(1, 2, 3, 4) : ";
		cin >> order;
		switch (order)
		{
		case 1:

			for (int i = 0; i < 4; i++)
			{//곱셈 나눗셈 먼저
				result = 0;
				if (oper[i] == 3 || oper[i] == 4)
				{//곱셈이나 나눗셈이면 v[i] v[i+1]을 연산해 v[i]에 넣고 한칸 씩 땡겨서 맨 뒤 벡터는 삭제한다
					v.at(i) = Operating(oper[i], v.at(i), v.at(i + 1));
					for (int push = i + 1; push < 4; push++)
					{
						v.at(push) = push + 1;
					}
				}
			}

			break;

		case 2:
			break;

		case 3:
			break;

		case 4:
			break;

		case'q':
			break;

		default:
			break;
		}
	}
}

int Operating(int operate, int a, int b)
{
	if (operate == ADD)
		a + b;
	else if (operate == SUB)
		a - b;
	else if (operate == MUL)
		a* b;
	else if (operate == DIV)
		a / b;
	else
		cout << "OPERATING_ERROR" << endl;
	return 0;
}