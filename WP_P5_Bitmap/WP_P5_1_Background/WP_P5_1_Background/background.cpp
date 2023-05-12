#include <windows.h> //--- ������ ��� ����
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
{//5���� ���콺 �̵�x
	PAINTSTRUCT ps;
	HDC hdc, memdc;
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;
	static HBITMAP hBitmap;

	static RECT rt;//
	static DWORD scopy = SRCCOPY;//���������� �ƴ���

	static bool full = false;//���� ��ä������
	static pictures pic[4];	//���� �Լ�

	static int xPos = -1;
	static int yPos = -1;


	static int sel = -1;

	switch (uMsg) {
	case WM_CREATE:
	{
		hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
		pic[0].x = 0, pic[0].y = 0, pic[0].sx = 800, pic[0].sy = 800, pic[0].subx = 0, pic[0].suby = 0;
		pic[1].x = 800, pic[1].y = 0, pic[1].sx = 0, pic[1].sy = 800, pic[1].subx = 0, pic[1].suby = 0;
		pic[2].x = 0, pic[2].y = 800, pic[2].sx = 800, pic[2].sy = 0, pic[2].subx = 0, pic[2].suby = 0;
		pic[3].x = 800, pic[3].y = 800, pic[3].sx = 0, pic[3].sy = 0, pic[3].subx = 0, pic[3].suby = 0;
	}
		break;
	case WM_PAINT:
		printf("x : %d sx : %d sy : %d\n", pic[0].subx, pic[0].sx, pic[0].sy);
		printf("sel : %d mx : %d, %y : %d\n", sel, pic[2].y, yPos);
		hdc = BeginPaint(hwnd, &ps);
		memdc = CreateCompatibleDC(hdc);
		SelectObject(memdc, hBitmap);
		
		
		//��������
		if (full == false) {
			BitBlt(hdc, 0, 0, 224, 219, memdc, 0, 0, scopy);
		}
		//���һ���
		if (full == true) {//���λ��� 4��, ������� 4�� * 2 + ���� ������ �ϳ� ��
			if (pic[0].subx > 0) {//����� ����
				StretchBlt(hdc, pic[0].sx - (pic[0].subx * pic[0].sx / 224),  pic[0].y, pic[0].sx, pic[0].sy,		memdc, 0, 0, 224, 219, scopy);//1�����ʻ���
			}
			else {
				StretchBlt(hdc, -pic[0].sx - (pic[0].subx * pic[0].sx / 224),  pic[0].y, pic[0].sx, pic[0].sy,		memdc, 0, 0, 224, 219, scopy);//1���ʻ���
			}

			if (pic[1].subx > 0) {//����� ����
				StretchBlt(hdc, (pic[1].x + pic[1].sx) - (pic[1].subx * pic[1].sx / 224), pic[1].y, pic[1].sx, pic[1].sy, memdc, 0, 0, 224, 219, scopy);//2������
			}
			else {
				StretchBlt(hdc, (pic[1].x - pic[1].sx) - (pic[1].subx * pic[1].sx / 224), pic[1].y, pic[1].sx, pic[1].sy, memdc, 0, 0, 224, 219, scopy);//2����
			}

			if (pic[2].subx > 0) {//����� ����
				StretchBlt(hdc, pic[2].sx - (pic[2].subx * pic[2].sx / 224),  pic[2].y, pic[2].sx, pic[2].sy,		memdc, 0, 0, 224, 219, scopy);//1�����ʻ���
			}
			else {
				StretchBlt(hdc, -pic[2].sx - (pic[2].subx * pic[2].sx / 224),  pic[2].y, pic[2].sx, pic[2].sy,		memdc, 0, 0, 224, 219, scopy);//1���ʻ���
			}

			if (pic[3].subx > 0) {//����� ����
				StretchBlt(hdc, (pic[3].x + pic[3].sx) - (pic[3].subx * pic[3].sx / 224), pic[3].y, pic[3].sx, pic[3].sy, memdc, 0, 0, 224, 219, scopy);//2������
			}
			else {
				StretchBlt(hdc, (pic[3].x - pic[3].sx) - (pic[3].subx * pic[3].sx / 224), pic[3].y, pic[3].sx, pic[3].sy, memdc, 0, 0, 224, 219, scopy);//2����
			}

			StretchBlt(hdc, pic[0].x, pic[0].y, pic[0].sx, pic[0].sy, memdc, pic[0].subx, 0, 224, 219, scopy);//1���� ����
			StretchBlt(hdc, pic[1].x, pic[1].y, pic[1].sx, pic[1].sy, memdc, pic[1].subx, 0, 224, 219, scopy);//2��° ����

			StretchBlt(hdc, pic[2].x, pic[2].y, pic[2].sx, pic[2].sy, memdc, pic[2].subx, 0, 224, 219, scopy);
			StretchBlt(hdc, pic[3].x, pic[3].y, pic[3].sx, pic[3].sy, memdc, pic[3].subx, 0, 224, 219, scopy);
		
		
			if (sel == 0) {
				hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0)); // GDI: �� �����
				oldPen = (HPEN)SelectObject(hdc, hPen);
				MoveToEx(hdc, pic[0].x, pic[0].y, NULL); 
				LineTo(hdc, pic[0].sx, 0);

				MoveToEx(hdc, pic[0].sx, pic[0].y, NULL);
				LineTo(hdc, pic[0].sx, pic[0].sy);

				MoveToEx(hdc, pic[0].sx, pic[0].sy, NULL);
				LineTo(hdc, pic[0].x, pic[0].sy);

				MoveToEx(hdc, pic[0].x, pic[0].sy, NULL);
				LineTo(hdc, pic[0].x, pic[0].y);

				SelectObject(hdc, oldPen); // ������ ������ ���ư�
				DeleteObject(hPen);
			}
			if (sel == 1) {
				hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0)); // GDI: �� �����
				oldPen = (HPEN)SelectObject(hdc, hPen);
				MoveToEx(hdc, pic[1].x, pic[1].y, NULL); 
				LineTo(hdc, pic[1].x + pic[1].sx, 0);

				MoveToEx(hdc, pic[1].x + pic[1].sx, pic[1].y, NULL);
				LineTo(hdc, pic[1].x + pic[1].sx, pic[1].y + pic[1].sy);

				MoveToEx(hdc, pic[1].x + pic[1].sx, pic[1].y + pic[1].sy, NULL);
				LineTo(hdc, pic[1].x, pic[1].y + pic[1].sy);

				MoveToEx(hdc, pic[1].x, pic[1].y + pic[1].sy, NULL);
				LineTo(hdc, pic[1].x, pic[1].y);

				SelectObject(hdc, oldPen); // ������ ������ ���ư�
				DeleteObject(hPen);
			}
			if (sel == 2) {
				hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0)); // GDI: �� �����
				oldPen = (HPEN)SelectObject(hdc, hPen);
				MoveToEx(hdc, pic[2].x, pic[2].y, NULL); 
				LineTo(hdc, pic[2].x + pic[2].sx, pic[2].y);

				MoveToEx(hdc, pic[2].x + pic[2].sx, pic[2].y, NULL);
				LineTo(hdc, pic[2].x + pic[2].sx, pic[2].y + pic[2].sy);

				MoveToEx(hdc, pic[2].x + pic[2].sx, pic[2].y + pic[2].sy, NULL);
				LineTo(hdc, pic[2].x, pic[2].y + pic[2].sy);

				MoveToEx(hdc, pic[2].x, pic[2].y + pic[2].sy, NULL);
				LineTo(hdc, pic[2].x, pic[2].y);

				SelectObject(hdc, oldPen); // ������ ������ ���ư�
				DeleteObject(hPen);
			}
			if (sel == 3) {
				hPen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0)); // GDI: �� �����
				oldPen = (HPEN)SelectObject(hdc, hPen);
				MoveToEx(hdc, pic[3].x, pic[3].y, NULL); 
				LineTo(hdc, pic[3].x + pic[3].sx, pic[3].y);

				MoveToEx(hdc, pic[3].x + pic[3].sx, pic[3].y, NULL);
				LineTo(hdc, pic[3].x + pic[3].sx, pic[3].y + pic[3].sy);

				MoveToEx(hdc, pic[3].x + pic[3].sx, pic[3].y + pic[3].sy, NULL);
				LineTo(hdc, pic[3].x, pic[3].y + pic[3].sy);

				MoveToEx(hdc, pic[3].x, pic[3].y + pic[3].sy, NULL);
				LineTo(hdc, pic[3].x, pic[3].y);

				SelectObject(hdc, oldPen); // ������ ������ ���ư�
				DeleteObject(hPen);
			}
			
		}
		
		DeleteDC(memdc);
		EndPaint(hwnd, &ps);
		break;
	case WM_CHAR:
		if (wParam == 'a') {
			if (full == false)
				full = true;
			else
				full = false;
		}
		if (wParam == 'r') {
			if (scopy == NOTSRCCOPY)
				scopy = SRCCOPY;
			else
				scopy = NOTSRCCOPY;
		}
		if (wParam == '+') {
			if (sel == 0 || sel == -1) {
				pic[0].sx += 10;
				pic[0].sy += 10;

				pic[1].x += 10;
				pic[1].sx -= 10;
				pic[1].sy += 10;

				pic[2].y += 10;
				pic[2].sy -= 10;
				pic[2].sx += 10;

				pic[3].x += 10;
				pic[3].sx -= 10;
				pic[3].y += 10;
				pic[3].sy -= 10;
			}
			if (sel == 1) {
				pic[1].x -= 10;
				pic[1].sx += 10;
				pic[1].sy += 10;

				pic[0].sx -= 10;
				pic[0].sy += 10;

				pic[2].y += 10;
				pic[2].sy -= 10;
				pic[2].sx -= 10;

				pic[3].x -= 10;
				pic[3].sx += 10;
				pic[3].y += 10;
				pic[3].sy -= 10;
			}
			if (sel == 2) {
				pic[2].y -= 10;
				pic[2].sx += 10;
				pic[2].sy += 10;

				pic[0].sx += 10;
				pic[0].sy -= 10;

				pic[1].x += 10;
				pic[1].sy -= 10;
				pic[1].sx -= 10;
				
				pic[3].x += 10;
				pic[3].sx -= 10;
				pic[3].y -= 10;
				pic[3].sy += 10;
			}
			if (sel == 3) {
				pic[3].x -= 10;
				pic[3].sx += 10;
				pic[3].y -= 10;
				pic[3].sy += 10;

				pic[0].sx -= 10;
				pic[0].sy -= 10;

				pic[1].x -= 10;
				pic[1].sx += 10;
				pic[1].sy -= 10;

				pic[2].y -= 10;
				pic[2].sy += 10;
				pic[2].sx -= 10;

			}
		}
		if (wParam == '-') {
			if (sel == 3) {
				pic[0].sx += 10;
				pic[0].sy += 10;

				pic[1].x += 10;
				pic[1].sx -= 10;
				pic[1].sy += 10;

				pic[2].y += 10;
				pic[2].sy -= 10;
				pic[2].sx += 10;

				pic[3].x += 10;
				pic[3].sx -= 10;
				pic[3].y += 10;
				pic[3].sy -= 10;
			}
			if (sel == 2) {
				pic[1].x -= 10;
				pic[1].sx += 10;
				pic[1].sy += 10;

				pic[0].sx -= 10;
				pic[0].sy += 10;

				pic[2].y += 10;
				pic[2].sy -= 10;
				pic[2].sx -= 10;

				pic[3].x -= 10;
				pic[3].sx += 10;
				pic[3].y += 10;
				pic[3].sy -= 10;
			}
			if (sel == 1) {
				pic[2].y -= 10;
				pic[2].sx += 10;
				pic[2].sy += 10;

				pic[0].sx += 10;
				pic[0].sy -= 10;

				pic[1].x += 10;
				pic[1].sy -= 10;
				pic[1].sx -= 10;
				
				pic[3].x += 10;
				pic[3].sx -= 10;
				pic[3].y -= 10;
				pic[3].sy += 10;
			}
			if (sel == 0 || sel == -1) {
				pic[3].x -= 10;
				pic[3].sx += 10;
				pic[3].y -= 10;
				pic[3].sy += 10;

				pic[0].sx -= 10;
				pic[0].sy -= 10;

				pic[1].x -= 10;
				pic[1].sx += 10;
				pic[1].sy -= 10;

				pic[2].y -= 10;
				pic[2].sy += 10;
				pic[2].sx -= 10;

			}
		}
		if (wParam == 'p') {
			sel = 5;
		}
		if (wParam == 's') {
			scopy = SRCCOPY;//���������� �ƴ���
			full = false;//���� ��ä������
			xPos = -1;
			yPos = -1;
			sel = -1;
			pic[0].x = 0, pic[0].y = 0, pic[0].sx = 800, pic[0].sy = 800, pic[0].subx = 0, pic[0].suby = 0;
			pic[1].x = 800, pic[1].y = 0, pic[1].sx = 0, pic[1].sy = 800, pic[1].subx = 0, pic[1].suby = 0;
			pic[2].x = 0, pic[2].y = 800, pic[2].sx = 800, pic[2].sy = 0, pic[2].subx = 0, pic[2].suby = 0;
			pic[3].x = 800, pic[3].y = 800, pic[3].sx = 0, pic[3].sy = 0, pic[3].subx = 0, pic[3].suby = 0;
		}
		if (wParam == 'q') {
			PostQuitMessage(0);
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_LEFT) {
			if(sel == 0)
				pic[0].subx += 10;
			if(sel == 1)
				pic[1].subx += 10;
			if(sel == 2)
				pic[2].subx += 10;
			if(sel == 3)
				pic[3].subx += 10;
			if (sel == 5) {
				pic[0].subx += 10;
				pic[1].subx += 10;
				pic[2].subx += 10;
				pic[3].subx += 10;
			}
		}
		if (wParam == VK_RIGHT) {
			if (sel == 0)
				pic[0].subx -= 10;
			if (sel == 1)
				pic[1].subx -= 10;
			if (sel == 2)
				pic[2].subx -= 10;
			if (sel == 3)
				pic[3].subx -= 10;
			if (sel == 5) {
				pic[0].subx -= 10;
				pic[1].subx -= 10;
				pic[2].subx -= 10;
				pic[3].subx -= 10;
			}

		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hwnd);
		xPos = LOWORD(lParam);
		yPos = HIWORD(lParam);

		if (xPos < pic[0].sx && yPos < pic[0].sy) {
			sel = 0;
		}
		else if (xPos > pic[0].sx && yPos < pic[0].sy) {
			sel = 1;
		}
		else if (xPos < pic[0].sx && yPos > pic[0].sy) {
			sel = 2;
		}
		else if (xPos > pic[0].sx && yPos > pic[0].sy) {
			sel = 3;
		}

		ReleaseDC(hwnd, hdc);
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_DESTROY:
		DeleteObject(hBitmap);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam); //--- ���� �� �޽��� ���� ������ �޽����� OS��
}
