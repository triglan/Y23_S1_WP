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

	static TCHAR str[10][MAXWORD + 1];	//�⺻ ���� ���
	//static TCHAR caretstr[10][100];//ȭ��ǥ �̵��� ���� 

	//�� ��, ���� ī��Ʈ
	static int linecount = 0;
	static int wordcount[COUNTNUM] = { 0 };
	
	//ĳ�� ��ġ
	static int lineNum = 0;
	static int wordNum = 0;

	//ĳ�� ��ǥ
	static int xPos = 0;//ĳ�� xPos
	static int yPos = 0;//ĳ�� yPos, �� ��ġ�� yPos/20


	switch (uMsg)
	{
	case WM_CREATE:
		CreateCaret(hwnd, NULL, 5, 15); //--- ĳ�� �����
		ShowCaret(hwnd);				//--�� ȭ�鿡 ĳ�� ǥ��
		SetCaretBlinkTime(300);
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);

		if (wParam == VK_BACK)
		{//ĳ�� ��ġ���� �� ���� �ϳ� �����
			//lineNum, wordNum�� 0�̸� break
			//wordNum�� 0�̸� ���ٷ�
			if (wordNum <= 0)
			{

			}
			str[lineNum][wordNum--] = ' ';
			wordcount[lineNum]--;
			yPos = yPos - 20;
		}

		ReleaseDC(hwnd, hdc);
		InvalidateRect(hwnd, NULL, TRUE); //--- WM_PAINT �޽��� �߻�
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetTextExtentPoint32(hdc, str[lineNum], xPos, &size); //--- ĳ�� ��ġ �˾Ƴ���

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