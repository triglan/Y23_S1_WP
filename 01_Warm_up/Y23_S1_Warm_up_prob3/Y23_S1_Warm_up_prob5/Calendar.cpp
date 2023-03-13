#include <iostream>
#include <sstream>
#include <string>

#define Sunday 0
#define Monday 1
#define Tuesday 2
#define Wednesday 3
#define Thursday 4
#define Friday 5
#define Saturday 6

using namespace std;



string sDate;

int getDay(int year, int month, int day);
int lastDays(int month, int year);

void LastDaysOfYears(int year);//마지막 날의 요일 출력
void GetDaysOfWeek(int year, int month, int day);//요일 출력
void PrintCalendar(int year, int month, int day);//달력 출력

int main()
{
	int i = 0;
	int j = 0;
	int k = 0;

	int year = 0;	//해당 연도
	int month = 0;
	int day = 0;

	char input[20] = { 0 };
	while (true)
	{
		i = 0;
		j = 0;
		k = 0;

		year = 0;
		month = 0;
		day = 0;

		for (int i = 0; i < 20; i++)
		{
			input[i] = 0;
		};

		cin >> input;

		if (input[0] == 'q')
			return 0;

		else if (input[0] == 'f')
		{
			cin >> input;
			for (i = 0; i < strlen(input); i++)
			{

				year = year * 10 + input[i] - 48;
			}

			LastDaysOfYears(year);
			continue;
		}


		

		for (i = 0; i < strlen(input); i++)
		{
			if (input[i] == '/')
				break;

			year = year * 10 + input[i] - 48;
		}

		if (!(2000 <= year < 2030))
		{
			cout << "잘못된 값" << endl << endl;
			break;
		}

		for (j = i + 1; j < strlen(input); j++)
		{
			if (input[j] == '/')
				break;

			month = month * 10 + input[j] - 48;
		}

		for (k = j + 1; k < strlen(input); k++)
		{
			day = day * 10 + input[k] - 48;
		}


		GetDaysOfWeek(year, month, day);

		cout << endl << endl;

		PrintCalendar(year, month, day);//달력 출력


		
	}
	return 0;
}

//일 반환
int getDay(int year, int month, int day)
{
	int fullDay = 0;

	if (year != 2000) {
		for (int i = 0; i < year - 2000; i++)//if 2000 1월 2일
		{
			if (i % 4 == 0)
				fullDay += 366;
			else
				fullDay += 365;
		}
	}

	if (month != 1) {
		for (int i = 1; i < month; i++)
		{
			fullDay += lastDays(i, year);//1월부터 이번 달 전까지 계산
		}
	}


	for (int i = 0; i < day; i++)
	{
		fullDay += 1;
	}
	if (year == 2000 && month == 1 && day == 1)
		return 6;

	fullDay -= 2;
	return fullDay;//2001 1월 2일 이면 0 반환, 일요일
}

//달의 마지막 날 출력
int lastDays(int month, int year)
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
		if (year % 4 == 0)
			return 29;
		else
			return 28;

	default:
		return 0;
	}
}


void LastDaysOfYears(int year)//마지막 날의 요일 출력
{

	for (int i = 1; i <= 12; i++)
	{
		printf("%d-%2d-%2d : ", year, i, lastDays(i, year));
		GetDaysOfWeek(year, i, lastDays(i, year));
		cout << "\t";
		if ((i % 4) == 0)
			cout << endl;
	}
}

void GetDaysOfWeek(int year, int month, int day)//요일 출력
{
	int whatDay = getDay(year, month, day) % 7;//

	switch (whatDay)
	{
		break;
	case '\0':
		cout << "Sunday";
		break;
	case'\1':
		cout << "Monday";
		break;
	case'\2':
		cout << "Tuesday";
		break;
	case'\3':
		cout << "Wednesday";
		break;
	case'\4':
		cout << "Thursday";
		break;
	case'\5':
		cout << "Friday";
		break;
	case'\6':
		cout << "Saturday";
		break;
	default:
		break;
	}
}

void PrintCalendar(int year, int month, int day)//달력 출력
{
	int startDay = getDay(year, month, 1) % 7;//첫날 요일 저장
	
	cout << "Sunday    " << "Monday    " << "Tuesday   " << "Wednesday  " << "Thursday  " << "Friday    " << "Saturday" << endl;

	cout << "    ";
	for (int i = 0; i < startDay; i++)
	{
		cout << "          ";
	}

	startDay = (startDay ) % 7;

	for (int i = 1; i <= lastDays(month, year); i++)
	{
		if(i<10)
			cout << i << "         ";
		else
			cout << i << "        ";

		if (((i + startDay)% 7) == 0 && i)
		{
			cout << endl;
			cout << "   ";
		}
	}

	cout << endl << endl;
}