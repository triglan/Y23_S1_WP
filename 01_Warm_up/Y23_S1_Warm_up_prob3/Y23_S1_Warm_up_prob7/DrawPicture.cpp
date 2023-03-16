#include <iostream>

using namespace std;

void PrintX(int x);
void RTriangle(int x);
void diamond(int x);
void ButterFly(int x);
void SandClock(int x);
void DoubleRec(int x);

int main()
{
	int x;
	char shape;
	while (true)
	{
		while (true)
		{
			cout << "명령어(모양, 너비) : ";
			cin >> shape;
			if (shape == 'q')
				return 0;
			cin >> x;

			if (x > 0 && x <= 20 && shape > '0' && shape <= '6' && x % 2 == 0)
				break;
			else
				cout << "다시 입력하세요" << endl;
		}
		//선의 길이가 x - 1만큼 짝수면 안이쁨, 짝수를 원할 시 > 0 -> >= 0
//나비는 x칸 그대로
		switch (shape)
		{
		case '1':
			PrintX(x);
			break;
		case '2':
			RTriangle(x);
			break;
		case '3':
			diamond(x - 1);
			break;
		case '4':
			ButterFly(x);
			break;
		case '5':
			SandClock(x);
			break;

		case '6':
			DoubleRec(x);
			break;

		case 'q':
			return 0;

		default:
			return 0;
		}
	}

	
}


void PrintX(int x)
{
	for (int up = 1; up < x; up++)
	{
		for (int i = 0; i < x; i++)
		{
			if (i == up || i == (x - up))
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;
	}
	cout<< endl;
}

void RTriangle(int x)
{
	for (int up = 0; up < x / 2; up++)
	{
		for (int i = 0; i < x; i++)
		{
			if (i > up && i < x - up)
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void diamond(int x)
{
	for (int up = 0; up < x / 2; up++)
	{
		for (int i = 0; i < x; i++)
		{
			if (i >= x / 2 - up && i <= x / 2 + up)
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;
	}
	for (int up = 0; up < x / 2 + 1; up++)
	{
		for (int i = 0; i < x; i++)
		{
			if (i >= up && i < x - up)
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;
	}

	cout << endl;
}

void ButterFly(int x)
{
	for (int up = 0; up < x; up++)
	{//10
		if (up < x / 2 + 1)
		{
			for (int i = 0; i < x; i++)
			{
				if (i < up || i >= (x - up))
					cout << "*";
				else
					cout << " ";
			}
		}
		else
			for (int i = 0; i < x; i++)
			{
				if ((i >= 0 && i < x - up) || (i >= up && i < x))
					cout << "*";
				else
					cout << " ";
			}
		cout << endl;
	}
}

void SandClock(int x)
{
	
	for (int up = 0; up < x / 2; up++)
	{
		if (up < x / 2)
		{
			for (int i = 0; i < x; i++)
			{
				if (i > up && i < (x - up))
					cout << "*";
				else
					cout << " ";
			}
			cout << endl;
		}
	}
	for (int up = x / 2 - 2; up >= 0; up--)
	{
		for (int i = x; i >= 0; i--)//9 i>
		{
			if (i > up && i < (x - up))
				cout << "*";
			else
				cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void DoubleRec(int x)
{
	for (int i = 0; i < x; i++)
	{
		cout << "* ";
	}
	cout << endl;

	for (int j = 0; j < x / 2; j++)
	{
		for (int i = 0; i < x; i++)
		{
			if (i == 0 || i == x / 2 || i == x / 2 - 1 || i == x - 1)
				cout << "* ";
			else
				cout << "  ";
		}
		cout << endl;
	}

	for (int i = 0; i < x; i++)
	{
		cout << "* ";
	}
	cout << endl;

}