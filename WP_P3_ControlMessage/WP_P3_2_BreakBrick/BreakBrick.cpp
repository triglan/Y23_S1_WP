#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>
#include <random>

#define WINDOWSIZE 800
#define XSIZE 30
#define YSIZE 15
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 1";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

struct BreakBrick {
	int x;
	int y;
	int xsize;
	int ysize;

	int a, b, c;
};



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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 300, 200, WINDOWSIZE + 18, WINDOWSIZE + 41, NULL, (HMENU)NULL, hInstance, NULL);
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
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH hBrush, oldBrush;

	//벽돌 만들기
	static BreakBrick player;
	static BreakBrick brick[100];
	static BreakBrick ball;

	static int brickCount = 0;
	switch (uMsg)
	{
	case WM_CREATE:
		player = { 400,700,40,15,30,200,200 };
		for (int i = 0; i < 30; i++)
		{//x,y,sizex,y,r,g,b
			brick[i] = { i % 10 * XSIZE * 2 + 100, (i / 10 * 20) + 100 + 20, 30, 10, 100, 100, 100 };
			brickCount++;
		}

	case WM_PAINT:
		//기본 생성
		hdc = BeginPaint(hwnd, &ps);

		//벽돌 그리기
		hBrush = CreateSolidBrush(RGB(brick[0].a, brick[0].b, brick[0].c));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		for (int i = 0; i < brickCount; i++)
		{
			Rectangle(hdc, brick[i].x - brick[i].xsize, brick[i].y - brick[i].ysize, brick[i].x + brick[i].xsize, brick[i].y + brick[i].ysize);

		}





		SelectObject(hdc, oldBrush); // 이전의 펜으로 돌아감
		DeleteObject(oldBrush);
		EndPaint(hwnd, &ps);
		break;

	case WM_RBUTTONDOWN:

		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:

		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_CHAR:

		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
