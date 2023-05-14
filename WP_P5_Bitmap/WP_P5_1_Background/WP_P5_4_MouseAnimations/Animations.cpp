#include <windows.h> //--- 윈도우 헤더 파일
#include <tchar.h>
#include<stdio.h>
#include"resource.h"
#include <atlimage.h>

#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3
#define RIGHTUP 5
#define LEFTUP 6
#define RIGHTDOWN 7
#define LEFTDOWN 8

#define IDLE 0
#define JUMP 1
#define ZIAZAG 2
//투명 비트맵 처리 
#pragma comment(lib, "msimg32.lib")
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#define WINDOWSIZE 800

typedef struct {
	int x, y;
	int move;
	int state;
	int speed;
	int size;
}copypaste;
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

static HBITMAP hBitmap, hBitmap2, oldmap;

//copy paste
static int count = 0;
static int tc = 0;
static copypaste won[6];
static copypaste twon[5];


void NewChar();
void changeTurn(int i);
//따라가기
//{
	//if (won[0].move == RIGHT) {
	//	for (int i = 0; i < count; i++)
	//	{
	//		TransparentBlt(mdc, won[0].x - i * won[0].size, won[0].y, won[0].size, won[0].size, idle.GetDC(), 19 * timer1, 0, 19, 18, RGB(235, 197, 241));
	//	}
	//}
	//if (won[0].move == LEFT) {
	//	for (int i = 0; i < count; i++)
	//	{
	//		TransparentBlt(mdc, won[0].x + i * won[0].size, won[0].y, won[0].size, won[0].size, idle.GetDC(), 19 * timer1, 0, 19, 18, RGB(235, 197, 241));
	//	}
	//}
	//if (won[0].move == UP) {
	//	for (int i = 0; i < count; i++)
	//	{
	//		TransparentBlt(mdc, won[0].x, won[0].y + i * won[0].size, won[0].size, won[0].size, idle.GetDC(), 19 * timer1, 0, 19, 18, RGB(235, 197, 241));
	//	}
	//}
	//if (won[0].move == DOWN) {
	//	for (int i = 0; i < count; i++)
	//	{
	//		TransparentBlt(mdc, won[0].x, won[0].y - i * won[0].size, won[0].size, won[0].size, idle.GetDC(), 19 * timer1, 0, 19, 18, RGB(235, 197, 241));
	//	}
	//}
	//if (won[0].move == RIGHTDOWN) {
	//	for (int i = 0; i < count; i++)
	//	{
	//		TransparentBlt(mdc, won[0].x - i * won[0].size, won[0].y - i * won[0].size, won[0].size, won[0].size, idle.GetDC(), 19 * timer1, 0, 19, 18, RGB(235, 197, 241));
	//	}
	//}
	//if (won[0].move == RIGHTUP) {
	//	for (int i = 0; i < count; i++)
	//	{
	//		TransparentBlt(mdc, won[0].x - i * won[0].size, won[0].y + i * won[0].size, won[0].size, won[0].size, idle.GetDC(), 19 * timer1, 0, 19, 18, RGB(235, 197, 241));
	//	}
	//}
	//if (won[0].move == LEFTUP) {
	//	for (int i = 0; i < count; i++)
	//	{
	//		TransparentBlt(mdc, won[0].x + i * won[0].size, won[0].y + i * won[0].size, won[0].size, won[0].size, idle.GetDC(), 19 * timer1, 0, 19, 18, RGB(235, 197, 241));
	//	}
	//}
	//if (won[0].move == LEFTDOWN) {
	//	for (int i = 0; i < count; i++)
	//	{
	//		TransparentBlt(mdc, won[0].x + i * won[0].size, won[0].y - i * won[0].size, won[0].size, won[0].size, idle.GetDC(), 19 * timer1, 0, 19, 18, RGB(235, 197, 241));
	//	}
	//}
//}
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

