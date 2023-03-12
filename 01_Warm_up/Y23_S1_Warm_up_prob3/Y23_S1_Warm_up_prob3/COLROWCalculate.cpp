#include <iostream>

#define ROW 5		//������ ��
#define COL 4		//������ ��
#define MAXCOUNT 50

int num[COL][ROW];
int duplicateNum[COL][ROW];//�ӽ�����

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
void dupNum(); //���ۿ� ����
void returnNum();//�ǵ�����
void swap(int& a, int& b);//���� �Լ�

void ascend(); //2���� �迭 �������� ����
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
	//������ ����
	RandomInput();
	char input;

	while (true)
	{
		std::cout << "��ɾ� : ";
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

void dupNum()//����
{
	for (int i = 0; i < COL; i++)//������
	{
		for (int j = 0; j < ROW; j++)//������
		{
			duplicateNum[i][j] = num[i][j];
		}
	}
}

void returnNum()//�ǵ�����
{
	for (int i = 0; i < COL; i++)//������
	{
		for (int j = 0; j < ROW; j++)//������
		{
			num[i][j] = duplicateNum[i][j];
		}
	}

	//���
	for (int i = 0; i < COL; i++)//������
	{
		for (int j = 0; j < ROW; j++)//������
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
	{//�ѹ� �� ��������
		returnNum();
		bAscend = false;
		return;
	}

	makeFalse();
	bAscend = true;
	dupNum();//�ӽ�����

	//���� ���� ��������
	for (int i = 0; i < COL * ROW; i++)
	{
		for (int j = 0; j < COL * ROW; j++)
		{
			if (num[i / ROW][i % ROW] < num[(j / ROW)][(j % ROW)])	//�� ���ڰ� �ں��� ���� �� �ٲ�
				swap(num[i / ROW][i % ROW], num[j / ROW][j % ROW]);
		}
	}

	//���
	for (int i = 0; i < COL; i++)//������
	{
		for (int j = 0; j < ROW; j++)//������
		{
			std::cout << num[i][j] << " ";
		}
		std::cout << endl;
	}
	
}

void descend()
{
	if (bDescend == true)
	{//�ѹ� �� ��������
		returnNum();
		bDescend = false;
		return;
	}

	makeFalse();
	bDescend = true;
	dupNum();//�ӽ�����

	//���� ���� ��������
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
	

	//���
	for (int i = 0; i < COL; i++)//������
	{
		for (int j = 0; j < ROW; j++)//������
		{
			std::cout << num[i][j] << " ";
		}
		std::cout << endl;
	}
}

void even()
{
	if (bDubble == true)
	{//�ѹ� �� ��������
		returnNum();
		bDubble = false;
		return;
	}

	makeFalse();
	bDubble = true;
	dupNum();//�ӽ�����



	//���
	for (int i = 0; i < COL; i++)//������
	{
		for (int j = 0; j < ROW; j++)//������
		{
			if(num[i][j] % 2 == 0)	//¦����
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
	{//�ѹ� �� ��������
		returnNum();
		bDubble = false;
		return;
	}

	makeFalse();
	bDubble = true;
	dupNum();//�ӽ�����



	//���
	for (int i = 0; i < COL; i++)//������
	{
		for (int j = 0; j < ROW; j++)//������
		{
			if (num[i][j] % 2 == 1)	//Ȧ����
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
	{//�ѹ� �� ��������
		returnNum();
		bMax = false;
		return;
	}

	makeFalse();
	bMax = true;
	dupNum();//�ӽ�����

	int Max = 0;

	for (int i = 0; i < COL; i++)//������
	{
		for (int j = 0; j < ROW; j++)//������
		{
			if (num[i][j] > Max)
				Max = num[i][j];
		}
	}

	for (int i = 0; i < COL; i++)//������
	{
		for (int j = 0; j < ROW; j++)//������
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
	{//�ѹ� �� ��������
		returnNum();
		bMin = false;
		return;
	}

	makeFalse();
	bMin = true;
	dupNum();//�ӽ�����

	int min = 5000;

	for (int i = 0; i < COL; i++)//������
	{
		for (int j = 0; j < ROW; j++)//������
		{
			if (num[i][j] < min)
				min = num[i][j];
		}
	}

	for (int i = 0; i < COL; i++)//������
	{
		for (int j = 0; j < ROW; j++)//������
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
	{//�ѹ� �� ��������
		returnNum();
		bFirstRow = false;
		return;
	}

	makeFalse();
	bFirstRow = true;
	dupNum();//�ӽ�����

	int FRow[COL] = { 0 };

	//1�࿡ ����
	for (int i = 0; i < COL; i++)//������
	{
		for (int j = 0; j < ROW; j++)//������
		{
			FRow[i] += num[i][j];
		}
	}

	//���
	for (int i = 0; i < COL; i++)//������
	{
		for (int j = 0; j < ROW; j++)//������
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
	{//�ѹ� �� ��������
		returnNum();
		bRandomSort = false;
		return;
	}

	makeFalse();
	bRandomSort = true;
	dupNum();//�ӽ�����

	int newRand = rand() % 2;
	int temp;

	for (int repeat = 0; repeat < COL * ROW; repeat++)
	{
		for (int i = 0; i < COL; i++)//������
		{
			for (int j = 0; j < ROW; j++)//������
			{
				newRand = rand() % 2;
				if (newRand == 1)	// newRand���� 1�̸� ���� ���� �ƴϸ� ����x
				{
					temp = num[i / ROW][i % ROW];
					num[i / ROW][i % ROW] = num[j / ROW][j % ROW];
					num[j / ROW][j % ROW] = temp;
				}
			}
		}
	}

	//���
	for (int i = 0; i < COL; i++)//������
	{
		for (int j = 0; j < ROW; j++)//������
		{
			std::cout << num[i][j] << " ";
		}
		std::cout << endl;
	}
}

void RandomInput()
{
	if (bRandomInput == true)
	{//�ѹ� �� ��������
		returnNum();
		bRandomInput = false;
		return;
	}

	makeFalse();
	bRandomInput = true;
	dupNum();//�ӽ�����

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

	for (int i = 0; i < COL; i++)//������
	{
		for (int j = 0; j < ROW; j++)//������
		{
			std::cout << num[i][j] << " ";
		}
		std::cout << endl;
	}
}

