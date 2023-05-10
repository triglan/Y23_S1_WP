#include <windows.h> //--- 윈도우 헤더 파일
#include <tchar.h>
#include<stdio.h>
#include"resource.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#define WINDOWSIZE 800

typedef struct {
	int x, y;	//x,y
	int sx, sy;	//size x,y
	int zoom;
	int cx, cy; //카피된 xy
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
	HPEN hPen, oldPen;
	static HBITMAP hBitmap, hBitmap2, oldmap;

	static RECT rt;//
	static DWORD scopy = SRCCOPY;//반전색인지 아닌지

	static int sx, sy, ex, ey;//마우스 좌표
	static int rsx, rsy, rex, rey;//마우스 좌표
	static int rx, ry;//우클릭 마우스 좌표
	static int startx, starty;
	static bool lclick, rclick;
	static bool reside = true, reup = true;

	static pictures lens;
	static pictures paste[5];
	static pictures copy;
	static pictures reset;
	static int Timer1Count = 0;

	static bool moving = false;
	static bool sizing = false;
	static int pastec = 0;
	static bool fullscreen = false;
	static int Picture = 1;
	switch (uMsg) {
	case WM_CREATE:
	{
		hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		hBitmap2 = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
		sx = -1, sy = -1, ex = -1, ey = -1;
		lens.x = sx, lens.y = sy, lens.sx = ex - sx, lens.sy = ey - ex, lens.zoom = 0;
		SetTimer(hwnd, 1, 200, NULL);
	}
	break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			Timer1Count++;
			if (moving) {
				if (Timer1Count % 2 == 0) {
					lens.x += 5;
				}
				else {
					lens.y += 5;
				}
			}
			if (sizing) {
				if (Timer1Count % 2 == 0) {
					lens.x += 5;
					lens.sx -= 10;
					lens.y += 5;
					lens.sy -= 10;
				}
				else {
					lens.x -= 5;
					lens.sx += 10;
					lens.y -= 5;
					lens.sy += 10;
				}
			}

			break;
		default:
			break;
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_PAINT:
		
		hdc = BeginPaint(hwnd, &ps);
		memdc = CreateCompatibleDC(hdc);

		//그림
		{
			//그림
			if(Picture == 1)
				SelectObject(memdc, hBitmap);
			else
				SelectObject(memdc, hBitmap2);

			BitBlt(hdc, 0, 0, 800, 800, memdc, 0, 0, scopy);
			//복사본

			if (reside && reup) {
				for (int i = 0; i < pastec; i++) {
					StretchBlt(hdc, paste[i].x, paste[i].y, paste[i].sx, paste[i].sy, memdc,
						paste[i].cx + (paste[i].zoom * paste[i].sx / 20) + paste[i].sx - 2 * (paste[i].zoom * paste[i].sx / 20), 
						paste[i].cy + (paste[i].zoom * paste[i].sy / 20) + paste[i].sy - 2 * (paste[i].zoom * paste[i].sy / 20),
						-(paste[i].sx - 2 * (paste[i].zoom * paste[i].sx / 20)), 
						-(paste[i].sy - 2 * (paste[i].zoom * paste[i].sy / 20)), scopy);//1오른쪽사진
				}
			}
			else if (reside) {
				for (int i = 0; i < pastec; i++) {
					StretchBlt(hdc, paste[i].x, paste[i].y, paste[i].sx, paste[i].sy, memdc,
						paste[i].cx + (paste[i].zoom * paste[i].sx / 20) + paste[i].sx - 2 * (paste[i].zoom * paste[i].sx / 20),
						paste[i].cy + (paste[i].zoom * paste[i].sy / 20),
						-(paste[i].sx - 2 * (paste[i].zoom * paste[i].sx / 20)), 
						paste[i].sy - 2 * (paste[i].zoom * paste[i].sy / 20), scopy);//1오른쪽사진
				}
			}
			else if (reup) {
				for (int i = 0; i < pastec; i++) {
					StretchBlt(hdc, paste[i].x, paste[i].y, paste[i].sx, paste[i].sy, memdc,
						paste[i].cx + (paste[i].zoom * paste[i].sx / 20),
						paste[i].cy + (paste[i].zoom * paste[i].sy / 20) + (paste[i].sy - 2 * (paste[i].zoom * paste[i].sy / 20)),
						paste[i].sx - 2 * (paste[i].zoom * paste[i].sx / 20),
						-(paste[i].sy - 2 * (paste[i].zoom * paste[i].sy / 20)), scopy);//1오른쪽사진
				}
			}
			else {
				for (int i = 0; i < pastec; i++) {
					StretchBlt(hdc, paste[i].x, paste[i].y, paste[i].sx, paste[i].sy, memdc,
						paste[i].cx + (paste[i].zoom * paste[i].sx / 20), paste[i].cy + (paste[i].zoom * paste[i].sy / 20),
						paste[i].sx - 2 * (paste[i].zoom * paste[i].sx / 20), paste[i].sy - 2 * (paste[i].zoom * paste[i].sy / 20), scopy);//1오른쪽사진
				}
			}
			
			//복사본 사각형
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			for (int i = 0; i < pastec; i++) {
				rt.left = paste[i].x, rt.top = paste[i].y, rt.right = paste[i].x + paste[i].sx, rt.bottom = paste[i].y + paste[i].sy;
				FrameRect(hdc, &rt, hBrush);
			}
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);

			//돋보기
			StretchBlt(hdc, lens.x, lens.y, lens.sx, lens.sy, memdc,
				lens.x + (lens.zoom * lens.sx / 20), lens.y + (lens.zoom * lens.sy / 20),
				lens.sx - 2 * (lens.zoom * lens.sx / 20), lens.sy - 2 * (lens.zoom * lens.sy / 20), scopy);//1오른쪽사진

			//돋보기 사각형
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			rt.left = lens.x, rt.top = lens.y, rt.right = lens.x + lens.sx, rt.bottom = lens.y + lens.sy;
			FrameRect(hdc, &rt, hBrush);
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);

			if (fullscreen) {
				StretchBlt(hdc, 0, 0, WINDOWSIZE, WINDOWSIZE, memdc,
					paste[pastec - 1].cx + (paste[pastec - 1].zoom * paste[pastec - 1].sx / 20), paste[pastec - 1].cy + (paste[pastec - 1].zoom * paste[pastec - 1].sy / 20),
					paste[pastec - 1].sx - 2 * (paste[pastec - 1].zoom * paste[pastec - 1].sx / 20), paste[pastec - 1].sy - 2 * (paste[pastec - 1].zoom * paste[pastec - 1].sy / 20), scopy);//1오른쪽사진
			}

			StretchBlt(hdc, 0, 0, 800, 800, memdc, 800, 0, 800, 800, scopy);
		}
		
		DeleteObject(hBrush);
		DeleteObject(oldBrush);

		DeleteDC(memdc);
		EndPaint(hwnd, &ps);
		break;
	case WM_CHAR:
		if (wParam == '1') {
			Picture = 1;
		}
		if (wParam == '2') {
			Picture = 2;
		}
		if (wParam == '+') {
		}
		if (wParam == 'e') {
			if(lens.zoom < 9)
			lens.zoom++;
		}
		if (wParam == 's') {
			if (lens.zoom > 0)
			lens.zoom--;
		}
		if (wParam == '0') {
			lens.zoom = 0;
		}
		if (wParam == 'c') {
			copy.sx = lens.sx, copy.sy = lens.sy;
			copy.cx = lens.x, copy.cy = lens.y;
			copy.zoom = lens.zoom;
			break;
		}
		if (wParam == 'p') {
			if (pastec >= 5)
				break;
			paste[pastec].x = rand() % 600, paste[pastec].y = rand() % 600;
			paste[pastec].sx = copy.sx, paste[pastec].sy = copy.sy;
			paste[pastec].cx = copy.cx, paste[pastec].cy = copy.cy;
			paste[pastec].zoom = copy.zoom;
			pastec++;
		}
		if (wParam == 'f') {
			if (fullscreen == false)
				fullscreen = true;
			else
				fullscreen = false;
		}
		if (wParam == 'r') {
			scopy = SRCCOPY;

			reside = true, reup = true;

			Timer1Count = 0;

			moving = false;
			sizing = false;
			pastec = 0;
			fullscreen = false;
			Picture = 1;

			lens.x = -1000, lens.y=-1000;
		}
		if (wParam == 'q') {
			PostQuitMessage(0);
		}
		if (wParam == 'm') {
			lens.x += 5;
			lens.sx -= 10;
			lens.y += 5;
			lens.sy -= 10;
		}
		if (wParam == 'n') {
			lens.x -= 5;
			lens.sx += 10;
			lens.y -= 5;
			lens.sy += 10;
		}
		if (wParam == 'x') {
			lens.x += 5;
			lens.sx -= 10;
		}
		if (wParam == 'X') {
			lens.x -= 5;
			lens.sx += 10;
		}
		if (wParam == 'y') {
			lens.y += 5;
			lens.sy -= 10;
		}
		if (wParam == 'Y') {
			lens.y -= 5;
			lens.sy += 10;
		}
		if (wParam == 'h') {
			if (reside)
				reside = false;
			else
				reside = true;
		}
		if (wParam == 'v') {
			if (reup)
				reup = false;
			else
				reup = true;
		}
		if (wParam == 'a') {
			if (moving)
				moving = false;
			else
				moving = true;
		}
		if (wParam == 'b') {
			if (sizing) {
				sizing = false;
				lens = reset;
			}
			else {
				sizing = true;
				reset = lens;
			}
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_LEFT) {
			lens.x -= 10;
			for (int i = 0; i < pastec; i++) {
				paste[i].cx -= 10;
			}
		}
		if (wParam == VK_RIGHT) {
			lens.x += 10;
			for (int i = 0; i < pastec; i++) {
				paste[i].cx += 10;
			}
		}
		if (wParam == VK_UP) {
			lens.y -= 10;
			for (int i = 0; i < pastec; i++) {
				paste[i].cy -= 10;
			}
		}
		if (wParam == VK_DOWN) {
			lens.y += 10;
			for (int i = 0; i < pastec; i++) {
				paste[i].cy += 10;
			}
		}

		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_MOUSEMOVE:
		if (lclick) {
			ex = LOWORD(lParam);
			ey = HIWORD(lParam);
			lens.x = sx, lens.y = sy, lens.sx = ex - sx, lens.sy = ey - sy;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		if (rclick) {
			rex = LOWORD(lParam);
			rey = HIWORD(lParam);
			lens.x = startx + rex - rsx;
			lens.y = starty + rey - rsy;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		break;
	case WM_RBUTTONDOWN:
	{
		rx = LOWORD(lParam);
		ry = HIWORD(lParam);
		if (rx > lens.x && ry > lens.y && rx < lens.x + lens.sx && lens.y + lens.sy) {//돋보기와 충돌 시
			rclick = true;
			rsx = LOWORD(lParam);
			rsy = HIWORD(lParam);
			startx = lens.x;
			starty = lens.y;
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}
	break;
	case WM_RBUTTONUP:
	{
		rclick = false;
		InvalidateRect(hwnd, NULL, TRUE);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		ex = LOWORD(lParam);
		sy = HIWORD(lParam);
		lclick = true;
	}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONUP:
	{
		ex = LOWORD(lParam);
		ey = HIWORD(lParam);
		lens.x = sx, lens.y = sy, lens.sx = ex - sx, lens.sy = ey - sy;
		lclick = false;
	}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		DeleteObject(hBitmap);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam); //--- 위의 세 메시지 외의 나머지 메시지는 OS로
}