//CImage를 사용한 이미지 출력
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{//5개면 마우스 이동x
	PAINTSTRUCT ps;
	HDC hdc, mdc;
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	static CImage img, idle, jump, lying;
	static RECT rt;//
	static DWORD scopy = SRCCOPY;//반전색인지 아닌지

	static int timer1 = 0;
	static int jumptimer = 0;
	static int w, h;

	static int move = 0;
	static int state = 0;

	static int moveSpeed = 10;
	static int imgsize = 50;

	static bool sizeup = false;
	static int sizeuptimer = 0;

	static bool sizedown = false;
	static int sizedowntimer = 0;

	static bool zigzag = false;
	static bool uturn = false;

	static int uturnc = 0;

	static int mx, my;
	static bool clicked = false;
	static bool moveto = false;
	static bool changeAnim = false;

	static float angle;
	switch (uMsg) {
	case WM_CREATE:
	{
		img.LoadFromResource(g_hInst, IDB_BITMAP2); //--- background
		idle.LoadFromResource(g_hInst, IDB_BITMAP1); //--- sprite image
		jump.LoadFromResource(g_hInst, IDB_BITMAP3); //--- sprite image
		lying.LoadFromResource(g_hInst, IDB_BITMAP4); //--- sprite image
		GetClientRect(hwnd, &rt);
		NewChar();
		SetTimer(hwnd, 1, 100, NULL);
	}
	break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			timer1++;
			timer1 = timer1 % 4;

			for (int i = 0; i < count; i++)
			{
				if (moveto && i == 0)
				{
					won[0].x += won[0].speed * cos(angle);
					won[0].y += won[0].speed * sin(angle);
					if (mx - 5 < won[0].x && mx + 5 > won[0].x) {
						moveto = false;
						changeAnim = false;
					}
					continue;
				}
				//점프
				if (state == JUMP) {
					jumptimer++;
					if (jumptimer < 6 * count) {
						if (won[i].move == RIGHT || won[i].move == LEFT) {
							won[i].y -= moveSpeed;
						}
						else if (won[i].move == DOWN) {
							won[i].x += moveSpeed;
						}
						else if (won[i].move == UP) {
							won[i].x -= moveSpeed;
						}
					}
					else if (jumptimer < 12 * count) {
						if (won[i].move == RIGHT || won[i].move == LEFT) {
							won[i].y += moveSpeed;
						}
						else if (won[i].move == DOWN) {
							won[i].x -= moveSpeed;
						}
						else if (won[i].move == UP) {
							won[i].x += moveSpeed;
						}
					}
					else {
						jumptimer = 0;
						state = IDLE;
					}
				}
				//방향
				{
					if (won[i].move == RIGHT)
						won[i].x += won[i].speed;
					if (won[i].move == LEFT) {
						won[i].x -= won[i].speed;
					}
					if (won[i].move == DOWN) {
						won[i].y += won[i].speed;
					}
					if (won[i].move == UP) {
						won[i].y -= won[i].speed;
					}
					if (won[i].move == RIGHTUP) {
						won[i].x += won[i].speed;
						won[i].y -= won[i].speed;
					}
					if (won[i].move == LEFTUP) {
						won[i].x -= won[i].speed;
						won[i].y -= won[i].speed;
					}
					if (won[i].move == RIGHTDOWN) {
						won[i].x += won[i].speed;
						won[i].y += won[i].speed;
					}
					if (won[i].move == LEFTDOWN) {
						won[i].x -= won[i].speed;
						won[i].y += won[i].speed;
					}
				}
				//크기 조절
				if (sizeup) {
					sizeuptimer++;
					if (sizeuptimer < 6 * count) {
						won[i].size += 3;
					}
					else if (sizeuptimer < 12 * count) {
						won[i].size -= 3;
					}
					else {
						sizeuptimer = 0;
						sizeup = false;
					}
				}
				if (sizedown) {
					sizedowntimer++;
					if (sizedowntimer < 6 * count) {
						won[i].size -= 3;
					}
					else if (sizedowntimer < 12 * count) {
						won[i].size += 3;
					}
					else {
						sizedowntimer = 0;
						sizedown = false;
					}
				}
				//충돌
				if (won[i].x >= WINDOWSIZE - imgsize) {
					if (won[i].move == RIGHTDOWN)
						won[i].move = LEFTDOWN;
					else if (won[i].move == RIGHTUP)
						won[i].move = LEFTUP;
					else
						won[i].move = LEFT;
				}
				if (won[i].x <= 0) {
					if (won[i].move == LEFTDOWN)
						won[i].move = RIGHTDOWN;
					else if (won[i].move == LEFTUP)
						won[i].move = RIGHTUP;
					else
						won[i].move = RIGHT;
				}
				if (won[i].y >= WINDOWSIZE - imgsize) {
					if (won[i].move == RIGHTDOWN)
						won[i].move = RIGHTUP;
					else if (won[i].move == LEFTDOWN)
						won[i].move = LEFTUP;
					else
						won[i].move = UP;
				}
				if (won[i].y <= 0) {
					if (won[i].move == RIGHTUP)
						won[i].move = RIGHTDOWN;
					else if (won[i].move == LEFTUP)
						won[i].move = LEFTDOWN;
					else
						won[i].move = DOWN;
				}
				//유턴
				if (uturn && zigzag) {
					for (int i = 0; i < count; i++)
					{
						if (uturnc == i * 5)
							changeTurn(i);
					}
					uturnc++;
					if (uturnc == count * 5) {
						uturn = false;
						uturnc = 0;
					}
				}
			}

			break;
		}
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		mdc = CreateCompatibleDC(hdc);

		(HBITMAP)SelectObject(mdc, hBitmap);

		w = img.GetWidth();
		h = img.GetHeight();

		img.Draw(mdc, 0, 0, rt.right, rt.bottom, 0, 0, w, h); //--- 메모리 DC에 배경 그리기
		
		//캐릭터
		{

			for (int i = 0; i < count; i++)
			{
				if (changeAnim) {//changeAnim 우선
					TransparentBlt(mdc, won[i].x, won[i].y, won[i].size, won[i].size, lying.GetDC(), 19 * timer1, 0, 19, 18, RGB(235, 197, 241));
				}
				else if (state == IDLE) {
					TransparentBlt(mdc, won[i].x, won[i].y, won[i].size, won[i].size, idle.GetDC(), 19 * timer1, 0, 19, 18, RGB(235, 197, 241));
				}
				else if (state == JUMP) {
					TransparentBlt(mdc, won[i].x, won[i].y, won[i].size, won[i].size, jump.GetDC(), 19 * timer1, 0, 18, 25, RGB(235, 197, 241));
				}
			}
		}

		BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY); //--- 메모리 DC의 그림을 화면 DC에 복사하기

		DeleteObject(hBitmap);
		DeleteDC(mdc);

		InvalidateRect(hwnd, NULL, false);
		EndPaint(hwnd, &ps);
		break;

	case WM_CHAR:
		if (wParam == 'j') {
			state = JUMP;
		}
		if (wParam == 'e') {
			sizeup = true;
		}
		if (wParam == 's') {
			sizedown = true;
		}
		if (wParam == 't') {
			NewChar();
		}
		if (wParam == 'a') {
			if (zigzag) {
				zigzag = false;
				for (int i = 0; i < tc; i++)
				{
					won[i + 1] = twon[i];
				}
				for (int i = 0; i < count; i++)
				{
					won[i].speed = 10;
				}
			}
			else {
				zigzag = true;
				for (int i = 0; i < count; i++)
				{
					won[i].speed = 20;
				}
				for (int i = 0; i < count - 1; i++)
				{
					twon[i] = won[i + 1];
					tc++;
				}

			}
			if (zigzag) {
				for (int i = 0; i < count; i++)
				{
					if (won[i].move == RIGHT || won[i].move == DOWN) {
						won[i].move = RIGHTDOWN;
					}
					if (won[i].move == UP || won[i].move == LEFT) {
						won[i].move = LEFTDOWN;
					}
					if (won[0].move == RIGHTDOWN) {
						won[i].x = won[0].x - i * won[i].size;
						won[i].y = won[0].y - i * won[i].size;
					}
					if (won[0].move == LEFTDOWN) {
						won[i].x = won[0].x + i * won[i].size;
						won[i].y = won[0].y - i * won[i].size;
					}
				}
			}
			else {
				for (int i = 0; i < count; i++)
				{
					if (won[i].move == RIGHTDOWN || won[i].move == RIGHTUP) {
						won[i].move = RIGHT;
					}
					if (won[i].move == LEFTUP || won[i].move == LEFTDOWN) {
						won[i].move = LEFT;
					}
				}
			}
		}
		if (wParam == 'r') {
			if(!uturn)
				uturn = true;
		}
		InvalidateRect(hwnd, NULL, false);
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		
		for (int i = 0; i < count; i++)
		{
			if (won[i].x < mx && mx < won[i].x + won[i].size && won[i].y < my && my < won[i].y + won[i].size)
				clicked = true;
		}
		//캐릭터 다른곳으로 이동 후 다른 애니메이션 보이기
		if (clicked) {
			for (int i = 0; i < count; i++)
			{
				my = rand() % 600 + 100;
				mx = rand() % 600 + 100;
				angle = atan2(my - won[0].y, mx - won[0].x);
				moveto = true;
				if(changeAnim)
					changeAnim = false;
				else
					changeAnim = true;
			}
		}//내부가 클릭되지 않았다면
		else{
			angle = atan2(my - won[0].y, mx - won[0].x);
			moveto = true;
		}
		clicked = false;
		InvalidateRect(hwnd, NULL, false);
		break;
	case WM_KEYDOWN:
		if (!zigzag) {
			if (wParam == VK_LEFT) {
				for (int i = 0; i < count; i++)
				{
					won[i].move = LEFT;
				}
				
			}
			if (wParam == VK_RIGHT) {
				for (int i = 0; i < count; i++)
				{
					won[i].move = RIGHT;
				}
			}
			if (wParam == VK_UP) {
				for (int i = 0; i < count; i++)
				{
					won[i].move = UP;
				}
			}
			if (wParam == VK_DOWN) {
				for (int i = 0; i < count; i++)
				{
					won[i].move = DOWN;
				}
			}
		}
		InvalidateRect(hwnd, NULL, false);
		break;
	case WM_DESTROY:
		DeleteObject(hBitmap);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam); //--- 위의 세 메시지 외의 나머지 메시지는 OS로
}

void NewChar() {
	if (count >= 6)
		return;
	won[count].x = rand() % 700 + 50;
	won[count].y = rand() % 700 + 50;
	won[count].size = 50;
	won[count].speed = 10;
	won[count].state = IDLE;
	won[count].move = RIGHT;
	count++;
}
void changeTurn(int i) {
	switch (won[i].move)
	{
	case RIGHT:
		won[i].move = LEFT;
		break;
	case LEFT:
		won[i].move = RIGHT;
		break;
	case UP:
		won[i].move = DOWN;
		break;
	case DOWN:
		won[i].move = UP;
		break;
	case RIGHTUP:
		won[i].move = LEFTDOWN;
		break;
	case LEFTUP:
		won[i].move = RIGHTDOWN;
		break;
	case RIGHTDOWN:
		won[i].move = LEFTUP;
		break;
	case LEFTDOWN:
		won[i].move = RIGHTUP;
		break;
	default:
		break;
	}
}