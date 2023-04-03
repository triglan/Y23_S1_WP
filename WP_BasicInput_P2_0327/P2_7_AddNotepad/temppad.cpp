#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#define MAXWORD 10
#define COUNTNUM 10

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

	static TCHAR str[10][100];
	static TCHAR caretstr[10][100];

	static int strcount = 0;
	static int count[COUNTNUM] = { 0 };
	static int lineNum = 0;

	static int xPos = 0;
	static int yPos = 0;


	switch (uMsg)
	{
	case WM_CREATE:
		CreateCaret(hwnd, NULL, 5, 15); //--- ĳ�� �����
		ShowCaret(hwnd);				//--�� ȭ�鿡 ĳ�� ǥ��
		SetCaretBlinkTime(300);
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);

		if (strcount % 10 == 0 && strcount >= 10)
		{
			lineNum = 0;
			yPos = lineNum * 20;
		}

		if (wParam == VK_BACK) //--- �齺���̽��� �Է��ϸ�
		{
			str[strcount % 10][count[lineNum] - 1] = ' ';
			count[lineNum]--;
		}
		else if (count[lineNum] >= MAXWORD)
		{
			count[lineNum] = 0; //--- �ε��� ����
			strcount++;
			yPos = yPos + 20;
			yPos = lineNum * 20;

			str[strcount][count[lineNum]++] = wParam;
		}
		else if (wParam == VK_RETURN) //--- ����Ű�� �Է��ϸ�: ���ڿ��� �����ٿ� ���
		{
			if (count <= 0)
			{
				strcount--;
				yPos = yPos - 20;
				yPos = lineNum * 20;
			}
			count[lineNum] = 0; //--- �ε��� ����
			strcount++;
			lineNum++;
			yPos = yPos + 20;
			yPos = lineNum * 20;
		}
		else if (wParam == VK_ESCAPE)
		{
			strcount = 0;
			count[lineNum] = 0;
			yPos = 0;
			yPos = lineNum * 20;
		}
		else if (wParam == VK_TAB)
		{
			for (int i = 0; i < 4; i++)
			{
				if (count[lineNum] >= MAXWORD - 1)
				{
					count[lineNum] = 0; //--- �ε��� ����
					strcount++;
					yPos = yPos + 20;
					yPos = lineNum * 20;
					break;
				}
				str[strcount % 10][count[lineNum]++] = ' ';
			}
		}
		else
		{
			str[strcount % 10][count[lineNum]++] = wParam; //--- �� �ܿ��� ���ڸ� ���ڿ� �� �ڿ� ���δ�.
		}

		ReleaseDC(hwnd, hdc);
		InvalidateRect(hwnd, NULL, TRUE); //--- WM_PAINT �޽��� �߻�

		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetTextExtentPoint32(hdc, str[strcount % 10], count[lineNum], &size); //--- ���ڿ� ���� �˾Ƴ���
		//lstrlen(str[strcount % 10])


		if (strcount >= 10)
		{
			for (int i = 0; i < 10; i++)
			{
				TextOut(hdc, 0, i * 20, str[i], lstrlen(str[i]));//���
			}
			for (int i = strcount % 10 * 10; i <= strcount; i++)
			{
				TextOut(hdc, 0, i * 20, str[i], lstrlen(str[i]));//���
			}
			SetCaretPos(size.cx, yPos % 200); //--- ĳ�� ��ġ�ϱ�
			EndPaint(hwnd, &ps);
			break;
		}

		for (int i = 0; i < strcount; i++)
		{
			TextOut(hdc, 0, i * 20, str[i], lstrlen(str[i]));//���
		}
		TextOut(hdc, 0, yPos, str[strcount], lstrlen(str[strcount]));//���


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