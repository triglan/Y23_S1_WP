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
	//���Ϳ� ���� ����
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 4; i++)
	{
		int random = rand() % 4 + 1;
		v.push_back(random);
	}

	int num[5] = { 0 };
	
	//���� ��� ����
	for (int i = 0; i < v.size(); i++)
	{
		cout << v.at(i) << " ";
	}
	cout << endl;


	cout << "a, b, c, d, e�� ���� �Է��� �ּ��� : ";
	while (true)
	{
		std::cin >> num[0] >> num[1] >> num[2] >> num[3] >> num[4];
		if (num[0] > 0 && num[0] < 100 && num[1]>0 && num[1] < 100 && num[2]>0 && num[2] < 100 && num[3]>0 && num[3] < 100 && num[4]>0 && num[4] < 100)
			break;
		else
			std::cout << "�߸��� ��, �ٽ� �Է��� �ּ���." << std::endl;
	}

	int result = 0;
	int order = 0;
	while (true)
	{
		cout << "������ : " << oper[0] << oper[1] << oper[2] << oper[3] << endl;
		cout << "��ɾ �Է��� �ּ���(1, 2, 3, 4) : ";
		cin >> order;
		switch (order)
		{
		case 1:

			for (int i = 0; i < 4; i++)
			{//���� ������ ����
				result = 0;
				if (oper[i] == 3 || oper[i] == 4)
				{//�����̳� �������̸� v[i] v[i+1]�� ������ v[i]�� �ְ� ��ĭ �� ���ܼ� �� �� ���ʹ� �����Ѵ�
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