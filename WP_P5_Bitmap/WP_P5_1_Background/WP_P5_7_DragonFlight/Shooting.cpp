#include <windows.h> //--- 윈도우 헤더 파일
#include <tchar.h>
#include<stdio.h>
#include"resource.h"
#include <atlimage.h>

//투명 비트맵 처리 
#pragma comment(lib, "msimg32.lib")
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#define WINDOWSIZE 800

typedef struct {
	int x, y;
	int move;
	int state;
	int speed;
	int size;
}copypaste;

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

static HBITMAP hBitmap, hBitmap2, oldmap;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
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
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	WndClass.lpszMenuName = NULL;

	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 500, 100, WINDOWSIZE + 16, WINDOWSIZE + 35, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

//CImage를 사용한 이미지 출력
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{//5개면 마우스 이동x
	PAINTSTRUCT ps;
	HDC hdc, mdc;
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	static CImage img, idle, jump, lying;
	static RECT rt;//

	static float angle;
	switch (uMsg) {
	case WM_CREATE:
	{
		img.LoadFromResource(g_hInst, IDB_BITMAP2); //--- background
		idle.LoadFromResource(g_hInst, IDB_BITMAP1); //--- sprite image
		jump.LoadFromResource(g_hInst, IDB_BITMAP3); //--- sprite image
		lying.LoadFromResource(g_hInst, IDB_BITMAP4); //--- sprite image
		GetClientRect(hwnd, &rt);

		SetTimer(hwnd, 1, 100, NULL);
	}
	break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
		}
		InvalidateRect(hwnd, NULL, false);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		mdc = CreateCompatibleDC(hdc);

		(HBITMAP)SelectObject(mdc, hBitmap);

		w = img.GetWidth();
		h = img.GetHeight();

		img.Draw(mdc, 0, 0, rt.right, rt.bottom, 0, 0, w, h); //--- 메모리 DC에 배경 그리기

		TransparentBlt(mdc, won[i].x, won[i].y, won[i].size, won[i].size, jump.GetDC(), 19 * timer1, 0, 18, 25, RGB(235, 197, 241));
		jump.ReleaseDC();

		BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY); //--- 메모리 DC의 그림을 화면 DC에 복사하기

		DeleteObject(hBitmap);
		DeleteDC(mdc);
		InvalidateRect(hwnd, NULL, false);
		EndPaint(hwnd, &ps);
		break;

	case WM_CHAR:
		InvalidateRect(hwnd, NULL, false);
		break;
	case WM_DESTROY:
		//DeleteObject(hBitmap);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam); //--- 위의 세 메시지 외의 나머지 메시지는 OS로
}
