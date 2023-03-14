#include <iostream>

using namespace std;

typedef struct
{
	char name[5];
	int id;
	int bd;
	int enter[6];
	int rank;
}member;

member m[15];
int num = 0;

int lastDays(int month);
void ERROR();
void PrecedeMem();
void PrintMem(int number);

int main()
{
	char order;

	char name[100] = { 0 };
	int id;
	int bd;
	int enter;
	int enterMonth;
	
	int Max;
	int Maxmem;	
	int Min;
	int Minmem;
	int CheckCount[6] = { 0 };

	bool AContinue = true;

	PrecedeMem();

	while (true)
	{
		cout << "명령어 : ";
		cin >> order;

		switch (order)
		{
		case 'A':
		case 'a':	
			while (true)
			{
				AContinue = true;

				cout << "이름/ID/생일/1~6달 출석 횟수 : ";
				cin >> name;
				if (name[5] != 0)
				{
					ERROR();
					continue;
				}
				for (int i = 0; i < 5; i++)
				{
					m[num].name[i] = name[i];
				}

				cin >> id;
				if (id < 10000 || id >= 100000)
				{
					ERROR();
					continue;
				}

				m[num].id = id;

				cin >> bd;
				if (bd / 100 == 1 && bd / 100 == 3 && bd / 100 == 5)
				{
					if (bd % 100 > 31)
					{
						ERROR();
						continue;
					}
				}
				else if (bd / 100 == 4 && bd / 100 == 6)
				{
					if (bd % 100 > 30)
					{
						ERROR();
						continue;
					}
				}
				else if (bd / 100 == 2)
				{
					if(bd%100>28)
						if (bd % 100 > 30)
						{
							ERROR();
							continue;
						}
				}


				m[num].bd = bd;


				for (int i = 0; i < 6; i++)
				{
					cin >> enterMonth;
					cin >> enter;

					if (enterMonth < 0 || enterMonth>12)
					{
						ERROR();
						AContinue = false;
					}

					if (enter > lastDays(enterMonth))
					{
						ERROR();
						AContinue = false;
					}
					
					m[num].enter[enterMonth] = enter;
				}

				if (AContinue == false)
					continue;

				num++;
				break;
			}

			break;

		case 'p':
		case 'P':
			for (int i = 0; i <= num; i++)
			{
				PrintMem(i);
			}

			break;

		case 'M':
		case 'm':
			Max = 0;
			Maxmem = 0;
			for (int i = 0; i <= num; i++)
			{
				for (int count = 0; count < 6; count++)
				{
					CheckCount[i] += m[i].enter[count];
				}
			}
			for (int i = 0; i <= num; i++)
			{
				if (Max < CheckCount[i])
				{
					Max = CheckCount[i];
					Maxmem = i;
				}
			}
			PrintMem(Maxmem);
			break;

		case 'N':
		case 'n':
			Min = 100000;
			Minmem = 0;
			for (int i = 0; i <= num; i++)
			{
				for (int count = 0; count < 6; count++)
				{
					CheckCount[i] += m[i].enter[count];
				}
			}
			for (int i = 0; i <= num; i++)
			{
				if (Min > CheckCount[i])
				{
					Min = CheckCount[i];
					Minmem = i;
				}
			}

			PrintMem(Minmem);
			break;

		case '1':
			Max = 0;
			Maxmem = 0;
			for (int i = 0; i <= num; i++)
			{
				if (Max < m[i].enter[0])
				{
					Max = m[i].enter[0];
					Maxmem = i;
				}
			}

			PrintMem(Maxmem);
			break;
		case '2':
			Max = 0;
			Maxmem = 0;
			for (int i = 0; i <= num; i++)
			{
				if (Max < m[i].enter[1])
				{
					Max = m[i].enter[1];
					Maxmem = i;
				}
			}

			PrintMem(Maxmem);
			break;
		case '3':
			Max = 0;
			Maxmem = 0;
			for (int i = 0; i <= num; i++)
			{
				if (Max < m[i].enter[2])
				{
					Max = m[i].enter[2];
					Maxmem = i;
				}
			}

			PrintMem(Maxmem);
			break;

		case 'I':
		case 'i':

			for (int i = 0; i <= num; i++)
			{
				m[i].rank = i;
			}

			for (int i = 0; i <= num; i++)
			{
				for (int j = 0; j <= num; j++)
				{
					if (m[j].name[0] > m[i].name[0])	//앞 숫자가 뒤보다 높을 때 바꿈
						swap(m[j].rank, m[i].rank);
				}
			}

			for (int i = 0; i <= num; i++)
			{
				for (int ranking = 0; ranking <= num; ranking++)
				{
					if (m[ranking].rank == (num - i))
						PrintMem(ranking);
				}
			}

			break;
		case 'j':
		case 'J':
			for (int i = 0; i <= num; i++)
			{
				m[i].rank = i;
			}

			for (int i = 0; i <= num; i++)
			{
				for (int j = 0; j <= num; j++)
				{
					if (m[j].id > m[i].id)	//앞 숫자가 뒤보다 높을 때 바꿈
						swap(m[j].rank, m[i].rank);
				}
			}

			for (int i = 0; i <= num; i++)
			{
				for (int ranking = 0; ranking <= num; ranking++)
				{
					if (m[ranking].rank == (num - i))
						PrintMem(ranking);
				}
			}
			break;

			case 'k':
			case 'K':
			for (int i = 0; i <= num; i++)
			{
				m[i].rank = i;
			}

			for (int i = 0; i <= num; i++)
			{
				for (int j = 0; j <= num; j++)
				{
					if (m[j].bd > m[i].bd)	//앞 숫자가 뒤보다 높을 때 바꿈
						swap(m[j].rank, m[i].rank);
				}
			}

			for (int i = 0; i <= num; i++)
			{
				for (int ranking = 0; ranking <= num; ranking++)
				{
					if (m[ranking].rank == i)
						PrintMem(ranking);
				}
			}
			break;

			case 'q':
				return 0;
		default:
			break;
		}
	}
	
}
void PrintMem(int number)
{
	cout << "이름 : " << m[number].name << "\t";
	cout << "ID : " << m[number].id << "\t";
	printf("생일 : %04d\t", m[number].bd);
	cout << "횟수 : " << "\t" << 1 << " : " << m[number].enter[0];
	cout << "\t" << 2 << " : " << m[number].enter[1];
	cout << "\t" << 3 << " : " << m[number].enter[2];
	cout << "\t" << 4 << " : " << m[number].enter[3];
	cout << "\t" << 5 << " : " << m[number].enter[4];
	cout << "\t" << 6 << " : " << m[number].enter[5];
	cout << endl;
}

