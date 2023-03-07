
#ifdef temptemp
a = 0;
b = 0;
for (int i = 0; i < StringLength - 1; i++)	//문장 마침표 전까지
{
	if (str[i] != ' ')	//공백(단어)를 안만나면
		strWord[a][b] = str[i];
	else				//공백(단어)를 만나면
	{
		a++; //strWord[0] asdasd strWord[1] BEFd
		b = 0;
	}
	b++;
}//단어 구분

for (int i = 0; i < STRINGMAXSIZE; i++)
{
	for (int j = 0; j < STRINGMAXSIZE; j++)
	{
		if (strWord[i][j] == 'e')//e가 있으면
		{
			if (strWord[i][j] >= 'a' && strWord[i][j] <= 'z')//소문자면
			{	//대문자 변환
				strWord[i][j] = strWord[i][j] - 'a' + 'A';
			}
		}
	}
}
for (int i = 0; i < STRINGMAXSIZE; i++)//출력
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
for (int i = 0; i < StringLength - 1; i++)	//문장 마침표 전까지
{
	if (str[i] != ' ')	//공백(단어)를 안만나면
		stringWord[a].push_back(str[i]);
	else				//공백(단어)를 만나면
	{
		a++;
	}
}//단어 구분

for (int a = 0; a < STRINGMAXSIZE; a++)
{
	if (stringWord[a] == "e")//e가 있으면
	{
		if (stringWord[a][b] >= 'a' && stringWord[a][b] <= 'z')//소문자면
		{	//대문자 변환
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