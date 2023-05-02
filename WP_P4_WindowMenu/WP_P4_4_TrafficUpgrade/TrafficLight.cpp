#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>
#include <random>
#include "resource.h"

#define WINDOWSIZE 1000
#define XSIZE 30
#define YSIZE 15
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 1";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

struct socar {
	int x;
	int y;
	int xsize;
	int ysize;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevIsntace, LPSTR lpszCmdParam, int nCmdShow)
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
	WndClass.hIcon = LoadCursor(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 400, 50, WINDOWSIZE + 18, WINDOWSIZE + 41, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	HDC mdc;
	HBITMAP hBitmap;
	RECT rt;
	static socar car[8];
	static socar car2[8];
	static socar man;

	static int Speed = 20;
	static int Timer1Count = 0;
	static int Timer2Count = 0;
	static int Timer3Count = 0;
	static int Timer4Count = 0;

	static int traffic = 2;

	static bool car0pass = false;
	static bool car1pass = false;
	static bool car2pass = false;
	static bool car3pass = false;
	static bool car4pass = false;
	static bool car5pass = false;
	static bool car6pass = false;
	static bool car7pass = false;

	static bool stop = false;
	static bool start = true;

	static bool updown = true;
	static bool side = true;

	static bool autotraffic = true;
	static bool crossing = false;

	static bool goright = false;
	static bool goleft = false;
	static bool goup = false;
	static bool godown = false;

	static bool rightup = false;
	static bool leftup = false;
	static bool rightdown = false;
	static bool leftdown= false;

	int randcross = 0;

	static int trafficcount = 0;
	switch (uMsg)
	{
	case WM_CREATE:
		//초기값
	{
		SetTimer(hwnd, 1, Speed, NULL);
		SetTimer(hwnd, 2, Speed, NULL);
		SetTimer(hwnd, 3, Speed, NULL);
		SetTimer(hwnd, 4, Speed, NULL);

		car[0] = { 450, 100, 25, 50 };
		car[1] = { 450, 250, 25, 50 };

		car[2] = { 550, 750, 25, 50 };
		car[3] = { 550, 900, 25, 50 };

		car[4] = { 100, 550, 50, 25 };
		car[5] = { 250, 550, 50, 25 };

		car[6] = { 750, 450, 50, 25 };
		car[7] = { 900, 450, 50, 25 };

		car2[0] = { 450, -50, 25, 50 };
		car2[1] = { 450, -50, 25, 50 };

		car2[2] = { 550, 1050, 25, 50 };
		car2[3] = { 550, 1050, 25, 50 };

		car2[4] = { -50, 550, 50, 25 };
		car2[5] = { -50, 550, 50, 25 };

		car2[6] = { 1050, 450, 50, 25 };
		car2[7] = { 1050, 450, 50, 25 };

		man = { 380,620,20,20 };
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_40001://start
			start = true;
			break;
		case ID_40002://end
			start = false;
			break;
		case ID_40003://가속
			if (Speed > 10)
			{
				Speed -= 10;
				SetTimer(hwnd, 1, Speed, NULL);
				SetTimer(hwnd, 2, Speed, NULL);
				SetTimer(hwnd, 3, Speed, NULL);
				SetTimer(hwnd, 4, Speed, NULL);
			}
			break;
		case ID_40004://감속
			if (Speed < 50)
			{
				Speed += 10;
				SetTimer(hwnd, 1, Speed, NULL);
				SetTimer(hwnd, 2, Speed, NULL);
				SetTimer(hwnd, 3, Speed, NULL);
				SetTimer(hwnd, 4, Speed, NULL);
			}
			break;
		case ID_40005://위아래
			side = false;
			updown = true;
			break;
		case ID_40006://왼오
			updown = false;
			side = true;
			break;
		case ID_40007://모두
			updown = true;
			side = true;
			break;
		case ID_40008://빨
			autotraffic = false;
			traffic = 0;
			break;
		case ID_40009://파
			autotraffic = false;
			traffic = 2;
			break;
		case ID_40010://노
			autotraffic = false;
			traffic = 1;
			break;
		case ID_40011://자동
			if (autotraffic == false)
				autotraffic = true;
			else
				autotraffic = false;
			break;
		case ID_40012://건너기
			if (crossing == false)
				crossing = true;
			break;
		}
	
	case WM_TIMER:

		switch (wParam)
		{
		case 1:
			Timer1Count++;

			break;
		case 2:
			if (!stop)
				Timer2Count++;
			printf("TimerCount1 : %d, TimerCount2 : %d Speed : %d\n", Timer1Count, Timer2Count, Speed);
			printf("man.x : %d\n\n", man.x);
			//Traffic
			{
				if (autotraffic) {
					if (Timer2Count % 40 == 0) {
						traffic = trafficcount % 4;
						trafficcount++;
					}
				}
			}
			break;
		default:
			break;
		}
		//끝자락 지났는지 검사
		{
			


			if (car[0].y == WINDOWSIZE - car[0].ysize)
			{
				car0pass = true;
				car2[0].y = -50;
			}
			else if (car[1].y == WINDOWSIZE - car[0].ysize)
			{
				car1pass = true;
				car2[1].y = -50;
			}
			if (car[2].y == car[2].ysize)
			{
				car2pass = true;
				car2[2].y = 1050;
			}
			else if (car[3].y == car[3].ysize)
			{
				car3pass = true;
				car2[3].y = 1050;
			}
			if (car[4].x == WINDOWSIZE - car[4].xsize)
			{
				car4pass = true;
				car2[4].x = -50;
			}
			else if (car[5].x == WINDOWSIZE - car[5].xsize)
			{
				car5pass = true;
				car2[5].x = -50;
			}
			if (car[6].x == car[6].xsize)
			{
				car6pass = true;
				car2[6].x = 1050;
			}
			else if (car[7].x == car[7].xsize)
			{
				car7pass = true;
				car2[7].x = 1050;
			}
		}
		//시작점 지났는지 검사
		{
			if (car2[0].y == car[0].ysize)
			{
				car0pass = false;
				car2[0].y = -50;
				car[0].y = 50;
			}
			else if (car2[1].y == car[0].ysize)
			{
				car1pass = false;
				car2[1].y = -50;
				car[1].y = 50;
			}
			if (car2[2].y == WINDOWSIZE - car[2].ysize)
			{
				car2pass = false;
				car2[2].y = 1050;
				car[2].y = 950;
			}
			else if (car2[3].y == WINDOWSIZE - car[3].ysize)
			{
				car3pass = false;
				car2[3].y = 1050;
				car[3].y = 950;
			}
			if (car2[4].x == car[4].xsize)
			{
				car4pass = false;
				car2[4].x = -50;
				car[4].x = 50;
			}
			else if (car2[5].x == car[5].xsize)
			{
				car5pass = false;
				car2[5].x = -50;
				car[5].x = 50;
			}
			if (car2[6].x == WINDOWSIZE - car[6].xsize)
			{
				car6pass = false;
				car2[6].x = 1050;
				car[6].x = 950;
			}
			else if (car2[7].x == WINDOWSIZE - car[7].xsize)
			{
				car7pass = false;
				car2[7].x = 1050;
				car[7].x = 950;
			}
		}
		//자동차 AI
		{
			if (start) {
				if (updown) {
					if (Timer1Count % 1 == 0)
					{
						if (updown) {
							car[0].y++;//위로 이동 
							car[1].y++;
						}
						if (traffic == 0 || traffic == 3)//신호등에 걸리면
						{
							if (car[1].y == 325)
							{
								car[0].y--;
								car[1].y--;
							}
							if (car[1].y > 325 && car[1].y < 575)
							{
								if (car[1].y >= 325)
								{
									car[0].y -= 5;
									car[1].y -= 5;
								}
							}
							if (car[1].y >= 575 && car[1].y < 825)
							{
									car[0].y += 5;
									car[1].y += 5;
							}
						}
						if (car0pass)//끝자락 지났으면 세컨드 차 보냄
						{
							car2[0].y++;
						}
						else if (car1pass)
						{
							car2[1].y++;
						}
					}
					if (Timer1Count % 2 == 0)
					{
						if (updown) {
							car[2].y--;
							car[3].y--;
						}

						if (traffic == 0 || traffic == 3)
						{
							if (car[2].y == 675)
							{
								car[2].y++;
								car[3].y++;
							}
							else if (car[3].y > 325 && car[3].y < 600)
							{
								if (car[3].y >= 325)
								{
									car[2].y -= 5;
									car[3].y -= 5;
								}
							}
							else if (600 < car[2].y && car[2].y <= 675)
							{
car[2].y += 5;
car[3].y += 5;

							}
						}

						if (car2pass)
						{
							car2[2].y--;
						}
						else if (car3pass)
						{
							car2[3].y--;
						}
					}
				}
				if (Timer1Count % 1 == 0)
				{
					if (side) {
						car[4].x++;
						car[5].x++;
					}
					if (traffic == 2 || traffic == 1)
					{
						if (car[5].x == 325)
						{
							car[4].x--;
							car[5].x--;
						}
						if (car[5].x > 325 && car[5].x < 600)
						{
							if (car[5].x >= 300)
							{
								car[4].x -= 5;
								car[5].x -= 5;
							}
						}
						if (car[5].x > 600 && car[5].x < 800)
						{
							if (car[5].x <= 800)
							{
								car[4].x += 5;
								car[5].x += 5;
							}
						}
					}
					if (car4pass)
					{
						car2[4].x++;
					}
					else if (car5pass)
					{
						car2[5].x++;
					}
				}
				if (Timer1Count % 1 == 0)
				{
					if (side) {
						car[6].x--;
						car[7].x--;
					}
					if (traffic == 2 || traffic == 1)
					{
						if (car[6].x == 675)
						{
							car[6].x++;
							car[7].x++;
						}
						else if (car[7].x > 325 && car[7].x < 600)
						{
							if (car[7].x >= 325)
							{
								car[6].x -= 5;
								car[7].x -= 5;
							}
						}
						else if (500 < car[6].x && car[6].x < 675)
						{
							if (car[6].x <= 700)
							{
								car[6].x += 5;
								car[7].x += 5;
							}
						}
					}
					if (car6pass)
					{
						car2[6].x--;
					}
					else if (car7pass)
					{
						car2[7].x--;
					}
				}

			}
		}

		//방향 AI
		{
			if(!updown){
				if (car[1].y > 325 && car[1].y < 575)
				{
					if (car[1].y >= 325)
					{
						car[0].y -= 5;
						car[1].y -= 5;
					}
				}
				if (car[1].y >= 575 && car[1].y < 825)
				{
					car[0].y += 5;
					car[1].y += 5;
				}
				if (car[3].y > 325 && car[3].y < 600)
				{
						car[2].y -= 5;
						car[3].y -= 5;
				}
				else if (600 < car[3].y && car[3].y <= 825)
				{
					car[2].y += 5;
					car[3].y += 5;
				}
			}
			if (!side) {
				if (car[5].x > 325 && car[5].x < 600)
				{
					if (car[5].x >= 300)
					{
						car[4].x -= 5;
						car[5].x -= 5;
					}
				}
				if (car[5].x > 600 && car[5].x < 800)
				{
					if (car[5].x <= 800)
					{
						car[4].x += 5;
						car[5].x += 5;
					}
				}
				if (car[7].x > 325 && car[7].x < 600)
				{
					if (car[7].x >= 325)
					{
						car[6].x -= 5;
						car[7].x -= 5;
					}
				}
				if (500 < car[6].x && car[6].x < 675)
				{
					if (car[6].x <= 700)
					{
						car[6].x += 5;
						car[7].x += 5;
					}
				}
			}
		}

		//행인 AI
		{
			//AI ON/OFF
			if (crossing) {
				updown = false;
				side = false;
				autotraffic = false;
				randcross = rand() % 2;
				if (randcross == 0) {//좌우 건너기
					if (traffic == 0 || traffic == 3) {
						if (man.x < 500) {
							goright = true;
						}
						else {
							goleft = true;
						}
					}
					else {
						if (man.y < 500) {
							godown = true;
						}
						else {
							goup = true;
						}
					}
				}
				else {
					if ((man.x < 500 && man.y < 500))
						rightdown = true;
					else if ((man.x > 500 && man.y > 500))
						leftup = true;
					else if ((man.x < 500 && man.y > 500))
						rightup = true;
					else if ((man.x > 500 && man.y < 500))
						leftdown = true;
				}
				crossing = false;
			}
			//AI 알고리즘
			{
				//상하좌우
				{
					if (goright) {
						man.x += 5;
						if (man.x > 620) {
							goright = false;
							updown = true;
							side = true;
							autotraffic = true;
						}
					}
					else if (goleft) {
						man.x -= 5;
						if (man.x < 380) {
							goleft = false;
							updown = true;
							side = true;
							autotraffic = true;
						}
					}
					else if (goup) {
						man.y -= 5;
						if (man.y < 380) {
							goup = false;
							updown = true;
							side = true;
							autotraffic = true;
						}
					}
					else if (godown) {
						man.y += 5;
						if (man.y > 620) {
							godown = false;
							updown = true;
							side = true;
							autotraffic = true;
						}
					}
				}
				//대각선
				{
					if (rightdown) {
						man.x += 5, man.y += 5;
						if (man.x > 620) {
							rightdown = false;
							updown = true;
							side = true;
							autotraffic = true;
						}
					}
					if (leftup) {
						man.x -= 5, man.y -= 5;
						if (man.x < 380) {
							leftup = false;
							updown = true;
							side = true;
							autotraffic = true;
						}
					}
					if (rightup) {
						man.x += 5, man.y -= 5;
						if (man.x > 620) {
							rightup = false;
							updown = true;
							side = true;
							autotraffic = true;
						}
					}
					if (leftdown) {
						man.x -= 5, man.y += 5;
						if (man.x < 380) {
							leftdown = false;
							updown = true;
							side = true;
							autotraffic = true;
						}
					}
				}
			}
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_PAINT:
		//기본 생성
		GetClientRect(hwnd, &rt);
		hdc = BeginPaint(hwnd, &ps);
		mdc = CreateCompatibleDC(hdc); //--- 메모리 DC 만들기+++전부 mdc 써야함
		hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom); //--- 메모리 DC와 연결할 비트맵 만들기+++
		SelectObject(mdc, (HBITMAP)hBitmap);//+++
		//배경 칠하기
		{
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
			Rectangle(mdc, 0, 0, WINDOWSIZE, WINDOWSIZE);
			SelectObject(mdc, oldBrush);
			DeleteObject(hBrush);
		}
		//경계선
		{
			hPen = CreatePen(PS_DOT, 1, BLACK_PEN);
			oldPen = (HPEN)SelectObject(mdc, hPen);
			MoveToEx(mdc, 400, 400, NULL);
			LineTo(mdc, 400, 600);
			MoveToEx(mdc, 400, 400, NULL);
			LineTo(mdc, 600, 400);
			MoveToEx(mdc, 600, 400, NULL);
			LineTo(mdc, 600, 600);
			MoveToEx(mdc, 400, 600, NULL);
			LineTo(mdc, 600, 600);
			SelectObject(mdc, oldPen);
			DeleteObject(hPen);

			hPen = CreatePen(PS_SOLID, 3, BLACK_PEN);
			SelectObject(mdc, hPen);
			MoveToEx(mdc, 400, 0, NULL);
			LineTo(mdc, 400, 400);
			MoveToEx(mdc, 600, 0, NULL);
			LineTo(mdc, 600, 400);
			MoveToEx(mdc, 400, 600, NULL);
			LineTo(mdc, 400, 1000);
			MoveToEx(mdc, 600, 600, NULL);
			LineTo(mdc, 600, 1000);
			MoveToEx(mdc, 0, 400, NULL);
			LineTo(mdc, 400, 400);
			MoveToEx(mdc, 0, 600, NULL);
			LineTo(mdc, 400, 600);
			MoveToEx(mdc, 600, 400, NULL);
			LineTo(mdc, 1000, 400);
			MoveToEx(mdc, 600, 600, NULL);
			LineTo(mdc, 1000, 600);
			SelectObject(mdc, oldPen);
			DeleteObject(hPen);
		}
		//신호등
		{

			hBrush = CreateSolidBrush(RGB(200, 200, 200));
			oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
			Rectangle(mdc, 650, 100, 950, 200);
			SelectObject(mdc, oldBrush);
			DeleteObject(hBrush);

			if (traffic == 0) {
				hBrush = CreateSolidBrush(RGB(255, 0, 0));
				hPen = CreatePen(PS_DOT, 6, BLACK_PEN);
				oldPen = (HPEN)SelectObject(mdc, hPen);
			}
			else
				hBrush = CreateSolidBrush(RGB(50, 0, 0));
			oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
			Ellipse(mdc, 665, 115, 735, 185);
			SelectObject(mdc, oldBrush);
			DeleteObject(hBrush);
			if (traffic == 0) {
				SelectObject(mdc, oldPen);
			}


			if (traffic == 1 || traffic == 3) {
				hBrush = CreateSolidBrush(RGB(255, 255, 0));
				hPen = CreatePen(PS_DOT, 6, BLACK_PEN);
				oldPen = (HPEN)SelectObject(mdc, hPen);
			}
			else
				hBrush = CreateSolidBrush(RGB(50, 50, 0));
			oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
			Ellipse(mdc, 765, 115, 835, 185);
			SelectObject(mdc, oldBrush);
			DeleteObject(hBrush);
			if (traffic == 1 || traffic == 3) {
				SelectObject(mdc, oldPen);
			}


			if (traffic == 2) {
				hBrush = CreateSolidBrush(RGB(0, 0, 255));
				hPen = CreatePen(PS_DOT, 6, BLACK_PEN);
				oldPen = (HPEN)SelectObject(mdc, hPen);
			}
			else
				hBrush = CreateSolidBrush(RGB(0, 0, 50));
			oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
			Ellipse(mdc, 865, 115, 935, 185);
			SelectObject(mdc, oldBrush);
			DeleteObject(hBrush);
			if (traffic == 2) {
				SelectObject(mdc, oldPen);
			}
		}
		//자동차
		{
			hBrush = CreateSolidBrush(RGB(30, 250, 250));
			oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
			for (int i = 0; i < 8; i++)
			{
				Rectangle(mdc, car[i].x - car[i].xsize, car[i].y - car[i].ysize, car[i].x + car[i].xsize, car[i].y + car[i].ysize);
				Rectangle(mdc, car2[i].x - car2[i].xsize, car2[i].y - car2[i].ysize, car2[i].x + car2[i].xsize, car2[i].y + car2[i].ysize);
			}
			SelectObject(mdc, oldBrush); // 이전의 펜으로 돌아감
			DeleteObject(hBrush);
		}
		//행인
		{
			hBrush = CreateSolidBrush(RGB(50, 200, 250));
			oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
			Ellipse(mdc, man.x - man.xsize, man.y - man.ysize, man.x + man.xsize, man.y + man.ysize);
			SelectObject(mdc, oldBrush); // 이전의 펜으로 돌아감
			DeleteObject(hBrush);
		}

		DeleteObject(hPen);
		DeleteObject(oldPen);
		BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY);
		DeleteDC(mdc);
		EndPaint(hwnd, &ps);
		InvalidateRect(hwnd, NULL, FALSE);
		break;

	case WM_KEYDOWN:

		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_CHAR:
		if (wParam == 'a' || wParam == 'A')
		{
			if (stop == false)
				stop = true;
			else
				stop = false;
		}
		if (wParam == '+' && Speed > 10)
		{
			Speed -= 10;
			SetTimer(hwnd, 1, Speed, NULL);
			//SetTimer(hwnd, 2, Speed, NULL);
			SetTimer(hwnd, 3, Speed, NULL);
			SetTimer(hwnd, 4, Speed, NULL);
		}
		if (wParam == '-' && Speed < 100)
		{
			Speed += 10;
			SetTimer(hwnd, 1, Speed, NULL);
			//SetTimer(hwnd, 2, Speed, NULL);
			SetTimer(hwnd, 3, Speed, NULL);
			SetTimer(hwnd, 4, Speed, NULL);
		}
		if (wParam == 'q' || wParam == 'Q')
		{
			PostQuitMessage(0);
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
