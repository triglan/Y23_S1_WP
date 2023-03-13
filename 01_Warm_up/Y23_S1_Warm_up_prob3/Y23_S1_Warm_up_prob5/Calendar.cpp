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

void LastDaysOfYears();//마지막 날의 요일 출력
void GetDaysOfWeek(int year, int month, int day);//요일 출력
void PrintCalendar();//달력 출력

int main()
{
	int i = 0;
	int j = 0;
	int k = 0;

	int year = 0;	//해당 연도
	int month = 0;
	int day = 0;


	while (true)
	{
		char input[20];
		cin >> input;

		if (input[0] == 'q')
			return 0;
		else if (input[0] == 'f')
		{
			LastDaysOfYears();
		}


		for (i = 0; i < strlen(input); i++)
		{
			if (input[i] == '/')
				break;

			year = year * 10 + input[i] - 48;
		}

		for (j = i + 1; j < strlen(input); j++)
		{
			if (input[j] == '/')
				break;

			month = month * 10 + input[j] - 48;
		}

		for (int k = j + 1; k < strlen(input); k++)
		{
			day = day * 10 + input[k] - 48;
		}

		cout << getDay(year, month, day) << endl;

		GetDaysOfWeek(year, month, day);

		cout << endl << endl;

		PrintCalendar();//달력 출력


		
	}
	return 0;
}

//요일 반환
int getDay(int year, int month, int day)
{
	if (month < 3) {
		year -= 1;
		month += 12;
	}
	int q = day;
	int m = month;
	int Y = year;
	int K = Y % 100;
	int J = Y / 100;

	int h = (q + 13 * (m + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
	return h;
}

//달의 마지막 날 출력
int lastDays(int month, int year)
{
	switch (year)
	{
	case '4':
	case '6':
	case '9':
	case '11':
		return 30;

	case '1':
	case '3':
	case '5':
	case '7':
	case '8':
	case '10':
	case '12':
		return 31;

	case '2':
		if (year % 4 == 0)
			return 29;
		else
			return 28;

	default:
		return 0;
	}
}


void LastDaysOfYears()//마지막 날의 요일 출력
{

}

void GetDaysOfWeek(int year, int month, int day)//요일 출력
{
	int whatDay = getDay(year, month, day);

	switch (whatDay)
	{
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
	cout << endl;
}

void PrintCalendar()//달력 출력
{

}