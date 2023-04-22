#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#define MAXWORD 80
#define MAXLINE 10

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 1";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevIsntace, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 400, 200, 1280, 800, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static SIZE size;
	PAINTSTRUCT ps;
	HDC hdc;

	static TCHAR str[MAXLINE][100];
	static TCHAR roundstr[MAXLINE][500];
	static TCHAR passstr[MAXLINE][100];
	static TCHAR blankstr[MAXLINE][100];

	static int linecount = 0;
	static int wordcount;

	static int cword = 0;
	static int yPos = 0;

	static int caps = 1;
	static int insert = -1;
	static int password = -1;
	static int round = -1;
	static int blank = -1;

	//�齺���̽� ���ٷ� �̵�
	//10�� ������ ù�ٷ� �̵�
	switch (uMsg)
	{
	case WM_CREATE:
		CreateCaret(hwnd, NULL, 5, 15); //--- ĳ�� �����
		ShowCaret(hwnd);				//--�� ȭ�鿡 ĳ�� ǥ��
		SetCaretBlinkTime(300);
		wordcount = 0;
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);

		if (wParam == VK_BACK) //--- �齺���̽��� �Է��ϸ�
		{
			if (cword == 0 && yPos == 0)
				break;
			//���� cword�� 0�̶�� ���ٷ� ����
			if (cword <= 0)
			{
				yPos = yPos - 20;
				cword = lstrlen(str[yPos / 20]);
				wordcount = lstrlen(str[yPos / 20]);
			}
			for (int i = cword; i < wordcount; i++)
			{//ĳ�� ���� ���ڵ� ������ �ű��
				str[yPos / 20][i - 1] = str[yPos / 20][i];
			}
			str[yPos / 20][wordcount - 1] = '\0';
			wordcount--;
			cword--;
		}
		else if (wParam == VK_RETURN) //--- ����Ű�� �Է��ϸ�: ���ڿ��� �����ٿ� ���
		{
			wordcount = 0; //--- �ε��� ����
			cword = 0;
			linecount++;
			yPos = yPos + 20;
			if (linecount % 10 == 0 && linecount >= 10)//10�̸�
			{//linecount�� 10�� �Ǹ� ����*2���� linecount++�� ���� Ŀ�� ��ġ���� �����
				yPos = 0;

			}
		}
		else if (wParam == VK_ESCAPE)
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < MAXWORD; j++)
				{
					str[i][j] = '\0';
				}
			}
			linecount = 0;
			wordcount = 0;
			cword = 0;
			yPos = 0;
		}
		else if (wParam == VK_TAB)
		{
			for (int i = 0; i < 4; i++)
			{
				if (wordcount >= MAXWORD - 1)
				{//�ε��� ����
					wordcount = 0; //--- �ε��� ����
					cword = 0;
					linecount++;
					yPos = yPos + 20;
					break;
				}
				str[yPos / 20][cword++] = ' ';
				wordcount++;
			}
		}
		else if (wParam == '+')
		{
			for (int i = 0; i <= linecount; i++)
			{
				for (int j = 0; j < MAXWORD; j++)
				{
					if (str[i][j] >= '0' && str[i][j] < '9')
						str[i][j]++;
				}
			}
		}
		else if (wParam == '-')
		{
			for (int i = 0; i <= linecount; i++)
			{
				for (int j = 0; j < MAXWORD; j++)
				{
					if (str[i][j] > '0' && str[i][j] <= '9')
						str[i][j]--;
				}
			}
		}
		else
		{
			printf("cword : %d // wordcount : %d\nyPos/20 : %d // linecount : %d\n\n", cword, wordcount, yPos / 20, linecount);//CMD
			//Maxword Insert
			if (wordcount >= MAXWORD && insert == 1)
			{
				wordcount = 0; //--- �ε��� ����
				cword = 0;
				linecount++;
				yPos = yPos + 20;
				if (linecount % 10 == 0 && linecount >= 10)//10�̸�
				{//linecount�� 10�� �Ǹ� ����*2���� linecount++�� ���� Ŀ�� ��ġ���� �����
					yPos = 0;
				}
			}
			//Defualt Insert
			if (wordcount < MAXWORD && insert == 1)
			{
				for (int i = wordcount; i >= cword; i--)
				{
					str[yPos / 20][i + 1] = str[yPos / 20][i];
				}
				wordcount++;
			}

			if (cword >= MAXWORD)
			{
				wordcount = 0; //--- �ε��� ����
				cword = 0;
				linecount++;
				yPos = yPos + 20;
				if (yPos / 20 >= 10)//10�̸�
				{//linecount�� 10�� �Ǹ� ����*2���� linecount++�� ���� Ŀ�� ��ġ���� �����
					yPos = 0;
				}
			}

			if (caps == -1 && ('a' <= wParam && wParam <= 'z'))//caps�� -1�̸� �빮�� ���
			{
				str[yPos / 20][cword++] = toupper(wParam); //--- �� �ܿ��� ���ڸ� ĳ�� �ڿ� ���δ�.
			}
			else
				str[yPos / 20][cword++] = wParam; //--- �� �ܿ��� ���ڸ� ĳ�� �ڿ� ���δ�.

			if (cword - 1 == wordcount)//���� ������������ ������̰� �þ
				wordcount++;

		}
		ReleaseDC(hwnd, hdc);
		InvalidateRect(hwnd, NULL, TRUE); //--- WM_PAINT �޽��� �߻�

		break;

	case WM_KEYDOWN:
		hdc = GetDC(hwnd);

		if (wParam == VK_LEFT)
		{
			if (cword > 0)
			{
				cword--;
			}
		}
		else if (wParam == VK_RIGHT)
		{
			if (cword < wordcount)
			{
				cword++;
			}
		}
		else if (wParam == VK_UP)
		{
			if (lstrlen(str[yPos / 20 - 1]) < cword)
			{
				yPos = yPos - 20;
				cword = lstrlen(str[yPos / 20]);
				wordcount = lstrlen(str[yPos / 20]);
				ReleaseDC(hwnd, hdc);
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			}
			if (yPos > 0)
			{
				yPos = yPos - 20;
				wordcount = lstrlen(str[yPos / 20]);
			}
		}
		else if (wParam == VK_DOWN)
		{
			if (lstrlen(str[yPos / 20 + 1]) < cword)
			{
				yPos = yPos + 20;
				cword = lstrlen(str[yPos / 20]);
				wordcount = lstrlen(str[yPos / 20]);
				ReleaseDC(hwnd, hdc);
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			}
			if (yPos < linecount * 20)
			{
				yPos = yPos + 20;
				wordcount = lstrlen(str[yPos / 20]);

			}
		}
		else if (wParam == VK_F1)
		{
			caps = caps * -1;
		}
		else if (wParam == VK_F2)
		{
			password *= -1;
		}
		//???
		else if (wParam == VK_F3)
		{
			int temp = linecount;
			for (int i = MAXLINE; i > 0; i--)
			{
				for (int j = 0; j < MAXWORD; j++)
				{
					str[i][j] = str[i - 1][j];
				}
			}
			for (int j = 0; j < MAXWORD; j++)
			{
				str[0][j] = '\0';
			}
			linecount = temp;
			if (linecount < 9)
				linecount++;
		}
		else if (wParam == VK_F4)
		{
			for (int i = 0; i < MAXWORD; i++)
			{
				str[yPos / 20][i] = '\0';
				wordcount = 0;
				cword = 0;
			}
		}
		else if (wParam == VK_DELETE)
		{
			int start = 0;
			int end = 0;
			bool bcword = false;
			bool endLoop = false;
			for (end = 0; end <= wordcount; end++)
			{
				if (cword == end)
					bcword = true;

				if (bcword == true)//ĳ�� ��ġ�� �˾Ƴ��� ������� ���ϰ� ������
				{
					while (true)
					{
						if (str[yPos / 20][end] == ' ' || str[yPos / 20][end] == '\0')
						{
							endLoop = true;
							break;
						}
						if (endLoop)
							break;
						end++;
					}
				}
				if (endLoop)
					break;
				if (str[yPos / 20][end] == ' ')//���鸶�� �ܾ� �ʱ�ȭ
					start = end;


			}
			printf("start : %d // end : %d\n", start, end);

			for (int loop = start; loop < end; loop++)
			{
				for (int i = start; i < wordcount; i++)
				{//ĳ�� ���� ���ڵ� ������ �ű��
					str[yPos / 20][i] = str[yPos / 20][i + 1];
				}
				str[yPos / 20][wordcount - 1] = '\0';
				if (wordcount >= 0)
					wordcount--;
				if (cword >= 0)
					cword--;
			}

			if (wordcount <= 0)
			{
				cword = 0;
				wordcount = 0;
			}
		}
		else if (wParam == VK_HOME)
		{
			cword = 0;
		}
		else if (wParam == VK_END)
		{
			cword = wordcount;
		}
		else if (wParam == VK_INSERT)
		{
			insert *= -1;
		}
		else if (wParam == VK_NEXT)
		{
			round *= -1;
		}
		else if (wParam == VK_PRIOR)
		{
			blank *= -1;
		}
		ReleaseDC(hwnd, hdc);
		InvalidateRect(hwnd, NULL, TRUE); //--- WM_PAINT �޽��� �߻�

		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		
		
		if (password == 1)
		{
			for (int i = 0; i <= linecount; i++)
			{
				if (i >= MAXLINE)
					break;
				TextOut(hdc, 0, i * 20, L"*****************************************************************************************************************************************************************", lstrlen(str[i]));//���
			}
		}
		else
		{
			//���۽� (, \0���� �� )
			//���� �߽߰� bool������ true��) false�� (
			//����Ʈ������
			if (round == 1)
			{
				int rj = 0;
				int tempCword = 0;
				//��ȣ�ֱ�
				for (int i = 0; i <= linecount; i++)
				{
					tempCword = 0;
					roundstr[i][rj++] = '(';
					for (int j = 0; 0 < MAXWORD; j++)
					{
						if (str[i][j] == '\0')
							break;

						if (str[i][0] == ' ' && j == 0)
						{
							while (true)
							{
								if (str[i][j] != ' ')
									break;
								j++;
							}
						}

						if (str[i][j] != ' ')
						{
							roundstr[i][rj++] = str[i][j];
							tempCword++;
						}
						else
						{
							roundstr[i][rj++] = ')';
							roundstr[i][rj++] = '(';
							tempCword++;
							tempCword++;
							while (str[i][j] == ' ')
							{
								j++;
								tempCword++;
							}
							j--;
							tempCword--;
						}

					}
					roundstr[i][rj] = ')';
					tempCword++;
					rj = 0;
				}

				for (int i = 0; i <= linecount; i++)
				{
					if (i >= MAXLINE)
						break;
					TextOut(hdc, 0, i * 20, roundstr[i], lstrlen(roundstr[i]));//���		
				}
				GetTextExtentPoint32(hdc, roundstr[yPos / 20], tempCword, &size);
				SetCaretPos(size.cx, yPos); //--- ĳ�� ��ġ�ϱ�
				EndPaint(hwnd, &ps);
				break;
			}
			if (blank == 1)
			{
				int blankCword = cword;
				;
				int bj = 0;
				for (int i = 0; i <= linecount; i++)
				{
					for (int j = 0; j < MAXWORD; j++)
					{
						if (str[i][j] == ' ')
						{
							if (i == yPos / 20)
								blankCword--;
						}
						else
						{
							blankstr[i][bj++] = str[i][j];
							
						}
					}
					bj = 0;
			
					
				}
				for (int i = 0; i <= linecount; i++)
				{
					if (i >= MAXLINE)
						break;
					TextOut(hdc, 0, i * 20, blankstr[i], lstrlen(blankstr[i]));//���		
				}

				GetTextExtentPoint32(hdc, blankstr[yPos / 20], blankCword, &size);
				SetCaretPos(size.cx, yPos); //--- ĳ�� ��ġ�ϱ�
				EndPaint(hwnd, &ps);
				break;
			}

			for (int i = 0; i <= linecount; i++)
			{
				if (i >= MAXLINE)
					break;
				TextOut(hdc, 0, i * 20, str[i], lstrlen(str[i]));//���
			}
		}
		GetTextExtentPoint32(hdc, str[yPos/20], cword, &size); //--- ���ڿ� ���� �˾Ƴ���
		SetCaretPos(size.cx, yPos); //--- ĳ�� ��ġ�ϱ�
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		HideCaret(hwnd); //--- ĳ�� �����
		DestroyCaret(); //--- ĳ�� �����ϱ�
		PostQuitMessage(0);
		break;


	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
