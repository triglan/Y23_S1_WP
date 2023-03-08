#include <iostream>

#define COL 5		//������ ��
#define ROW 4		//������ ��
#define MAXCOUNT 50
int num[ROW][COL];

using namespace std;


//2���� �迭 �������� ����
void ascend();

int main()
{
	//������ ����
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


	for (int i = 0; i < ROW; i++)//������
	{
		for (int j = 0; j < COL; j++)//������
		{
			std::cout << num[i][j] << " ";
		}
		std::cout << endl;
	}

	char input;

	while (true)
	{
		std::cout << "��ɾ� : ";
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


	//temparr ����
	for (int i = 0; i < ROW - 1; i++)//������
	{
		for (int j = 0; j < COL - 1; j++)//������
		{
			temparr[i * j + j] = num[i][j];
		}
	}

	//temparr ����
	int temp = 0;
	for (int i = 0; i < multiple - 1; i++)
	{
		for (int j = 0; j < multiple - 1; j++)
		{
			if (temparr[i] < temparr[j])	// ������ ���� ���ʺ��� ũ�� ���� ��ġ �ٲٱ�
			{
				temp = temparr[i];
				temparr[i] = temparr[j];
				temparr[j] = temp;
			}
		}
	}

	//���İ� ������ ����
	for (int i = 0; i < ROW; i++)//������
	{
		for (int j = 0; j < COL; j++)//������
		{
			num[i][j] = temparr[i * j + j];
		}
	}

	//���
	for (int i = 0; i < ROW; i++)//������
	{
		for (int j = 0; j < COL; j++)//������
		{
			std::cout << num[i][j] << " ";
		}
		std::cout << endl;
	}
}