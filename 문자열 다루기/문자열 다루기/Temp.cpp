
#ifdef temptemp
a = 0;
b = 0;
for (int i = 0; i < StringLength - 1; i++)	//���� ��ħǥ ������
{
	if (str[i] != ' ')	//����(�ܾ�)�� �ȸ�����
		strWord[a][b] = str[i];
	else				//����(�ܾ�)�� ������
	{
		a++; //strWord[0] asdasd strWord[1] BEFd
		b = 0;
	}
	b++;
}//�ܾ� ����

for (int i = 0; i < STRINGMAXSIZE; i++)
{
	for (int j = 0; j < STRINGMAXSIZE; j++)
	{
		if (strWord[i][j] == 'e')//e�� ������
		{
			if (strWord[i][j] >= 'a' && strWord[i][j] <= 'z')//�ҹ��ڸ�
			{	//�빮�� ��ȯ
				strWord[i][j] = strWord[i][j] - 'a' + 'A';
			}
		}
	}
}
for (int i = 0; i < STRINGMAXSIZE; i++)//���
{
	for (int j = 0; j < STRINGMAXSIZE; j++)
	{
		if (strWord[i][j] != ' ' && strWord[i][j + 1] != ' ')
			cout << strWord[i][j];
		else
			break;
	}
}

break;

a = 0;
for (int i = 0; i < StringLength - 1; i++)	//���� ��ħǥ ������
{
	if (str[i] != ' ')	//����(�ܾ�)�� �ȸ�����
		stringWord[a].push_back(str[i]);
	else				//����(�ܾ�)�� ������
	{
		a++;
	}
}//�ܾ� ����

for (int a = 0; a < STRINGMAXSIZE; a++)
{
	if (stringWord[a] == "e")//e�� ������
	{
		if (stringWord[a][b] >= 'a' && stringWord[a][b] <= 'z')//�ҹ��ڸ�
		{	//�빮�� ��ȯ
			stringWord[a][b] = stringWord[a][b] - 'a' + 'A';
		}
	}
}

for (int a = 0; f < length; f++)
{

}
break;
str.push_back

#endif