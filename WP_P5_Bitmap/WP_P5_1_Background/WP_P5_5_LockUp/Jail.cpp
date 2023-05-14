#include <windows.h> //--- 윈도우 헤더 파일
#include <tchar.h>
#include <atlImage.h>
#include<stdlib.h>
#include<time.h>
#include"resource.h"
//#define _ATL_NO_AUTOMATIC_NAMESPACE  
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib, "msimg32.lib") 
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
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
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

	HBRUSH hbr, oldbr;
	HPEN hpen, oldpen;
	static CImage img, imgSprite[30][4];
	static int x[30], y[30];
	static int down[30];
	static int speed[30];
	static int w, h;
	static RECT rect;
	PAINTSTRUCT ps;
	HDC hdc;
	HDC mdc;
	HBITMAP hBitmap;
	static int num;
	static int drag = 0;
	static int startX = 0;
	static int startY = 0;
	static int endx = 0;
	static int endy = 0;
	static int one = 0;
	static RECT gl;
	static int  mx = 0, my = 0;
	static int click = 0;
	static int rx, ry;
	static int oldx, oldy;
	static int s[30];
	static int p = 0;
	srand((unsigned)time(NULL));
	//--- 메시지 처리하기
	switch (uMsg) {
	case WM_CREATE:
		num = 0;
		img.Load(L"bitmap1.bmp"); //--- background
		for (int i = 0; i < 30; i++) {
			imgSprite[i][0].Load(L"bitmap3.bmp"); //--- sprite image
			imgSprite[i][1].Load(L"bitmap5.bmp");
			imgSprite[i][2].Load(L"bitmap6.bmp");
			imgSprite[i][3].Load(L"bitmap5.bmp");
			x[i] = rand() % 750;
			y[i] = 0;
			down[i] = 0;
			s[i] = 0;
			speed[i] = rand() % 3 + 1;
		}

		GetClientRect(hWnd, &rect);

		SetTimer(hWnd, 1, 100, NULL);
		SetTimer(hWnd, 2, 30, NULL);
		SetTimer(hWnd, 3, 1000, NULL);
		break;
	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);
		hBitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
		mdc = CreateCompatibleDC(hdc);
		SelectObject(mdc, hBitmap);
		w = img.GetWidth();
		h = img.GetHeight();
		img.Draw(mdc, 0, 0, rect.right, rect.bottom, 0, 0, w, h); //--- 메모리 DC에 배경 그리기
		//TransparentBlt(mdc, xPos, yPos, 100, 100, imgSprite[num].GetDC(), 0, 0, 100, 100, RGB(255, 255, 255));
		for (int i = 0; i < 30; i++) {
			imgSprite[i][num].Draw(mdc, x[i], y[i], 60, 60, 0, 0, 100, 100);
		}
		hbr = CreateSolidBrush(RGB(255, 0, 0)); // GDI: 브러시 만들기
		oldbr = (HBRUSH)SelectObject(mdc, hbr);
		FrameRect(mdc, &gl, hbr); // 그리기
		SelectObject(mdc, oldbr);
		DeleteObject(hbr);

		BitBlt(hdc, 0, 0, rect.right, rect.bottom, mdc, 0, 0, SRCCOPY); //--- 메모리 DC의 그림을 화면 DC에 복사하기
		DeleteObject(hBitmap);
		DeleteDC(mdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_CHAR:
		if (wParam == 'p') {
			p = 1;
		}
		if (wParam == 'd') {
			gl.left = -1;
			gl.right = -1;
			gl.top = -1;
			gl.bottom = -1;

		}
		if (wParam == 'r') {
			drag = 0;
			startX = 0;
			startY = 0;
			endx = 0;
			endy = 0;
			one = 0;
			mx = 0, my = 0;
			click = 0;
			p = 0;
			for (int i = 0; i < 30; i++) {
				x[i] = rand() % 750;
				y[i] = 0;
				down[i] = 0;
				s[i] = 0;
				speed[i] = rand() % 3 + 1;
			}
		}
		InvalidateRgn(hWnd, NULL, false);
		break;
	case WM_LBUTTONDOWN:
		if (one == 0) {
			startX = LOWORD(lParam);
			startY = HIWORD(lParam);
			gl.left = startX;
			gl.top = startY;
			drag = 1;
			one = 1;
		}
		break;
	case WM_LBUTTONUP:
		drag = 0;
		rx = gl.right - gl.left;
		ry = gl.bottom - gl.top;
		break;
	case WM_RBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (gl.left <= mx && mx <= gl.right && gl.top <= my && my <= gl.bottom) {
			click = 1;
		}
		break;
	case WM_RBUTTONUP:
		click = 0;
		break;

	case WM_MOUSEMOVE:
		if (drag == 1) {
			endx = LOWORD(lParam);
			endy = HIWORD(lParam);
			gl.right = endx;
			gl.bottom = endy;
			InvalidateRgn(hWnd, NULL, false);
		}
		if (click == 1) {
			gl.left = LOWORD(lParam) - rx / 2;
			gl.top = HIWORD(lParam) - rx / 2;
			gl.right = gl.left + rx;
			gl.bottom = gl.top + ry;
			for (int i = 0; i < 30; i++) {
				if (gl.bottom >= y[i] + 30 && y[i] + 40 >= gl.bottom && gl.left <= x[i] && x[i] + 40 <= gl.right) {
					y[i] = gl.bottom - 40;

				}
				if (x[i] + 5 >= gl.left && gl.left >= x[i] && gl.bottom >= y[i]
					&& y[i] >= gl.top) {
					x[i] = gl.left;
				}
				if (x[i] + 40 - 5 <= gl.right && gl.right <= x[i] + 40 && gl.bottom >= y[i]
					&& y[i] >= gl.top) {
					x[i] = gl.right - 40;
				}
			}

			oldx = gl.right;
			InvalidateRgn(hWnd, NULL, false);
		}
		break;
	case WM_TIMER:
		switch (wParam) {
		case 1://TransparentBlt(MemDC, 50, 50, 50, 50, MemDCImage, 0, 0, 100, 100, RGB(255, 255, 255));
			if (p == 1) {
				num += 1;
				if (num == 4) {
					num = 0;
				}
			}
			break;
		case 2:
			if (p == 1) {
				for (int i = 0; i < 30; i++) {
					if (down[i] == 1) {
						y[i] += speed[i];
					}
					if (gl.bottom >= y[i] + 37 && y[i] + 40 >= gl.bottom && gl.left <= x[i] + 40 && x[i] <= gl.right) {
						y[i] -= speed[i];
					}
					if (y[i] >= 600) {
						for (int j = 0; j < 30; j++) {
							down[j] = 1;
						}
						y[i] = -60;
					}
				}
			}
			break;
		case 3:
			if (p == 1) {
				for (int i = 0; i < 30; i++) {
					if (rand() % 2 == 1) {
						down[i] = 1;
					}

				}
			}
			break;
		}
		InvalidateRect(hWnd, NULL, false);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam); //--- 위의 세 메시지 외의 나머지 메시지는 OS로
}