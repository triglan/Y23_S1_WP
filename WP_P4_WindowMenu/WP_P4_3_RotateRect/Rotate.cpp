#include <windows.h> //--- 윈도우 헤더 파일
#include <tchar.h>
#include <stdio.h>
#include <time.h>
#include<math.h>
#include "resource.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#define WINDOWSIZE 800

typedef struct {
	int x, y;
	int angle[9];
	int size;
	int r, g, b;
}MakeCir;

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

	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU2);

	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, WINDOWSIZE + 20, WINDOWSIZE + 90, NULL, (HMENU)NULL, hInstance, NULL);
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
	HDC hdc;
	HBRUSH hbr, oldbr;

	HDC mdc;
	HBITMAP hBitmap;
	RECT rt;	

	HPEN hp = 0, oldp = 0;

	static MakeCir cir[10];

	static int Timer1 = 0;
	static int Speed = 100;
	//계산
	const double PI = 3.1415926;
	static double a, b, c;
	switch (uMsg) {
	case WM_CREATE:
		srand(time(NULL));
		for (int i = 0; i < 10; i++){
			cir[i].x = rand() % 600 + 100, cir[i].y = rand() % 600 + 100;
			cir[i].size = rand() % 50 + 25;
			cir[i].r = rand() % 256, cir[i].g = rand() % 256, cir[i].b = rand() % 256;
			for (int j = 0; j < 9; j++){
				cir[i].angle[j] = j * 30;
			}

		}
		SetTimer(hwnd, 1, Speed, NULL);
		break;
	case WM_TIMER:

		switch (wParam)
		{
		case 1:
			Timer1++;
		default:
			break;
		}
		if (Timer1 % 5) {
			for (int i = 0; i < 10; i++){
				for (int j = 0; j < 9; j++){
					cir[i].angle[j] -= 10;
				}
			}
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rt);
		hdc = BeginPaint(hwnd, &ps);
		mdc = CreateCompatibleDC(hdc); //--- 메모리 DC 만들기
		hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom); //--- 메모리 DC와 연결할 비트맵 만들기
		SelectObject(mdc, (HBITMAP)hBitmap);
		
		//바탕색
		{
			hbr = CreateSolidBrush(RGB(255, 255, 255));
			oldbr = (HBRUSH)SelectObject(mdc, hbr);
			Rectangle(mdc, 0, 0, WINDOWSIZE, WINDOWSIZE);
			SelectObject(mdc, oldbr);
			DeleteObject(hbr);
		}
		//도형 그리기
		for (int i = 0; i < 10; i++) {
			hbr = CreateSolidBrush(RGB(cir[i].r, cir[i].g, cir[i].b));
			oldbr = (HBRUSH)SelectObject(mdc, hbr);
			Ellipse(mdc, cir[i].x - cir[i].size, cir[i].y - cir[i].size, cir[i].x + cir[i].size, cir[i].y + cir[i].size);
			SelectObject(mdc, oldbr); // 이전의 펜으로 돌아감
			DeleteObject(hbr);

			//작은 원
			a = cir[i].x + (cir[i].size + 10) * sin(cir[i].angle[0] * PI / 180), b = cir[i].y + (cir[i].size + 10)* cos(cir[i].angle[0] * PI / 180);
			Ellipse(mdc, a - 10, b - 10, a + 10, b + 10);
			//for (int j = 0; j < 9; j++)//직선 그리기
			//{
			//	hbr = CreateSolidBrush(RGB(cir[i].r, cir[i].g, cir[i].b));
			//	oldbr = (HBRUSH)SelectObject(mdc, hbr);
			//	Ellipse(mdc, b, a + 20, b + 20, a);
			//	SelectObject(mdc, oldbr); // 이전의 펜으로 돌아감
			//	DeleteObject(hbr);
			//}

		}
		BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
		break;
	case WM_COMMAND: //--- 메뉴를 선택했을 때
		switch (LOWORD(wParam)) { //--- 선택된 메뉴의 id가 저장되어 있다
		case ID_MOVE:
			break;
		case ID_CHANGE_CHANGE:
			break;
		case ID_CHANGE_RED:
			break;
		case ID_CHANGE_GREEN:
			break;
		case ID_CHANGE_BLUE:
			break;
		case ID_CHANGE_RANDOM:
			break;
		case ID_GAME_RESET:
			break;
		case ID_GAME_QUIT:
			break;
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_CHAR:
	{
		
	}
	InvalidateRgn(hwnd, NULL, TRUE);
	break;
	case WM_KEYDOWN:
		
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONDOWN:
	{
		
	}
	break;
	case WM_LBUTTONUP:
	{
	
	}
	break;
	case WM_MOUSEMOVE:
	
		break;
	case WM_RBUTTONDOWN:
	{
	}
	break;
	case WM_RBUTTONUP:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam); //--- 위의 세 메시지 외의 나머지 메시지는 OS로
}