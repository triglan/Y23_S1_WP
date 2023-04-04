//insert의 경우
//caps
//MAXWORD보다 클 때
if (wordcount >= MAXWORD)
{
	wordcount = 0; //--- 인덱스 변경
	cword = 1;
	linecount++;
	yPos = yPos + 20;
	if (linecount % 10 == 0 && linecount >= 10)//10이면
	{//linecount가 10이 되면 엔터*2에서 linecount++를 빼고 커서 위치에서 덮어쓰기
		yPos = 0;
	}
}

if (wordcount < MAXWORD && insert == 1)
{
	for (int i = wordcount; i >= cword; i--)
	{
		str[yPos / 20][i + 1] = str[yPos / 20][i];
	}
	wordcount++;
}

if (caps == -1 && ('a' <= wParam && wParam <= 'z'))//caps가 -1이면 대문자 출력
{
	str[yPos / 20][cword++] = toupper(wParam); //--- 그 외에는 문자를 캐럿 뒤에 붙인다.
}
else
str[yPos / 20][cword++] = wParam; //--- 그 외에는 문자를 캐럿 뒤에 붙인다.

if (cword - 1 == wordcount)//문장 마지막에서만 문장길이가 늘어남
wordcount++;


if (insert == -1)//
{
	if (wordcount >= MAXWORD)
	{
		wordcount = 0;
		cword = 0;
		linecount++;
		yPos = yPos + 20;
		if (linecount % 10 == 0 && linecount >= 10)//10이면
		{
			yPos = 0;
		}
	}
	else
	{
		for (int i = wordcount; i >= cword; i--)
		{
			str[yPos / 20][i + 1] = str[yPos / 20][i];
		}
		wordcount++;
	}
}
if (wordcount >= MAXWORD && insert != -1)// 글자 초과
{
	wordcount = 0; //--- 인덱스 변경
	cword = 1;
	linecount++;
	yPos = yPos + 20;
	if (linecount % 10 == 0 && linecount >= 10)//10이면
	{//linecount가 10이 되면 엔터*2에서 linecount++를 빼고 커서 위치에서 덮어쓰기
		yPos = 0;
	}
	str[yPos / 20][wordcount++] = wParam;
}
else
{
	if (caps == -1 && ('a' <= wParam && wParam <= 'z'))//caps가 -1이면 대문자 출력
	{
		str[yPos / 20][cword++] = toupper(wParam); //--- 그 외에는 문자를 캐럿 뒤에 붙인다.
	}
	else
		str[yPos / 20][cword++] = wParam; //--- 그 외에는 문자를 캐럿 뒤에 붙인다.

	if (cword - 1 == wordcount)//문장 마지막에서만 문장길이가 늘어남
		wordcount++;
}