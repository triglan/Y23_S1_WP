#include <windows.h> //--- 윈도우 헤더 파일
#include <tchar.h>
#include<stdio.h>
#include "resource.h"
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
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);;
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
{//5개면 마우스 이동x
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH hbr, oldbr;
	HPEN hp=0, oldp=0;
	static te = 0;
	static c = 0;

	int mx, my;
	static int oldx[5], oldy[5];
	static int lclick=0;
	static int rclick = 0;
	static int sel;//fig선택
	static RECT fig[5];
	static int fcount = 0;//렉트 개수;
	static int col1[5];
	static int col2[5];
	static int col3[5];
	static int num=9;
	static RECT rap[10];
	static int rcol1[10];
	static int rcol2[10];
	static int rcol3[10];
	static int rcount = 0;
	//--- 메시지 처리하기
	switch (uMsg) {
	case WM_CREATE:
		col1[0] = 255, col2[0] = 0, col3[0] = 0, col1[1] = 0, col2[1] = 255, col3[1] = 0;
		col1[2] = 0, col2[2] = 0, col3[2] = 255, col1[3] = 0, col2[3] = 255, col3[3] = 255;
		col1[4] = 255, col2[4] = 0, col3[4] = 255;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < 41; i++) {
			MoveToEx(hdc, 0, 20 * i, NULL);
			LineTo(hdc, 800, 20 * i);
			MoveToEx(hdc, 20 * i, 0, NULL);
			LineTo(hdc, 20 * i, 800);
		}
		for (int i = 0; i < fcount + 1; i++) {
			hbr = CreateSolidBrush(RGB(255, 255, 255));
			oldbr = SelectObject(hdc, hbr);
			Rectangle(hdc, (fig[i].left / 20) * 20, (fig[i].top / 20) * 20, (oldx[i] / 20 - 1) * 20, (oldy[i] / 20 - 1) * 20);
			SelectObject(hdc, oldbr);
			DeleteObject(hbr);
			if (te == 1) {
				hp = CreatePen(PS_DOT, 1, RGB(0, 0, 0));
				oldp = (HPEN)SelectObject(hdc, hp);
			}
			if (te == 2) {
				hp = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
				oldp = (HPEN)SelectObject(hdc, hp);
			}
			if (i == num) {
				hp = CreatePen(PS_SOLID, 3, RGB(255, 0, 255));
				oldp = (HPEN)SelectObject(hdc, hp);
			}
			hbr = CreateSolidBrush(RGB(col1[i], col2[i], col3[i]));
			oldbr = SelectObject(hdc, hbr);
			
			Rectangle(hdc, (fig[i].left / 20) * 20, (fig[i].top / 20) * 20, (fig[i].right / 20) * 20, (fig[i].bottom / 20) * 20);
			SelectObject(hdc, oldbr);
			DeleteObject(hbr);
			SelectObject(hdc, oldp);
			DeleteObject(hp);

			oldx[i] = fig[i].right;
			oldy[i] = fig[i].bottom;
		}
		for (int i = 0; i < rcount + 1; i++) {
			hbr = CreateSolidBrush(RGB(rcol1[i], rcol2[i], rcol3[i]));
			oldbr = SelectObject(hdc, hbr);
			Rectangle(hdc, (rap[i].left / 20) * 20, (rap[i].top / 20) * 20, (rap[i].right / 20) * 20, (rap[i].bottom / 20) * 20);
			SelectObject(hdc, oldbr);
			DeleteObject(hbr);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_COMMAND: //--- 메뉴를 선택했을 때
		switch (LOWORD(wParam)) { //--- 선택된 메뉴의 id가 저장되어 있다
		case ID_sil:
			te = 2;
			break;
		case ID_jum:
			te = 1;
			break;
		case ID_BORDER_ON:
			te = 2;
			break;
		case ID_BORDER_OFF:
			te = 0;
			break;
		 case ID_COLOR_RED:
			 for (int i = 0; i < 5; i++) {
				 col1[i] = 255;
				 col2[i] = 0;
				 col3[i] = 0;
			}
	    	break;
	    case ID_COLOR_BLUE:
			for (int i = 0; i < 5; i++) {
				col1[i] = 0;
				col2[i] = 0;
				col3[i] = 255;
			}
	    	break;
	    case ID_COLOR_GREEN:
			for (int i = 0; i < 5; i++) {
				col1[i] = 0;
				col2[i] = 255;
				col3[i] = 0;
			}
	    	break;
	    case ID_COLOR_PURPLE:
			for (int i = 0; i < 5; i++) {
				col1[i] = 255;
				col2[i] = 0;
				col3[i] = 255;
			}
	    	break;
	    case ID_COLOR_SKY:
			for (int i = 0; i < 5; i++) {
				col1[i] = 0;
				col2[i] = 255;
				col3[i] = 255;
			}
	    	break;
	    case ID_COLOR_BLACK:
			for (int i = 0; i < 5; i++) {
				col1[i] = 100;
				col2[i] = 100;
				col3[i] = 100;
			}
		    break;
	    }
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_CHAR:
		if (wParam == '1') {
			num = 0;
		}
		else if (wParam == '2') {
			num = 1;
		}
		else if (wParam == '3') {
			num = 2;
		}
		else if (wParam == '4') {
			num = 3;
		}
		else if (wParam == '5') {
			num = 4;
		}
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_UP) {
			for (int i = 0; i < fcount; i++) {
				if (num == i) {
					fig[i].top -= 20;
					fig[i].bottom -= 20;
					if (fig[i].top <= 0) {
						fig[i].top += 20;
						fig[i].bottom += 20;
					}
				}
			}
		}
		if (wParam == VK_DOWN) {
			for (int i = 0; i < fcount; i++) {
				if (num == i) {
					fig[i].top += 20;
					fig[i].bottom += 20;
					if (fig[i].bottom >= 820) {
						fig[i].top -= 20;
						fig[i].bottom -= 20;
					}
				}
			}
		}
		if (wParam == VK_LEFT) {
			for (int i = 0; i < fcount; i++) {
				if (num == i) {
					fig[i].right -= 20;
					fig[i].left -= 20;
					if (fig[i].left <=-20) {
						fig[i].right += 20;
						fig[i].left += 20;
					}
				}
			}
		}
		if (wParam == VK_RIGHT) {
			for (int i = 0; i < fcount; i++) {
				if (num == i) {
					fig[i].right += 20;
					fig[i].left += 20;
					if (fig[i].right >= 820) {
						fig[i].right -= 20;
						fig[i].left -= 20;
					}
				}
			}
		}
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_LBUTTONDOWN:
		if (fcount < 5) {
			fig[fcount].left = oldx[fcount] = LOWORD(lParam);
			fig[fcount].top = oldy[fcount] = HIWORD(lParam);
			lclick = 1;
		}
		break;
	case WM_LBUTTONUP:
		if (fcount < 5) {
			for (int i = 0; i < fcount; i++) {
				if (IntersectRect(&rap[rcount], &fig[fcount], &fig[i])) {
					rcol1[rcount] = col1[i] + col1[fcount];
					rcol2[rcount] = col2[i] + col2[fcount];
					rcol3[rcount] = col3[i] + col3[fcount];
					if (rcol1[rcount] == 255 && rcol2[rcount] == 255 && rcol3[rcount] == 255) {
						rcol1[rcount] = 0;
						rcol2[rcount] = 0;
						rcol3[rcount] = 0;
					}
					if (rcol1[rcount] >= 256) {
						rcol1[rcount] = 0;
					}
					if (rcol2[rcount] >= 256) {
						rcol2[rcount] = 0;
					}
					if (rcol3[rcount] >= 256) {
						rcol3[rcount] = 0;
					}
					rcount++;
				}
			}
			lclick = 0;
			fcount++;
		}
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_RBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		POINT pt;
		pt.x = mx;
		pt.y = my;
		for (int i = 0; i < fcount; i++) {
			
			if (PtInRect(&fig[i], pt)) {
				printf("%d\n", i);
				sel = i;
				rclick = 1;
			}
		}
		break;
	case WM_RBUTTONUP:
		rclick = 0;
		break;
	case WM_MOUSEMOVE:
		if (lclick == 1) {
			fig[fcount].right = LOWORD(lParam);
			fig[fcount].bottom = HIWORD(lParam);
			InvalidateRgn(hWnd, NULL, TRUE);
		}
		if (rclick == 1) {
			mx = LOWORD(lParam);
			my = HIWORD(lParam);
			int subx = fig[sel].right - fig[sel].left;
			fig[sel].left = mx; //+ (fig[sel].left + fig[sel].right) / 2;
			fig[sel].right = fig[sel].left + subx;
			int suby = fig[sel].bottom - fig[sel].top;
			fig[sel].top = my;//+ (fig[sel].top + fig[sel].bottom) / 2;
			fig[sel].bottom = fig[sel].top + suby;
			InvalidateRgn(hWnd, NULL, TRUE);
			
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam); //--- 위의 세 메시지 외의 나머지 메시지는 OS로
}
