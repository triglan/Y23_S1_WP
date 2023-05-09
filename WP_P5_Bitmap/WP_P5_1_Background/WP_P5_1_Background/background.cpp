#include <windows.h> //--- 윈도우 헤더 파일
#include <tchar.h>
#include<stdio.h>
#include"resource.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#define WINDOWSIZE 800

typedef struct {
	int x, y;	//x,y
	int sx, sy;	//size x,y
	int subx, suby;
}pictures;
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

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

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{//5개면 마우스 이동x
	PAINTSTRUCT ps;
	HDC hdc, memdc;
	HBRUSH hBrush, oldBrush;
	static HBITMAP hBitmap;

	static RECT t;//
	static DWORD scopy = SRCCOPY;//반전색인지 아닌지

	static bool full = true;//사진 꽉채웠는지
	static pictures pic;	//메인 함수
	switch (uMsg) {
	case WM_CREATE:
	{
		hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
		pic.x = 0, pic.y = 0, pic.sx = 600, pic.sy = 600;
	}
		break;
	case WM_PAINT:
		printf("x : %d sx : %d sy : %d\n", pic.x, pic.sx, pic.sy);
		hdc = BeginPaint(hwnd, &ps);
		memdc = CreateCompatibleDC(hdc);
		SelectObject(memdc, hBitmap);
		
		
		//원본사진
		if (full == false) {
			BitBlt(hdc, 0, 0, 224, 219, memdc, 0, 0, scopy);
		}
		//분할사진
		if (full == true) {//메인사진 4개, 서브사진 4개 * 2 + 여유 있으면 하나 더
			//왼쪽 복사본
			//StretchBlt(hdc, 0, 0, pic.sx, pic.sy, memdc,												pic.x, 0, 224, 219, scopy);
			//StretchBlt(hdc, pic.sx, 0, WINDOWSIZE - pic.sx, pic.sy, memdc,							pic.x, 0, 224, 219, scopy);
			//StretchBlt(hdc, 0, pic.sy, pic.sx, WINDOWSIZE - pic.sy, memdc,							pic.x, 0, 224, 219, scopy);
			////StretchBlt(hdc, pic.sx, pic.sy, WINDOWSIZE - pic.sx, WINDOWSIZE - pic.sy, memdc,	pic.x, 0, 224, 219, scopy);
			////오른쪽 복사본
			//StretchBlt(hdc, pic.sx - 3 * pic.x,	0,					pic.sx, pic.sy, memdc,							0, 0, 224, 219, scopy);
			//StretchBlt(hdc, WINDOWSIZE - 3 * pic.x, 0,				WINDOWSIZE - pic.sx, pic.sy, memdc,						pic.x, 0, 224, 219, scopy);
			//StretchBlt(hdc, 0, pic.sy,								pic.sx, WINDOWSIZE - pic.sy, memdc,						pic.x, 0, 224, 219, scopy);
			//StretchBlt(hdc, pic.sx, pic.sy,							WINDOWSIZE - pic.sx, WINDOWSIZE - pic.sy, memdc,	pic.x, 0, 224, 219, scopy);

			StretchBlt(hdc, pic.x, 0,					pic.sx, pic.sy, memdc,										0, 0, 224, 219, scopy);


			StretchBlt(hdc, pic.x + pic.sx, 0,					WINDOWSIZE - pic.sx, pic.sy, memdc,						0, 0, 224, 219, scopy);
			StretchBlt(hdc, 0, pic.sy,					pic.sx, WINDOWSIZE - pic.sy, memdc,						pic.x, 0, 224, 219, scopy);
			StretchBlt(hdc, pic.sx, pic.sy,				WINDOWSIZE - pic.sx, WINDOWSIZE - pic.sy, memdc,	pic.x, 0, 224, 219, scopy);
		}
		
		
		
		DeleteDC(memdc);
		EndPaint(hwnd, &ps);
		break;

	case WM_KEYDOWN:
		if (wParam == VK_LEFT) {
			pic.x -= 10;
		}
		if (wParam == VK_RIGHT) {
			pic.x += 10;
		}
	case WM_LBUTTONDOWN:
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		DeleteObject(hBitmap);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam); //--- 위의 세 메시지 외의 나머지 메시지는 OS로
}
