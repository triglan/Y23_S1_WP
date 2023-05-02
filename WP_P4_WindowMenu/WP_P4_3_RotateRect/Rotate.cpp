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
	int scir;
	int size;
	int r, g, b;
	int clock;
	int sclock;
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

	HPEN hp, oldp;

	static MakeCir cir[10];

	static int Timer1 = 0;
	static int Speed = 100;
	//계산
	const double PI = 3.1415926;
	static double a, b, c;

	static bool stop = false;
	static int sx;
	static int sy;

	static int select = 0;
	static bool selected = false;
	switch (uMsg) {
	case WM_CREATE:
		srand(time(NULL));
		for (int i = 0; i < 10; i++){
			cir[i].x = rand() % 600 + 100, cir[i].y = rand() % 600 + 100;
			cir[i].size = rand() % 50 + 25;
			cir[i].r = rand() % 256, cir[i].g = rand() % 256, cir[i].b = rand() % 256;
			for (int j = 0; j < 9; j++){
				cir[i].angle[j] = j * 40;
			}
			cir[i].clock = rand() % 2;
			cir[i].sclock = rand() % 2;
			cir[i].scir = 0;
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

		if (!stop) {
			if (Timer1 % 5) {
				for (int i = 0; i < 10; i++) {
					if (cir[i].clock % 2 == 0) {
						for (int j = 0; j < 9; j++) {
							cir[i].angle[j] -= 5;
						}
					}
					else {
						for (int j = 0; j < 9; j++) {
							cir[i].angle[j] += 5;
						}
					}
					if (cir[i].sclock % 2 == 0) {
						cir[i].scir += 5;
					}
					else {
						cir[i].scir -= 5;
					}
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
			a = cir[i].x + (cir[i].size + 10) * sin(cir[i].scir * PI / 180), b = cir[i].y + (cir[i].size + 10) * cos(cir[i].scir * PI / 180);
			Ellipse(mdc, a - 10, b - 10, a + 10, b + 10);
			//직선 그리기
			for (int j = 0; j < 9; j++)
			{
				hp = CreatePen(PS_SOLID, 3, RGB(100, 100, 100));
				oldp = (HPEN)SelectObject(mdc, hp);
				a = (cir[i].size) * sin(cir[i].angle[j] * PI / 180), b = (cir[i].size) * cos(cir[i].angle[j] * PI / 180);
				MoveToEx(mdc, cir[i].x, cir[i].y, NULL);
				LineTo(mdc, cir[i].x + a, cir[i].y + b);
				SelectObject(mdc, oldp); // 이전의 펜으로 돌아감
				DeleteObject(hp);
			}
		}
		BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
		break;
	case WM_COMMAND: //--- 메뉴를 선택했을 때
		switch (LOWORD(wParam)) { //--- 선택된 메뉴의 id가 저장되어 있다
		case ID_MOVE_1:
			for (int i = 0; i < 10; i++){
				cir[i].clock += 1;
			}
			break;
		case ID_MOVE_2:
			for (int i = 0; i < 10; i++) {
				cir[i].sclock += 1;
			}
			break;
		case ID_MOVE_3:
			if (stop == true)
				stop = false;
			else
				stop = true;
			break;
		case ID_CHANGE_CHANGE:
		{
			int r;
			for (int i = 0; i < 10; i++) {
				r = rand() % 2;
				if (r % 2 == 0) {
					cir[i].r = 255 - cir[i].r, cir[i].g = 255 - cir[i].g, cir[i].b = 255 - cir[i].b;
				}
			}
		}
			break;
		case ID_CHANGE_RED:
			for (int i = 0; i < 10; i++) {
					cir[i].r = 255, cir[i].g = 0, cir[i].b = 0;
				
			}
			break;
		case ID_CHANGE_GREEN:
			for (int i = 0; i < 10; i++) {
					cir[i].r = 0, cir[i].g = 255, cir[i].b = 0;
				
			}
			break;
		case ID_CHANGE_BLUE:
			for (int i = 0; i < 10; i++) {
				cir[i].r = 0, cir[i].g = 0, cir[i].b = 255;
			}
			break;
		case ID_CHANGE_RANDOM:
		{
			int r, g, b;
			r = rand() % 256, g = rand() % 256, b = rand() % 256;
			for (int i = 0; i < 10; i++) {
				cir[i].r = r, cir[i].g = g, cir[i].b = b;
			}
		}
			break;
		case ID_GAME_RESET:
			srand(time(NULL));
			for (int i = 0; i < 10; i++) {
				cir[i].x = rand() % 600 + 100, cir[i].y = rand() % 600 + 100;
				cir[i].size = rand() % 50 + 25;
				cir[i].r = rand() % 256, cir[i].g = rand() % 256, cir[i].b = rand() % 256;
				for (int j = 0; j < 9; j++) {
					cir[i].angle[j] = j * 40;
				}
				cir[i].clock = rand() % 2;
				cir[i].scir = 0;
			}
			SetTimer(hwnd, 1, Speed, NULL);
			break;
		case ID_GAME_QUIT:
			PostQuitMessage(0);
			break;
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONDOWN:
	{
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		for (int i = 0; i < 10; i++){
			if (cir[i].size * cir[i].size > (sy - cir[i].y) * (sy - cir[i].y) + (sx - cir[i].x) * (sx - cir[i].x)) {
				cir[i].clock += 1;
				cir[i].sclock += 1;
				selected = true;
			}
		}
		if (!selected) {//말로는 이상한데 맞는 코드긴함 원이 선택됐다는거고 원이 선택 안됐을 때 실행한다 치면 될 듯
			cir[select%10].x = sx, cir[select%10].y = sy;
			cir[select%10].size = rand() % 50 + 25;
			cir[select%10].r = rand() % 256, cir[select%10].g = rand() % 256, cir[select%10].b = rand() % 256;
			for (int j = 0; j < 9; j++) {
				cir[select%10].angle[j] = j * 40;
			}
			cir[select%10].clock = rand() % 2;
			cir[select%10].scir = 0;
			select++;
		}
		selected = false;
	}
	InvalidateRgn(hwnd, NULL, TRUE);
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam); //--- 위의 세 메시지 외의 나머지 메시지는 OS로
}