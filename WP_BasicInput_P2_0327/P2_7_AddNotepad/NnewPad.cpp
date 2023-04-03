#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#define MAXWORD 10
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

	static int linecount = 0;
	static int wordcount;

	static int cword = 0;
	static int yPos = 0;

	static bool caps = false;

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


		if (linecount % 10 == 0 && linecount >= 10)//10�̸�
		{//linecount�� 10�� �Ǹ� ����*2���� linecount++�� ���� Ŀ�� ��ġ���� �����
			yPos = 0;
			
		}

		if (wParam == VK_BACK) //--- �齺���̽��� �Է��ϸ�
		{
			for (int i = 0; i < length; i++)
			{

			}
			str[yPos / 20][cword - 1] = ' ';
			wordcount--;
			cword--;
		}
		else if (wordcount >= MAXWORD)// ���� �ʰ�
		{
			wordcount = 0; //--- �ε��� ����
			cword = 0;
			linecount++;
			yPos = yPos + 20;
			str[linecount][wordcount++] = wParam;
		}
		else if (wParam == VK_RETURN) //--- ����Ű�� �Է��ϸ�: ���ڿ��� �����ٿ� ���
		{
			wordcount = 0; //--- �ε��� ����
			cword = 0;
			linecount++;
			yPos = yPos + 20;
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
		else
		{
			printf("cword : %d // wordcount : %d\nyPos/20 : %d // linecount : %d\n\n", cword, wordcount, yPos / 20, linecount);//CMD

			str[yPos/20][cword++] = wParam; //--- �� �ܿ��� ���ڸ� ĳ�� �ڿ� ���δ�.
			if(cword - 1 == wordcount)//���� ������������ ������̰� �þ
				wordcount++;
		}
		//str[linecount][wordcount] = '\0';
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
			if (yPos > 0)
			{
				yPos = yPos - 20;
			}
		}
		else if (wParam == VK_DOWN)
		{
			if (yPos < linecount * 20)
			{
				yPos = yPos + 20;
			}
		}
		else if (wParam == VK_F1)
		{
			caps = true;
		}

		ReleaseDC(hwnd, hdc);
		InvalidateRect(hwnd, NULL, TRUE); //--- WM_PAINT �޽��� �߻�

		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetTextExtentPoint32(hdc, str[linecount % 10], cword, &size); //--- ���ڿ� ���� �˾Ƴ���
		
		//if (linecount >= 10)
		//{
		//	for (int i = 0; i < 10; i++)
		//	{
		//		TextOut(hdc, 0, i * 20, str[i], lstrlen(str[i]));//���
		//	}
		//	for (int i = linecount % 10 * 10; i <= linecount; i++)
		//	{
		//		TextOut(hdc, 0, i * 20, str[i], lstrlen(str[i]));//���
		//	}
		//	SetCaretPos(size.cx, yPos % 200); //--- ĳ�� ��ġ�ϱ�
		//	EndPaint(hwnd, &ps);
		//	break;
		//}

		for (int i = 0; i <= linecount; i++)
		{
			TextOut(hdc, 0, i * 20, str[i], lstrlen(str[i]));//���
		}
		//TextOut(hdc, 0, yPos, str[linecount], lstrlen(str[linecount]));//���


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