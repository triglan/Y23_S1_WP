#include <windows.h> //--- 윈도우 헤더 파일
#include <tchar.h>
#include<stdio.h>
#include"resource.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
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
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 550, 680, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc, memdc;
	HPEN hp, oldp;
	HBRUSH hBrush, oldBrush;
	static HBITMAP hbitmap;
	static int x[4], y[4];
	static int subx[4], suby[4];
	static int bx, by;
	static int mov1[2] = { 0,0 };
	static int mov2[2] = { 0,0 };
	static int sizex[4], sizey[4];
	static int subsizex[4], subsizey[4];
	static int invert = 0;
	static int a = 0;
	static int p = 0;
	static int r = 0;
	static int s = 10;
	static RECT t;//
	int mx, my;
	//--- 메시지 처리하기
	switch (uMsg) {
	case WM_CREATE:
		x[0] = 0, y[0] = 0;

		sizex[0] = 400, sizey[0] = 500;
		for (int i = 1; i < 4; i++) {
			x[i] = x[0];
			y[i] = y[0];
			sizex[i] = sizex[0];
			sizey[i] = sizey[0];
		}

		hbitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		memdc = CreateCompatibleDC(hdc); //--- 3) 메모리 DC 만들기
		SelectObject(memdc, hbitmap); //--- 4) 비트맵 선택하기

		BitBlt(hdc, 0, 0, 330, 240, memdc, 0, 0, SRCCOPY);
		if (invert == 0) {
			if (a == 1) {
				for (int i = 0; i < 4; i++) {
					StretchBlt(hdc, subx[i], suby[i], sizex[i], sizey[i], memdc, 0, 0, 550, 660, SRCCOPY);
				}
				for (int i = 1; i < 4; i++) {
					StretchBlt(hdc, x[i], y[i], sizex[i], sizey[i], memdc, 0, 0, 550, 660, SRCCOPY);
				}
			}
			StretchBlt(hdc, x[0], y[0], sizex[0], sizey[0], memdc, 0, 0, 550, 660, SRCCOPY);
		}
		else if (invert == 1) {
			if (a == 1) {
				for (int i = 1; i < 4; i++) {
					StretchBlt(hdc, x[i], y[i], sizex[i], sizey[i], memdc, 0, 0, 550, 660, NOTSRCCOPY);
				}
			}
			StretchBlt(hdc, x[0], y[0], sizex[0] - r, sizey[0], memdc, 0 + r, 0, 550, 660, NOTSRCCOPY);

		}

		if (s == 0 || s == 1 || s == 2 || s == 3) {
			hBrush = CreateSolidBrush(RGB(255, 0, 0)); // GDI: 브러시 만들기
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush); // 새로운 브러시 선택하기
			FrameRect(hdc, &t, hBrush);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
		}

		DeleteDC(memdc);

		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_LEFT) {
			if (p == 0) {
				if (mov1[0] == 0) {
					mov1[1] = 1;
					x[s] -= 10;

					subx[s] = x[s] + sizex[s];
					suby[s] = y[s];
					if ((s == 0 || s == 2) && subx[s] <= 0) {
						mov1[0] = 1;
						x[s] = subx[s] + sizex[s];
					}
					if ((s == 1 || s == 3) && (bx >= x[s] + sizex[s])) {
						mov1[0] = 1;
						x[s] = subx[s] + sizex[s];
					}
				}
				else if (mov1[0] == 1) {
					mov1[1] = 0;
					subx[s] -= 10;
					x[s] = subx[s] + sizex[s];
					y[s] = suby[s];
					if ((s == 0 || s == 2) && x[s] <= 0) {
						mov1[0] = 0;
						subx[s] = x[s] + sizex[s];
					}
					if ((s == 1 || s == 3) && (bx >= subx[s] + sizex[s])) {
						mov1[0] = 0;
						subx[s] = x[s] + sizex[s];
					}

				}
			}
			if (p == 1) {
				for (int i = 0; i < 4; i++) {
					if (mov1[0] == 0) {
						mov1[1] = 1;
						x[i] -= 10;
						subx[i] = x[i] + sizex[i];
						suby[i] = y[i];
						if ((i == 0 || i == 2) && subx[i] <= 0) {
							mov1[0] = 1;
							x[i] = subx[i] + sizex[i];
						}
						if ((i == 1 || i == 3) && (bx >= x[i] + sizex[i])) {
							mov1[0] = 1;
							x[i] = subx[i] + sizex[i];
						}
					}
					else if (mov1[0] == 1) {
						mov1[1] = 0;
						subx[i] -= 10;
						x[i] = subx[i] + sizex[i];
						y[i] = suby[i];
						if ((i == 0 || i == 2) && x[i] <= 0) {
							mov1[0] = 0;
							subx[i] = x[i] + sizex[i];
						}
						if ((i == 1 || i == 3) && (bx >= subx[i] + sizex[i])) {
							mov1[0] = 0;
							subx[i] = x[i] + sizex[i];
						}

					}
				}
			}
		}
		if (wParam == VK_RIGHT) {
			if (p == 0) {
				if (mov1[1] == 0) {
					mov1[0] = 1;
					x[s] += 10;
					subx[s] = x[s] - sizex[s];
					suby[s] = y[s];
					if ((s == 0 || s == 2) && subx[s] >= 0) {
						mov1[1] = 1;
						x[s] = subx[s] - sizex[s];
					}
					if ((s == 1 || s == 3) && x[s] >= 550) {
						mov1[1] = 1;
						x[s] = subx[s] - sizex[s];
					}
				}
				else if (mov1[1] == 1) {
					mov1[0] = 0;
					subx[s] += 10;
					x[s] = subx[s] - sizex[s];
					y[s] = suby[s];
					if ((s == 0 || s == 2) && x[s] >= 0) {
						mov1[1] = 0;
						subx[s] = x[s] - sizex[s];
					}
					if ((s == 1 || s == 3) && (subx[s] >= 550)) {
						mov1[1] = 0;
						subx[s] = x[s] - sizex[s];
					}

				}
			}
			if (p == 1) {
				for (int i = 0; i < 4; i++) {
					if (mov1[1] == 0) {
						mov1[0] = 1;
						x[i] += 10;
						subx[i] = x[i] - sizex[i];
						suby[i] = y[i];
						if ((i == 0 || i == 2) && subx[i] >= 0) {
							mov1[1] = 1;
							x[i] = subx[i] - sizex[i];
						}
						if ((i == 1 || i == 3) && x[i] >= 550) {
							mov1[1] = 1;
							x[i] = subx[i] - sizex[i];
						}
					}
					else if (mov1[1] == 1) {
						mov1[0] = 0;
						subx[i] += 10;
						x[i] = subx[i] - sizex[i];
						y[i] = suby[i];
						if ((i == 0 || i == 2) && x[i] >= 0) {
							mov1[1] = 0;
							subx[i] = x[i] - sizex[i];
						}
						if ((i == 1 || i == 3) && (subx[i] >= 550)) {
							mov1[1] = 0;
							subx[i] = x[i] - sizex[i];
						}

					}
				}
			}
		}
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_CHAR:
		if (wParam == 'p') {
			if (p == 0) {
				t.left = 0;
				t.top = 0;
				t.right = 550;
				t.bottom = 660;
				x[0] = 0;
				y[0] = 0;
				x[1] = x[0] + sizex[0];
				y[1] = y[0];
				x[2] = x[0];
				y[2] = y[0] + sizey[0];
				x[3] = x[0] + sizex[0];
				y[3] = y[0] + sizey[0];
				for (int j = 0; j < 4; j++) {
					subx[j] = x[j];
					suby[j] = y[j];
				}
				p = 1;
			}
			else if (p == 1) {
				p = 0;
				s = 10;
			}
		}
		if (wParam == 'a') {
			sizex[0] = 550, sizey[0] = 660;
			x[1] = x[0] + sizex[0];
			sizex[1] = 550 - sizex[0];
			y[2] = y[0] + sizey[0];
			sizey[2] = 660 - sizey[0];
			x[3] = x[0] + sizex[0];
			sizex[3] = 550 - sizex[0];
			y[3] = y[0] + sizey[0];
			sizey[3] = 660 - sizey[0];
			a = 1;
		}
		if (wParam == 'r') {
			if (invert == 0) {
				invert = 1;
			}
			else if (invert == 1) {
				invert = 0;
			}
		}
		if (wParam == '+') {
			if (a == 1) {
				s = 5;
				x[0] = 0;
				y[0] = 0;
				sizex[0] += 20;
				sizey[0] += 24;
				for (int i = 1; i < 4; i++) {
					x[i] = x[0];
					y[i] = y[0];
					sizex[i] = sizex[0];
					sizey[i] = sizey[0];
				}
				x[1] = x[0] + sizex[0];
				sizex[1] = 550 - sizex[0];
				y[2] = y[0] + sizey[0];
				sizey[2] = 660 - sizey[0];
				x[3] = x[0] + sizex[0];
				sizex[3] = 550 - sizex[0];
				y[3] = y[0] + sizey[0];
				sizey[3] = 660 - sizey[0];
				if (sizex[0] >= 550 || sizey[0] >= 660) {//이해 하기
					sizex[0] -= 20;
					sizey[0] -= 24;
					x[1] = x[0] + sizex[0];
					sizex[1] = 550 - sizex[0];
					y[2] = y[0] + sizey[0];
					sizey[2] = 660 - sizey[0];
					x[3] = x[0] + sizex[0];
					sizex[3] = 550 - sizex[0];
					y[3] = y[0] + sizey[0];
					sizey[3] = 660 - sizey[0];
				}
			}
			for (int i = 0; i < 4; i++) {
				subx[i] = x[i];
				suby[i] = y[i];
			}
			bx = sizex[0];
			by = sizey[0];
		}
		if (wParam == '-') {
			if (a == 1) {
				s = 5;
				x[0] = 0;
				y[0] = 0;
				sizex[0] -= 20;
				sizey[0] -= 24;
				for (int i = 1; i < 4; i++) {
					x[i] = x[0];
					y[i] = y[0];
					sizex[i] = sizex[0];
					sizey[i] = sizey[0];
				}
				x[1] = x[0] + sizex[0];
				sizex[1] = 550 - sizex[0];
				y[2] = y[0] + sizey[0];
				sizey[2] = 660 - sizey[0];
				x[3] = x[0] + sizex[0];
				sizex[3] = 550 - sizex[0];
				y[3] = y[0] + sizey[0];
				sizey[3] = 660 - sizey[0];
				if (sizex[0] <= 50 || sizey[0] <= 60) {
					sizex[0] += 20;
					sizey[0] += 24;
					sizey[1] += 24;
					sizex[2] += 20;
					x[1] = x[0] + sizex[0];
					sizex[1] = 550 - sizex[0];
					y[2] = y[0] + sizey[0];
					sizey[2] = 660 - sizey[0];
					x[3] = x[0] + sizex[0];
					sizex[3] = 550 - sizex[0];
					y[3] = y[0] + sizey[0];
					sizey[3] = 660 - sizey[0];

				}
				for (int i = 0; i < 4; i++) {
					subx[i] = x[i];
					suby[i] = y
						[i];
				}
				bx = sizex[0];
				by = sizey[0];
			}

		}
		if (wParam == 'q') {
			PostQuitMessage(0);
		}
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		for (int i = 0; i < 4; i++) {
			if (a == 1) {
				if (x[i] <= mx && mx <= x[i] + sizex[i] && y[i] <= my && my <= y[i] + sizey[i]) {
					s = i;
					t.left = x[s];
					t.top = y[s];
					t.right = x[s] + sizex[s];
					t.bottom = y[s] + sizey[s];
					x[0] = 0;
					y[0] = 0;
					x[1] = x[0] + sizex[0];
					y[1] = y[0];
					x[2] = x[0];
					y[2] = y[0] + sizey[0];
					x[3] = x[0] + sizex[0];
					y[3] = y[0] + sizey[0];
					for (int j = 0; j < 4; j++) {
						subx[j] = x[j];
						suby[j] = y[j];
					}
				}
			}
		}

		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam); //--- 위의 세 메시지 외의 나머지 메시지는 OS로
}
