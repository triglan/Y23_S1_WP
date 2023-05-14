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
}pictures;
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

//msimg32를 사용한 이미지 출력
//LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
//{//5개면 마우스 이동x
//	PAINTSTRUCT ps;
//	HDC hdc, mdc;
//	HBRUSH hBrush, oldBrush;
//	HPEN hPen, oldPen;
//
//	static CImage img, imgSprite;
//	static int xPos = 0, yPos = 0;
//	static RECT rt;//
//	static DWORD scopy = SRCCOPY;//반전색인지 아닌지
//
//	static int timer1 = 0;
//	switch (uMsg) {
//	case WM_CREATE:
//		hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
//		SetTimer(hwnd, 1, 100, NULL);
//		break;
//	case WM_TIMER:
//		switch (wParam)
//		{
//		case 1:
//			timer1++;
//			timer1 = timer1 % 4;
//			printf("timer : %d %d\n", timer1*52, (timer1 +1)*52);
//			break;
//		}
//	case WM_PAINT:
//		hdc = BeginPaint(hwnd, &ps);
//		mdc = CreateCompatibleDC(hdc);
//
//		SelectObject(mdc, hBitmap);
//		TransparentBlt(hdc, 0, 0, 52, 60, mdc, timer1 * 52, 0, 52, 58, RGB(235, 197, 241)); //--- 마지막 인자를 RGB(0, 0, 0)으로 설정: 검정색을 투명하게 설정한다
//		DeleteDC(mdc);
//		
//		InvalidateRect(hwnd, NULL, false);
//		EndPaint(hwnd, &ps);
//		break;
//	case WM_DESTROY:
//		DeleteObject(hBitmap);
//		PostQuitMessage(0);
//		break;
//	}
//	return DefWindowProc(hwnd, uMsg, wParam, lParam); //--- 위의 세 메시지 외의 나머지 메시지는 OS로
//}

//CImage를 사용한 이미지 출력
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{//5개면 마우스 이동x
	PAINTSTRUCT ps;
	HDC hdc, mdc;
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	static CImage img, imgSprite;
	static int xPos = 0, yPos = 0;
	static RECT rt;//
	static DWORD scopy = SRCCOPY;//반전색인지 아닌지

	static int timer1 = 0;
	switch (uMsg) {
	case WM_CREATE:
	{
		hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		SetTimer(hwnd, 1, 100, NULL);
	}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			timer1++;
			timer1 = timer1 % 4;
			printf("timer : %d %d\n", timer1*52, (timer1 +1)*52);
			break;
		}
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		mdc = CreateCompatibleDC(hdc);

		SelectObject(mdc, hBitmap);
		
		w = img.GetWidth();
		h = img.GetHeight();

		DeleteDC(mdc);
		
		InvalidateRect(hwnd, NULL, false);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(hBitmap);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam); //--- 위의 세 메시지 외의 나머지 메시지는 OS로
}

