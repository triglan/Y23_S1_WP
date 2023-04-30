#include <windows.h> //--- 윈도우 헤더 파일
#include <tchar.h>
#include <stdio.h>
#include "resource.h"
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#define WINDOWSIZE 800

typedef struct {
	int sx, sy;
	int ex, ey;
	int r, g, b;
}MakeRectangle;

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

	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU2);

	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, WINDOWSIZE+20, WINDOWSIZE+90, NULL, (HMENU)NULL, hInstance, NULL);
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
	static int startX, startY, oldX, oldY;
	static int mx, my;
	static int sx, sy;
	static int ex, ey;
	static int movex, movey;
	static int startx, starty, endx, endy;

	static int select = -1;

	//도형
	static RECT fig[5];//검사용
	static RECT rt1, rt2, colrt[25];
	static int rcount = 0;
	static MakeRectangle r[5];
	static bool lclicked = false;
	static bool rclicked = false;
	static bool grid = false;
	static bool border = true;

	//크기
	static int space = 40;
	static int size = WINDOWSIZE / space;

	int colcount = 0;
	switch (uMsg) {
	case WM_CREATE:
		startX = oldX = 0; startY = oldY = 0;
		for (int i = 0; i < 5; i++)
		{
			r[i].r = 200, r[i].g = 200, r[i].b = 0;
			r[i].ex = 0, r[i].ey = 0, r[i].sx = 0, r[i].sy = 0;
		}
		break;
	case WM_PAINT:
		GetClientRect(hwnd, &rt);
		hdc = BeginPaint(hwnd, &ps);
		mdc = CreateCompatibleDC(hdc); //--- 메모리 DC 만들기
		hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom); //--- 메모리 DC와 연결할 비트맵 만들기
		SelectObject(mdc, (HBITMAP)hBitmap);

		printf("paint select : %d\n", select);
		//바탕색
		{
			hbr = CreateSolidBrush(RGB(255, 255, 255));
			oldbr = (HBRUSH)SelectObject(mdc, hbr);
			Rectangle(mdc, 0, 0, WINDOWSIZE, WINDOWSIZE);
			SelectObject(mdc, oldbr);
			DeleteObject(hbr);
		}
		//보드판
		{
			if (grid) {
				hp = CreatePen(PS_DOT, 0, RGB(0, 0, 0));
				oldp = (HPEN)SelectObject(mdc, hp);
			}
			else {
				hp = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				oldp = (HPEN)SelectObject(mdc, hp);
			}
			for (int x = 0; x <= space; x++)
			{
				MoveToEx(mdc, x * size, 0, NULL);
				LineTo(mdc, x * size, WINDOWSIZE);
			}
			for (int y = 0; y <= space; y++)
			{
				MoveToEx(mdc, 0, y * size, NULL);
				LineTo(mdc, WINDOWSIZE, y * size);
			}
			SelectObject(mdc, oldp); // 이전의 펜으로 돌아감
			DeleteObject(hp);
		}
		//사각형
		for (int i = 0; i <= rcount; i++){
			hbr = CreateSolidBrush(RGB(r[i].r, r[i].g, r[i].b));
			oldbr = (HBRUSH)SelectObject(mdc, hbr);
			if (border) {
				hp = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
				oldp = (HPEN)SelectObject(mdc, hp);
			}
			else {
				hp = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
				oldp = (HPEN)SelectObject(mdc, hp);
			}
			if (i == select) {
				SelectObject(mdc, oldp); // 이전의 펜으로 돌아감
				DeleteObject(hp);
				hp = CreatePen(PS_SOLID, 2, RGB(255, 100, 0));
				oldp = (HPEN)SelectObject(mdc, hp);
			}
			Rectangle(mdc, r[i].sx / size * size, r[i].sy / size * size, r[i].ex / size * size, r[i].ey / size * size);
			SelectObject(mdc, oldbr); // 이전의 펜으로 돌아감
			DeleteObject(hbr);
			SelectObject(mdc, oldp); // 이전의 펜으로 돌아감
			DeleteObject(hp);
		}
		for (int i = 0; i < rcount; i++){
			for (int j = 0; j < rcount; j++){
				rt1 = { r[i].sx, r[i].sy, r[i].ex, r[i].ey };
				rt2 = { r[j].sx, r[j].sy, r[j].ex, r[j].ey };
				if (IntersectRect(&colrt[colcount], &rt1, &rt2) && i != j) {
					hbr = CreateSolidBrush(RGB((r[i].r + r[j].r) / 2 , (r[i].g + r[j].g) / 2 , (r[i].b + r[j].b) / 2));
					oldbr = (HBRUSH)SelectObject(mdc, hbr);
					FillRect(mdc, &colrt[colcount], hbr);
				}
			}
		}
		BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
		break;
	case WM_COMMAND: //--- 메뉴를 선택했을 때
		switch (LOWORD(wParam)) { //--- 선택된 메뉴의 id가 저장되어 있다
		case ID_GRID:
			if (grid == false)
				grid = true;
			else
				grid = false;
			break;
		case ID_BORDER:
			if (border == false)
				border = true;
			else
				border = false;
			break;
		case ID_RED:
			r[select].r = 255, r[select].g = 0, r[select].b = 0;
			break;
		case ID_BLUE:
			r[select].r = 0, r[select].g = 0, r[select].b = 255;
			break;
		case ID_GREEN:
			r[select].r = 0, r[select].g = 255, r[select].b = 0;
			break;
		case ID_Cyan:
			r[select].r = 0, r[select].g = 255, r[select].b = 255;
			break;
		case ID_Magenta:
			r[select].r = 255, r[select].g = 0, r[select].b = 255;
			break;
		case ID_Yellow:
			r[select].r = 255, r[select].g = 255, r[select].b = 0;
			break;
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_CHAR:
	{
		printf("select : %d\n", select);
		if (wParam == '1') {
			select = 0;
		}
		if (wParam == '2') {
			select = 1;
		}
		if (wParam == '3') {
			select = 2;
		}
		if (wParam == '4') {
			select = 3;
		}
		if (wParam == '5') {
			select = 4;
		}
	}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		printf("x1 : %d y1 : %d x2 : %d y2 : %d\n", r[select].sx, r[select].ex, r[select].ex, r[select].ey);
		if (wParam == VK_UP && r[select].sy > 0) {
			r[select].ey -= size;
			r[select].sy -= size;
		}
		if (wParam == VK_DOWN && r[select].ey < WINDOWSIZE) {
			r[select].ey += size;
			r[select].sy += size;
		}
		if (wParam == VK_LEFT && r[select].sx > 0) {
			r[select].ex -= size;
			r[select].sx -= size;
		}
		if (wParam == VK_RIGHT && r[select].ex < WINDOWSIZE) {
			r[select].ex += size;
			r[select].sx += size;
		}
		InvalidateRgn(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONDOWN:
	{
		r[rcount].sx = r[rcount].ex = LOWORD(lParam) / size * size;
		r[rcount].sy = r[rcount].ey = HIWORD(lParam) / size * size;
		lclicked = true;
	}
		break;
	case WM_LBUTTONUP:
	{
		rcount++;
		lclicked = false;
		InvalidateRgn(hwnd, NULL, TRUE);
	}
		break;
	case WM_MOUSEMOVE:
	if(lclicked){
		int x, y;
		r[rcount].ex = LOWORD(lParam) / size * size;
		r[rcount].ey = HIWORD(lParam) / size * size;
		InvalidateRgn(hwnd, NULL, TRUE);
	}
	else if (rclicked) {
		ex = LOWORD(lParam);
		ey = HIWORD(lParam);
		movex = (ex - sx) / size * size , movey = (ey - sy) / size * size;
		r[select].ex = endx + movex, r[select].sx = startx + movex;
		r[select].ey = endy + movey, r[select].sy = starty + movey;
		InvalidateRgn(hwnd, NULL, TRUE);
	}
	break;
	case WM_RBUTTONDOWN:
	{
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		POINT pt;
		pt.x = sx;
		pt.y = sy;
		for (int i = 0; i < rcount; i++) {
			fig[i].left = r[i].sx, fig[i].right = r[i].ex,
				fig[i].top = r[i].sy, fig[i].bottom = r[i].ey;
			if (PtInRect(&fig[i], pt)) {
				select = i;
				rclicked = true;
				startx = r[i].sx, endx = r[i].ex;
				starty = r[i].sy, endy = r[i].ey;
			}
		}
	}
		break;
	case WM_RBUTTONUP:
		rclicked = false;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam); //--- 위의 세 메시지 외의 나머지 메시지는 OS로
}