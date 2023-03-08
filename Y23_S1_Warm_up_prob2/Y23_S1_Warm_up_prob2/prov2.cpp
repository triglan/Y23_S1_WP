#include <iostream>
#include <vector>
#include <algorithm>

#define INPUTNUM 10

using namespace std;

int main()
{
	int randNum[INPUTNUM] = { 0 };
	int input;

	std::cout << "사용자가 입력한 숫자보다 작은 임의의 수 30개를 자동으로 만듭니다 : ";
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
		std::cout << "명령어 : ";
		cin >> Command;

		switch (Command)
		{
		case 'a':	//오름차순 오른쪽이 더 큼
			for (int i = 0; i < INPUTNUM - 1; i++)
			{
				for (int j = 0; j < INPUTNUM - 1; j++)
				{
					if (randNum[i] < randNum[j])	// 오른쪽 값이 왼쪽보다 크면 서로 위치 바꾸기
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


		case 'd':	//내림차순 왼쪽이 더 큼
			for (int i = 0; i < INPUTNUM - 1; i++)
			{
				for (int j = 0; j < INPUTNUM - 1; j++)
				{
					if (randNum[i] > randNum[j])	// 왼쪽 값이 오른쪽보다 크면 서로 위치 바꾸기
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
					if (newRand == 1)	// newRand값이 1이면 서로 스왑 아니면 스왑x
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
			//3의 배수 정렬
			for (int j = 0; j < INPUTNUM - 1; j++)
			{
				if (randNum[j] % 3 == 0)	// 
				{
					sortNum.push_back(randNum[j]);
				}
			}

			//오름차순 정렬
			sort(sortNum.begin(), sortNum.end());

			//출력
			for (iter = sortNum.begin(); iter != sortNum.end(); iter++)
			{
				std::cout << *iter << ' ';
			}

			std::cout << endl << endl;
			sortNum.clear();
			break;

		case 's':
			//7의 배수 정렬
			for (int j = 0; j < INPUTNUM - 1; j++)
			{
				if (randNum[j] % 7 == 0)	// 
				{
					sortNum.push_back(randNum[j]);
				}
			}

			//오름차순 정렬
			sort(sortNum.begin(), sortNum.end());

			//출력
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
				if (randNum[j] % 3 == 0 || randNum[j] % 7 == 0)	// or연산
				{
					sortNum.push_back(randNum[j]);
				}
			}

			//오름차순 정렬
			sort(sortNum.begin(), sortNum.end());

			//출력
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
				if (randNum[j] % 3 == 0 && randNum[j] % 7 == 0)	// and연산
				{
					sortNum.push_back(randNum[j]);
				}
			}

			//오름차순 정렬
			sort(sortNum.begin(), sortNum.end());

			//출력
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
				if (randNum[j] > Max)	// 신규 값이 Max보다 크면 실행
				{
					Max = randNum[j];
				}
			}
			std::cout << "최대 값 : " << Max << endl << endl;

			break;

		case 'n':
			Min = randNum[0];

			for (int j = 1; j < INPUTNUM - 1; j++)
			{
				if (randNum[j] < Min)	// 신규 값이 Max보다 크면 실행
				{
					Min = randNum[j];
				}
			}
			std::cout << "최소 값 : " << Min << endl << endl;

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

	