void ERROR()
{
	cout << "ERROR" << endl;
	cin.ignore();
}

int lastDays(int month)
{
	switch (month)
	{
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;

	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;

	case '\2':
		return 28;

	default:
		return 0;
	}
}

void PrecedeMem()
{
	m[0].name[0] = 'S';
	m[0].name[1] = 'o';
	m[0].name[2] = 'n';
	m[0].name[3] = 'g';
	m[0].id = 12345;
	m[0].bd = 302;
	m[0].enter[0] = 10;
	m[0].enter[1] = 10;
	m[0].enter[2] = 15;
	m[0].enter[3] = 5;
	m[0].enter[4] = 25;
	m[0].enter[5] = 20;
	
	m[1].name[0] = 'K';
	m[1].name[1] = 'i';
	m[1].name[2] = 'm';
	m[1].id = 21325;
	m[1].bd = 122;
	m[1].enter[0] = 5;
	m[1].enter[1] = 9;
	m[1].enter[2] = 15;
	m[1].enter[3] = 20;
	m[1].enter[4] = 25;
	m[1].enter[5] = 30;

	m[2].name[0] = 'P';
	m[2].name[1] = 'a';
	m[2].name[2] = 'r';
	m[2].name[3] = 'k';
	m[2].id = 32543;
	m[2].bd = 909;
	m[2].enter[0] = 1;
	m[2].enter[1] = 2;
	m[2].enter[2] = 3;
	m[2].enter[3] = 4;
	m[2].enter[4] = 5;
	m[2].enter[5] = 6;

	num = 2;
}