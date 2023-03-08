#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <Windows.h>

using namespace std;

char RandNum();

#define STRINGMAXSIZE 60 

int main()
{
	string str;
	string tempstr;

	char menu;

	bool DubSpace = true;
	bool BeginCheck;
	bool bChange = true;	//f키를 누를 때 랜덤한 문자로 변경

	int countWord;
	int StringLength = 0;
	while (true)
	{
		//입력
		cout << "input sentence : ";
		getline(cin, str);
		//60자 이내, 마침표 검사
		if (str.size() > STRINGMAXSIZE)
		{
			cout << "60자가 넘어갔습니다.\n다시 입력해 주십시오.";
			Sleep(1000);
			system("cls");
			continue;
		}
		if (str[str.size() - 1] != '.')
		{
			cout << "문장의 마지막이 마침표가 아닙니다.\n다시 입력해 주십시오.";
			Sleep(1000);
			system("cls");
			continue;
		}

		//공백 압축
		while (DubSpace)
		{
			BeginCheck = false;
			for (int i = 0; i < str.size(); i++)	// i < str.size() == str[i]
			{
				if (str[i] == ' ' && str[i + 1] == ' ')	//ab  de f
				{
					for (int nextNum = i + 1; nextNum < str.size(); nextNum++)
					{//두번 째 공백부터 다음기호를 넣음
						str[nextNum] = str[nextNum + 1];
						BeginCheck = true;
					}
				}
				//검출시 반복 계속
			}//for (int i = 0; i < str.size(); i++)
			if (BeginCheck == true)
				DubSpace = true;
			else//아니면 반복 끝
				DubSpace = false;
		}//while (DubSpace)
		
		for (int i = 0; i < str.size(); i++)	//
		{
			if (str[i] == '.')
			{
				StringLength = i;
				break;
			}
				
		}

		break;
	}


	bool bLoop = true;
	int i = 0;

	bool trueE;
	int letterCount;

	while (bLoop)
	{
		cout << "명령어 ";
		cin >> menu;
		
		//출력
		switch (menu)
		{
		case 'e':
		case 'E'://	e있는 단어 대문자로
			i = 0;
			letterCount = 0;
			while (str[i] != '.')//마침표를 만나면 끝나는 while문
			{
				trueE = false;//초기화
				
				while (str[i] != ' ' && str[i] != '.')//한 단어를 돌리는 while문
				{
					//e가 있는지 체크 있으면 trueE true 리턴해서 대문자로 바뀌게 유도
					if (str[i] == 'e')
						trueE = true;
						
					//몇글자를 검사했는지 letterCount에 입력
					letterCount++;
					i++;
				}

				
				//e가 있으면 letterCount 글자 수 만큼 대문자를 바꿔준다.
				if (trueE)
				{
					for (int k = 0; k <= letterCount; k++)
					{
						if (str[i - k] >= 'a' && str[i - k] <= 'z')//소문자면
							str[i - k] = str[i - k] - 32;
					}
					
				}

				letterCount = 0;
				//if (str[i] == '.')
				//	break;
				if (str[i] == ' ')
					i++;
			}//while (str[i] != '.')

			cout << str << endl << endl;
			break;

		case 'f':
		case 'F':
			if (bChange)	//바꾸기
			{
				for (int i = 0; i < StringLength - 1; i++)
				{
					if (str[i] == ' ')
					{
						str[i] = RandNum();
					}
				}
				cout << str << "\n\n";
				bChange = false;
				break;
			}
			else//원상복구
			{
				for (int i = 0; i < StringLength - 1; i++)	//문장 길이 -1(마침표 빼고) 돌려라
				{
					if (str[i] == '@' || str[i] == '%' || str[i] == '#' || str[i] == '?')
					{
						str[i] = ' ';
					}
				}
				cout << str << "\n\n";
				bChange = true;
				break;
			}
			//단어 개수 출력
		case 'l':
		case 'L':
			countWord = 1;
			for (int i = 0; i < StringLength; i++)	//문장 길이만큼 돌려라
			{
				if(str[i] == ' ')
					countWord++;
			}//단어의 수를 세라
			cout << "Result : " << countWord << "words" << endl;
			break;

		case 'c':
		case 'C':
			for (int i = 0; i < StringLength; i++)	//문장 길이만큼 돌려라
			{
				if (str[i] >= 'a' && str[i] <= 'z')
				{	//대문자 변환
					str[i] = str[i] - 'a' + 'A';
				}
				else if (str[i] >= 'A' && str[i] <= 'Z')//소문자 변환
					str[i] = str[i] + 'a' - 'A';
			}
			cout << str << "\n\n";
			break;

		case 'a':
		case 'A':
			tempstr.clear();
			for (int i = 0; i < StringLength - 1; i++)//마침표 빼고 넣기
			{
				/*if (str[i + 1] == ' ')
				{
					tempstr[i] = ' ';
				}*/
				//tempstr.push_back(str[i + 1]);
				tempstr.push_back(str[i + 1]);
			}
			tempstr.push_back(str[0]);
			tempstr.push_back('.');
			
			str = tempstr;
			cout << str << endl << endl;

			break;
			
			//종료
		case 'q' :
		case 'Q' :
			bLoop = false;
			break;

		default:
			break;
		}

	}


	

}

char RandNum()
{
	int randNum = rand() % 4;
	if(randNum == 0)
		return '@';
	else if(randNum == 1)
		return '%';
	else if(randNum == 2)
		return '#';
	else if(randNum == 3)
		return '?';	//마침표의 자율성을 물음표로 대체

	return '?';	
}

