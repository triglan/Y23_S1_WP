#include <windows.h>
#include <tchar.h>
#include<stdio.h>

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
	static TCHAR str[100];
	static int count;

	static int x;
	static int y[10];
	static int n[3];
	static int m[3];


	static int yPos = 0;


	//Test
	static TCHAR test[100];

	switch (uMsg)
	{
	case WM_CREATE:
		CreateCaret(hwnd, NULL, 5, 15); //--- ĳ�� �����
		ShowCaret(hwnd);				//--�� ȭ�鿡 ĳ�� ǥ��
		count = 0;
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);
		if (wParam == VK_BACK) //--- �齺���̽��� �Է��ϸ�
			count--; //--- �� ĭ ����
		else if (wParam == VK_RETURN) //--- ����Ű�� �Է��ϸ�: ���ڿ��� �����ٿ� ���
		{
			count = 0; //--- �ε��� ����
			yPos = yPos + 20; //--- y ��ġ ����: �� �� �Ʒ��� ���
		}
		else
			str[count++] = wParam; //--- �� �ܿ��� ���ڸ� ���ڿ� �� �ڿ� ���δ�.
		str[count] = '\0';
		TextOut(hdc, 0, yPos, str, lstrlen(str));
		ReleaseDC(hwnd, hdc);

		InvalidateRect(hwnd, NULL, TRUE); //--- WM_PAINT �޽��� �߻�
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetTextExtentPoint32(hdc, str, lstrlen(str), &size); //--- ���ڿ� ���� �˾Ƴ���
		TextOut(hdc, 0, yPos, str, lstrlen(str));
		SetCaretPos(size.cx, yPos); //--- ĳ�� ��ġ�ϱ�
		EndPaint
		(hwnd, &ps);
		break;
	case WM_DESTROY:
		HideCaret(hwnd); //--- ĳ�� �����
		DestroyCaret(); //--- ĳ�� �����ϱ�
		PostQuitMessage(0);
		break;


	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}