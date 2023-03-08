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
	bool bChange = true;	//fŰ�� ���� �� ������ ���ڷ� ����

	int countWord;
	int StringLength = 0;
	while (true)
	{
		//�Է�
		cout << "input sentence : ";
		getline(cin, str);
		//60�� �̳�, ��ħǥ �˻�
		if (str.size() > STRINGMAXSIZE)
		{
			cout << "60�ڰ� �Ѿ���ϴ�.\n�ٽ� �Է��� �ֽʽÿ�.";
			Sleep(1000);
			system("cls");
			continue;
		}
		if (str[str.size() - 1] != '.')
		{
			cout << "������ �������� ��ħǥ�� �ƴմϴ�.\n�ٽ� �Է��� �ֽʽÿ�.";
			Sleep(1000);
			system("cls");
			continue;
		}

		//���� ����
		while (DubSpace)
		{
			BeginCheck = false;
			for (int i = 0; i < str.size(); i++)	// i < str.size() == str[i]
			{
				if (str[i] == ' ' && str[i + 1] == ' ')	//ab  de f
				{
					for (int nextNum = i + 1; nextNum < str.size(); nextNum++)
					{//�ι� ° ������� ������ȣ�� ����
						str[nextNum] = str[nextNum + 1];
						BeginCheck = true;
					}
				}
				//����� �ݺ� ���
			}//for (int i = 0; i < str.size(); i++)
			if (BeginCheck == true)
				DubSpace = true;
			else//�ƴϸ� �ݺ� ��
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
		cout << "��ɾ� ";
		cin >> menu;
		
		//���
		switch (menu)
		{
		case 'e':
		case 'E'://	e�ִ� �ܾ� �빮�ڷ�
			i = 0;
			letterCount = 0;
			while (str[i] != '.')//��ħǥ�� ������ ������ while��
			{
				trueE = false;//�ʱ�ȭ
				
				while (str[i] != ' ' && str[i] != '.')//�� �ܾ ������ while��
				{
					//e�� �ִ��� üũ ������ trueE true �����ؼ� �빮�ڷ� �ٲ�� ����
					if (str[i] == 'e')
						trueE = true;
						
					//����ڸ� �˻��ߴ��� letterCount�� �Է�
					letterCount++;
					i++;
				}

				
				//e�� ������ letterCount ���� �� ��ŭ �빮�ڸ� �ٲ��ش�.
				if (trueE)
				{
					for (int k = 0; k <= letterCount; k++)
					{
						if (str[i - k] >= 'a' && str[i - k] <= 'z')//�ҹ��ڸ�
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
			if (bChange)	//�ٲٱ�
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
			else//���󺹱�
			{
				for (int i = 0; i < StringLength - 1; i++)	//���� ���� -1(��ħǥ ����) ������
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
			//�ܾ� ���� ���
		case 'l':
		case 'L':
			countWord = 1;
			for (int i = 0; i < StringLength; i++)	//���� ���̸�ŭ ������
			{
				if(str[i] == ' ')
					countWord++;
			}//�ܾ��� ���� ����
			cout << "Result : " << countWord << "words" << endl;
			break;

		case 'c':
		case 'C':
			for (int i = 0; i < StringLength; i++)	//���� ���̸�ŭ ������
			{
				if (str[i] >= 'a' && str[i] <= 'z')
				{	//�빮�� ��ȯ
					str[i] = str[i] - 'a' + 'A';
				}
				else if (str[i] >= 'A' && str[i] <= 'Z')//�ҹ��� ��ȯ
					str[i] = str[i] + 'a' - 'A';
			}
			cout << str << "\n\n";
			break;

		case 'a':
		case 'A':
			tempstr.clear();
			for (int i = 0; i < StringLength - 1; i++)//��ħǥ ���� �ֱ�
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
			
			//����
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
		return '?';	//��ħǥ�� �������� ����ǥ�� ��ü

	return '?';	
}

