#include <iostream>
#include <vector>
#include <algorithm>

#define INPUTNUM 10

using namespace std;

int main()
{
	int randNum[INPUTNUM] = { 0 };
	int input;

	std::cout << "����ڰ� �Է��� ���ں��� ���� ������ �� 30���� �ڵ����� ����ϴ� : ";
	cin >> input;

	for (int i = 0; i < INPUTNUM; i++)
	{
		randNum[i] = rand() % input + 1;
	}

	char Command;
	int temp = 0;
	int newRand = 0;
	bool bLoop = true;

	int Max = 0;
	int Min = 0;

	vector<int> sortNum;
	int count = 0;
	std::vector<int>::iterator iter;

	while (bLoop)
	{
		std::cout << "��ɾ� : ";
		cin >> Command;

		switch (Command)
		{
		case 'a':	//�������� �������� �� ŭ
			for (int i = 0; i < INPUTNUM - 1; i++)
			{
				for (int j = 0; j < INPUTNUM - 1; j++)
				{
					if (randNum[i] < randNum[j])	// ������ ���� ���ʺ��� ũ�� ���� ��ġ �ٲٱ�
					{
						temp = randNum[i];
						randNum[i] = randNum[j];
						randNum[j] = temp;
					}
				}
			}

			for (int i = 0; i < INPUTNUM - 1; i++)
			{
				std::cout << randNum[i] << ' ';
			}

			std::cout << endl << endl;
			break;


		case 'd':	//�������� ������ �� ŭ
			for (int i = 0; i < INPUTNUM - 1; i++)
			{
				for (int j = 0; j < INPUTNUM - 1; j++)
				{
					if (randNum[i] > randNum[j])	// ���� ���� �����ʺ��� ũ�� ���� ��ġ �ٲٱ�
					{
						temp = randNum[i];
						randNum[i] = randNum[j];
						randNum[j] = temp;
					}
				}
			}

			

			for (int i = 0; i < INPUTNUM - 1; i++)
			{
				std::cout << randNum[i] << ' ';
			}

			std::cout << endl << endl;
			break;


		case 'r':
			newRand = rand() % 2;

			for (int i = 0; i < INPUTNUM - 1; i++)
			{
				for (int j = 0; j < INPUTNUM - 1; j++)
				{
					if (newRand == 1)	// newRand���� 1�̸� ���� ���� �ƴϸ� ����x
					{
						temp = randNum[i];
						randNum[i] = randNum[j];
						randNum[j] = temp;
					}
				}
			}

			for (int i = 0; i < INPUTNUM - 1; i++)
			{
				std::cout << randNum[i] << ' ';
			}

			std::cout << endl << endl;
			break;


		case 'q':
			bLoop = false;
			break;


		case 't':
			//3�� ��� ����
			for (int j = 0; j < INPUTNUM - 1; j++)
			{
				if (randNum[j] % 3 == 0)	// 
				{
					sortNum.push_back(randNum[j]);
				}
			}

			//�������� ����
			sort(sortNum.begin(), sortNum.end());

			//���
			for (iter = sortNum.begin(); iter != sortNum.end(); iter++)
			{
				std::cout << *iter << ' ';
			}

			std::cout << endl << endl;
			sortNum.clear();
			break;

		case 's':
			//7�� ��� ����
			for (int j = 0; j < INPUTNUM - 1; j++)
			{
				if (randNum[j] % 7 == 0)	// 
				{
					sortNum.push_back(randNum[j]);
				}
			}

			//�������� ����
			sort(sortNum.begin(), sortNum.end());

			//���
			for (iter = sortNum.begin(); iter != sortNum.end(); iter++)
			{
				std::cout << *iter << ' ';
			}

			std::cout << endl << endl;
			sortNum.clear();
			break;

		case '+':
			for (int j = 0; j < INPUTNUM - 1; j++)
			{
				if (randNum[j] % 3 == 0 || randNum[j] % 7 == 0)	// or����
				{
					sortNum.push_back(randNum[j]);
				}
			}

			//�������� ����
			sort(sortNum.begin(), sortNum.end());

			//���
			for (iter = sortNum.begin(); iter != sortNum.end(); iter++)
			{
				std::cout << *iter << ' ';
			}

			std::cout << endl << endl;
			sortNum.clear();
			break;

		case '-':
			for (int j = 0; j < INPUTNUM - 1; j++)
			{
				if (randNum[j] % 3 == 0 && randNum[j] % 7 == 0)	// and����
				{
					sortNum.push_back(randNum[j]);
				}
			}

			//�������� ����
			sort(sortNum.begin(), sortNum.end());

			//���
			for (iter = sortNum.begin(); iter != sortNum.end(); iter++)
			{
				std::cout << *iter << ' ';
			}

			std::cout << endl << endl;
			sortNum.clear();
			break;
		case 'm':
			Max = randNum[0];

			for (int j = 1; j < INPUTNUM - 1; j++)
			{
				if (randNum[j] > Max)	// �ű� ���� Max���� ũ�� ����
				{
					Max = randNum[j];
				}
			}
			std::cout << "�ִ� �� : " << Max << endl << endl;

			break;

		case 'n':
			Min = randNum[0];

			for (int j = 1; j < INPUTNUM - 1; j++)
			{
				if (randNum[j] < Min)	// �ű� ���� Max���� ũ�� ����
				{
					Min = randNum[j];
				}
			}
			std::cout << "�ּ� �� : " << Min << endl << endl;

			break;

		case 'p':
			for (int i = 0; i < INPUTNUM; i++)
			{
				randNum[i] = rand() % input + 1;
			}

			for (int i = 0; i < INPUTNUM - 1; i++)
			{
				std::cout << randNum[i] << ' ' << endl << endl;
			}

			break; 
		}
	}

	return 0;
}//while

	

