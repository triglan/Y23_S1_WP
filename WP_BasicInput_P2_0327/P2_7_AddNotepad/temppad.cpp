//insert�� ���
//caps
//MAXWORD���� Ŭ ��
if (wordcount >= MAXWORD)
{
	wordcount = 0; //--- �ε��� ����
	cword = 1;
	linecount++;
	yPos = yPos + 20;
	if (linecount % 10 == 0 && linecount >= 10)//10�̸�
	{//linecount�� 10�� �Ǹ� ����*2���� linecount++�� ���� Ŀ�� ��ġ���� �����
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

if (caps == -1 && ('a' <= wParam && wParam <= 'z'))//caps�� -1�̸� �빮�� ���
{
	str[yPos / 20][cword++] = toupper(wParam); //--- �� �ܿ��� ���ڸ� ĳ�� �ڿ� ���δ�.
}
else
str[yPos / 20][cword++] = wParam; //--- �� �ܿ��� ���ڸ� ĳ�� �ڿ� ���δ�.

if (cword - 1 == wordcount)//���� ������������ ������̰� �þ
wordcount++;


if (insert == -1)//
{
	if (wordcount >= MAXWORD)
	{
		wordcount = 0;
		cword = 0;
		linecount++;
		yPos = yPos + 20;
		if (linecount % 10 == 0 && linecount >= 10)//10�̸�
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
if (wordcount >= MAXWORD && insert != -1)// ���� �ʰ�
{
	wordcount = 0; //--- �ε��� ����
	cword = 1;
	linecount++;
	yPos = yPos + 20;
	if (linecount % 10 == 0 && linecount >= 10)//10�̸�
	{//linecount�� 10�� �Ǹ� ����*2���� linecount++�� ���� Ŀ�� ��ġ���� �����
		yPos = 0;
	}
	str[yPos / 20][wordcount++] = wParam;
}
else
{
	if (caps == -1 && ('a' <= wParam && wParam <= 'z'))//caps�� -1�̸� �빮�� ���
	{
		str[yPos / 20][cword++] = toupper(wParam); //--- �� �ܿ��� ���ڸ� ĳ�� �ڿ� ���δ�.
	}
	else
		str[yPos / 20][cword++] = wParam; //--- �� �ܿ��� ���ڸ� ĳ�� �ڿ� ���δ�.

	if (cword - 1 == wordcount)//���� ������������ ������̰� �þ
		wordcount++;
}