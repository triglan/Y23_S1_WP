
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>

#include <random>

std::random_device rd;
std::uniform_int_distribution<> uid(0, 255);

#define UP 20
#define SIDE 20
#define SIZE 40
#define PlayerSIZE 5

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 1";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

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
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 400, 200, 818, 841, NULL, (HMENU)NULL, hInstance, NULL);
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
	//초기값
	PAINTSTRUCT ps;
	HDC hdc;

	HBRUSH oldBrush, p1Brush, p2Brush, o1Brush, o2Brush, o3Brush, o4Brush, Hatch;
	HBRUSH randBrush1, randBrush2, randBrush3, randBrush4, randBrush5;
	HBRUSH rb1, rb2, rb3, rb4, rb5;

	

	HPEN hPen, oldPen;
	static int x1 = 1, y1 = 1, p1size = 2;
	static int x2 = 18, y2 = 18, p2size = 2;
	static int a = 30, b = 30, c = 222;
	static int a2 = 30, b2 = 222, c2 = 33;

	static int p1shape = 3;
	static int p2shape = 2;
	srand(time(NULL));


	//장애물
	RECT tempRect;

	RECT orect1 = { 10 * SIZE, 10 * SIZE, 11 * SIZE, 11 * SIZE };
	RECT orect2 = { 5 * SIZE, 10 * SIZE, 6 * SIZE, 11 * SIZE };
	RECT orect3 = { 2 * SIZE, 5 * SIZE, 3 * SIZE, 6 * SIZE };
	RECT orect4 = { 12 * SIZE, 13 * SIZE, 13 * SIZE, 14*SIZE };
	RECT orect5 = { 15 * SIZE, 14 * SIZE, 16 * SIZE, 15 * SIZE };

	//색상 변경칸
	RECT crect1 = { 12 * SIZE, 12 * SIZE, 13 * SIZE, 13 * SIZE };
	RECT crect2 = { 7 * SIZE, 1 * SIZE, 8 * SIZE, 2 * SIZE };
	RECT crect3 = { 4 * SIZE, 15 * SIZE, 5 * SIZE, 16 * SIZE };
	RECT crect4 = { 2 * SIZE, 3 * SIZE, 3 * SIZE, 4*SIZE };
	RECT crect5 = { 5 * SIZE, 14 * SIZE, 6 * SIZE, 15 * SIZE };
	
	//모양 변경칸
	RECT srect1 = { 2 * SIZE, 3 * SIZE, 3 * SIZE, 4 * SIZE };
	RECT srect2 = { 5 * SIZE, 7 * SIZE, 6 * SIZE, 8 * SIZE };
	RECT srect3 = { 11 * SIZE, 4 * SIZE, 12 * SIZE, 5 * SIZE };
	RECT srect4 = { 8 * SIZE, 7 * SIZE, 9 * SIZE, 8 * SIZE };
	RECT srect5 = { 18 * SIZE, 14 * SIZE, 19 * SIZE, 15 * SIZE };

	//크기 변경칸
	RECT brect1 = { 3 * SIZE, 6 * SIZE, 4 * SIZE, 7 * SIZE };
	RECT brect2 = { 7 * SIZE, 10 * SIZE, 8 * SIZE, 11 * SIZE };
	RECT brect3 = { 14 * SIZE, 8 * SIZE, 15 * SIZE, 9 * SIZE };
	RECT brect4 = { 16 * SIZE, 17 * SIZE, 17 * SIZE, 18 * SIZE };
	RECT brect5 = { 1 * SIZE, 14 * SIZE, 2 * SIZE, 15 * SIZE };


	static bool p1turn = true;
	static bool error = false;

	static bool randColor = true;
	static bool changeColor1 = false;
	static bool changeColor2 = false;
	static bool FirstColor1 = false;
	static bool FirstColor2 = false;

	static bool bigger1 = false;
	static bool bigger2 = false;

	TCHAR lpOut[100];
	wsprintf(lpOut, L"ERROR : Next Turn");

	srand(time(NULL));

	//플레이어
	RECT player1 = { x1 * SIZE + SIZE / 2 - p1size * PlayerSIZE , y1 * SIZE + SIZE / 2 - p1size * PlayerSIZE,
			x1 * SIZE + SIZE / 2 + p1size * PlayerSIZE, y1 * SIZE + SIZE / 2 + p1size * PlayerSIZE };

	RECT player2 = { x2 * SIZE + SIZE / 2 - p2size * PlayerSIZE, y2 * SIZE + SIZE / 2 - p2size * PlayerSIZE,
		x2 * SIZE + SIZE / 2 + p2size * PlayerSIZE, y2 * SIZE + SIZE / 2 + p2size * PlayerSIZE };

	POINT Tripoint1[10] = { {x1 * SIZE + SIZE / 2, y1 * SIZE + SIZE / 2 - p1size * PlayerSIZE},
		{x1 * SIZE + SIZE / 2 + p1size * PlayerSIZE, y1 * SIZE + SIZE / 2 + p1size * PlayerSIZE},
		{x1* SIZE + SIZE / 2 - p1size * PlayerSIZE, y1* SIZE + SIZE / 2 + p1size * PlayerSIZE} };

	POINT Tripoint2[10] = { {x2 * SIZE + SIZE / 2, y2 * SIZE + SIZE / 2 - p2size * PlayerSIZE},
		{x2 * SIZE + SIZE / 2 + p2size * PlayerSIZE, y2 * SIZE + SIZE / 2 + p2size * PlayerSIZE},
		{x2* SIZE + SIZE / 2 - p2size * PlayerSIZE, y2* SIZE + SIZE / 2 + p2size * PlayerSIZE} };


	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		//보드판 그리기
		{
			for (int x = 0; x <= SIDE; x++)
			{
				MoveToEx(hdc, x * SIZE, 0, NULL);
				LineTo(hdc, x * SIZE, UP * SIZE);
			}
			for (int y = 0; y <= UP; y++)
			{
				MoveToEx(hdc, 0, y * SIZE, NULL);
				LineTo(hdc, SIDE * SIZE, y * SIZE);
			}
		}
		//Brush
		{
			p1Brush = CreateSolidBrush(RGB(a, b, c));
			Hatch = CreateHatchBrush(HS_DIAGCROSS, (RGB(a2, b2, c2)));
			

			o1Brush = CreateSolidBrush(RGB(255, 0, 0));
			o2Brush = CreateSolidBrush(RGB(0, 0, 255));
			o3Brush = CreateSolidBrush(RGB(0, 255, 0));
			oldBrush = (HBRUSH)SelectObject(hdc, o1Brush);

			randBrush1 = CreateSolidBrush(RGB(12, 80, 65));
			randBrush2 = CreateSolidBrush(RGB(210, 170, 50));
			randBrush3 = CreateSolidBrush(RGB(155, 20, 98));
			randBrush4 = CreateSolidBrush(RGB(125, 89, 123));
			randBrush5 = CreateSolidBrush(RGB(250, 40, 150));
			
		}

		//오브젝트
		{
			//장애물
			FillRect(hdc, &orect1, o1Brush);
			FillRect(hdc, &orect2, o1Brush);
			FillRect(hdc, &orect3, o1Brush);
			FillRect(hdc, &orect4, o1Brush);
			FillRect(hdc, &orect5, o1Brush);
			//색바꾸기
			FillRect(hdc, &crect1, randBrush1);
			FillRect(hdc, &crect2, randBrush2);
			FillRect(hdc, &crect3, randBrush3);
			FillRect(hdc, &crect4, randBrush4);
			FillRect(hdc, &crect5, randBrush5);
			//모양바꾸기
			FillRect(hdc, &srect1, o2Brush);
			FillRect(hdc, &srect2, o2Brush);
			FillRect(hdc, &srect3, o2Brush);
			FillRect(hdc, &srect4, o2Brush);
			FillRect(hdc, &srect5, o2Brush);
			//크기바꾸기
			FillRect(hdc, &brect1, o3Brush);
			FillRect(hdc, &brect2, o3Brush);
			FillRect(hdc, &brect3, o3Brush);
			FillRect(hdc, &brect4, o3Brush);
			FillRect(hdc, &brect5, o3Brush);
		}

		SelectObject(hdc, p1Brush);
		switch (p1shape)
		{
		case 0:
			FillRect(hdc, &player1, p1Brush);
			break;
		case 1:
			Ellipse(hdc, x1 * SIZE + SIZE / 2 - p1size * PlayerSIZE, y1 * SIZE + SIZE / 2 - p1size * PlayerSIZE,
				x1 * SIZE + SIZE / 2 + p1size * PlayerSIZE, y1 * SIZE + SIZE / 2 + p1size * PlayerSIZE);
			break;
		case 2:
			Polygon(hdc, Tripoint1, 3);
			break;
		case 3:
			Pie(hdc, x1 * SIZE + SIZE / 2 - p1size * PlayerSIZE, y1 * SIZE + SIZE / 2 - p1size * PlayerSIZE, 
				x1 * SIZE + SIZE / 2 + p1size * PlayerSIZE, y1 * SIZE + SIZE / 2 + p1size * PlayerSIZE,
				x1 * SIZE + SIZE / 2 + p1size * PlayerSIZE, y1 * SIZE + SIZE / 2 - p1size * PlayerSIZE, 
				x1 * SIZE + SIZE / 2 + p1size * PlayerSIZE, y1 * SIZE + SIZE / 2 + p1size * PlayerSIZE);
			break;
		default:
			break;
		}
		
		SelectObject(hdc, Hatch);
		switch (p2shape)
		{
		case 0:
			FillRect(hdc, &player2, Hatch);
			break;
		case 1:
			Ellipse(hdc, x2 * SIZE + SIZE / 2 - p2size * PlayerSIZE, y2 * SIZE + SIZE / 2 - p2size * PlayerSIZE,
				x2 * SIZE + SIZE / 2 + p2size * PlayerSIZE, y2 * SIZE + SIZE / 2 + p2size * PlayerSIZE);
			break;
		case 2:
			Polygon(hdc, Tripoint2, 3);
			break;
		case 3:
			Pie(hdc, x2 * SIZE + SIZE / 2 - p2size * PlayerSIZE, y2 * SIZE + SIZE / 2 - p2size * PlayerSIZE,
				x2 * SIZE + SIZE / 2 + p2size * PlayerSIZE, y2 * SIZE + SIZE / 2 + p2size * PlayerSIZE,
				x2 * SIZE + SIZE / 2 + p2size * PlayerSIZE, y2 * SIZE + SIZE / 2 - p2size * PlayerSIZE,
				x2 * SIZE + SIZE / 2 + p2size * PlayerSIZE, y2 * SIZE + SIZE / 2 + p2size * PlayerSIZE);
			break;
		default:
			break;
		}

		if (error)
		{
			TextOut(hdc, 340, 300, lpOut, lstrlen(lpOut));

		}

		EndPaint(hwnd, &ps);
		break;

	case WM_CHAR:
	{
		hdc = BeginPaint(hwnd, &ps);
		if (wParam == 'q' || wParam == 'Q')
		{
			PostQuitMessage(0);
		}
		else if (wParam == 'r' || wParam == 'R')
		{
			x1 = 1, y1 = 1, p1size = 2;
			x2 = 18, y2 = 18, p2size = 2;
			a = 30, b = 30, c = 222;
			a2 = 30, b2 = 222, c2 = 33;
		}
		if (p1turn)
		{
			if (wParam == 'w' || wParam == 'W')
			{
				if (0 < y1)
				{
					y1--;
					//충돌 처리
					{
						player1 = { x1 * SIZE + SIZE / 2 - p2size * PlayerSIZE , y1 * SIZE + SIZE / 2 - p2size * PlayerSIZE,
						x1 * SIZE + SIZE / 2 + p2size * PlayerSIZE, y1 * SIZE + SIZE / 2 + p2size * PlayerSIZE };
						if (IntersectRect(&tempRect, &player1, &orect1))
							y1++;
						if (IntersectRect(&tempRect, &player1, &orect2))
							y1++;
						if (IntersectRect(&tempRect, &player1, &orect3))
							y1++;
						if (IntersectRect(&tempRect, &player1, &orect4))
							y1++;
						if (IntersectRect(&tempRect, &player1, &orect5))
							y1++;
					}

				}
			}
			else if (wParam == 's' || wParam == 'S')
			{
				if (y1 < UP - 1)
				{
					y1++;
					//충돌 처리
					{
						player1 = { x1 * SIZE + SIZE / 2 - p2size * PlayerSIZE , y1 * SIZE + SIZE / 2 - p2size * PlayerSIZE,
						x1 * SIZE + SIZE / 2 + p2size * PlayerSIZE, y1 * SIZE + SIZE / 2 + p2size * PlayerSIZE };
						if (IntersectRect(&tempRect, &player1, &orect1))
							y1--;
						if (IntersectRect(&tempRect, &player1, &orect2))
							y1--;
						if (IntersectRect(&tempRect, &player1, &orect3))
							y1--;
						if (IntersectRect(&tempRect, &player1, &orect4))
							y1--;
						if (IntersectRect(&tempRect, &player1, &orect5))
							y1--;
					}
				}
			}
			else if (wParam == 'd' || wParam == 'D')
			{
				if (x1 < SIDE - 1)
				{
					x1++;
					//충돌 처리
					{
						player1 = { x1 * SIZE + SIZE / 2 - p2size * PlayerSIZE , y1 * SIZE + SIZE / 2 - p2size * PlayerSIZE,
						x1 * SIZE + SIZE / 2 + p2size * PlayerSIZE, y1 * SIZE + SIZE / 2 + p2size * PlayerSIZE };
						if (IntersectRect(&tempRect, &player1, &orect1))
							x1--;
						if (IntersectRect(&tempRect, &player1, &orect2))
							x1--;
						if (IntersectRect(&tempRect, &player1, &orect3))
							x1--;
						if (IntersectRect(&tempRect, &player1, &orect4))
							x1--;
						if (IntersectRect(&tempRect, &player1, &orect5))
							x1--;
					}
				}
			}
			else if (wParam == 'a' || wParam == 'A')
			{
				if (0 < x1)
				{
					x1--;
					//충돌 처리
					{
						player1 = { x1 * SIZE + SIZE / 2 - p2size * PlayerSIZE , y1 * SIZE + SIZE / 2 - p2size * PlayerSIZE,
						x1 * SIZE + SIZE / 2 + p2size * PlayerSIZE, y1 * SIZE + SIZE / 2 + p2size * PlayerSIZE };
						if (IntersectRect(&tempRect, &player1, &orect1))
							x1++;
						if (IntersectRect(&tempRect, &player1, &orect2))
							x1++;
						if (IntersectRect(&tempRect, &player1, &orect3))
							x1++;
						if (IntersectRect(&tempRect, &player1, &orect4))
							x1++;
						if (IntersectRect(&tempRect, &player1, &orect5))
							x1++;
					}
				}
			}

			
		}
	}

	//턴 검사
	if (wParam == 'w' || wParam == 'W' || wParam == 's' || wParam == 'S' ||
		wParam == 'd' || wParam == 'D' || wParam == 'a' || wParam == 'A')
	{
		error = false;
		if (!p1turn)
		{
			error = true;
			ReleaseDC(hwnd, hdc);
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		p1turn = false;

		//모양 충돌
		{
			if (IntersectRect(&tempRect, &player1, &srect1))
			{
				p1shape++;
				if (p1shape > 3)
					p1shape = 0;
			}
			if (IntersectRect(&tempRect, &player1, &srect2))
			{
				p1shape++;
				if (p1shape > 3)
					p1shape = 0;
			}
			if (IntersectRect(&tempRect, &player1, &srect3))
			{
				p1shape++;
				if (p1shape > 3)
					p1shape = 0;
			}
			if (IntersectRect(&tempRect, &player1, &srect4))
			{
				p1shape++;
				if (p1shape > 3)
					p1shape = 0;
			}
			if (IntersectRect(&tempRect, &player1, &srect5))
			{
				p1shape++;
				if (p1shape > 3)
					p1shape = 0;
			}
		}
		//색 충돌
		{
			//srand로 안바뀔 때가 잇어서 더 확실하게 바꿈
			if (IntersectRect(&tempRect, &player1, &crect1))
				a = uid(rd), b = uid(rd), c = uid(rd);
			else if (IntersectRect(&tempRect, &player1, &crect2))
				a = uid(rd), b = uid(rd), c = uid(rd);
			else if (IntersectRect(&tempRect, &player1, &crect3))
				a = uid(rd), b = uid(rd), c = uid(rd);
			else if (IntersectRect(&tempRect, &player1, &crect4))
				a = uid(rd), b = uid(rd), c = uid(rd);
			else if (IntersectRect(&tempRect, &player1, &crect5))
				a = uid(rd), b = uid(rd), c = uid(rd);

			//if (IntersectRect(&tempRect, &player1, &crect1))
			//	a = rand() % 256, b = rand() % 256, c = rand() % 256;
			//else if (IntersectRect(&tempRect, &player1, &crect2))
			//	a = rand() % 256, b = rand() % 256, c = rand() % 256;
			//else if (IntersectRect(&tempRect, &player1, &crect3))
			//	a = rand() % 256, b = rand() % 256, c = rand() % 256;
			//else if (IntersectRect(&tempRect, &player1, &crect4))
			//	a = rand() % 256, b = rand() % 256, c = rand() % 256;
			//else if (IntersectRect(&tempRect, &player1, &crect5))
			//	a = rand() % 256, b = rand() % 256, c = rand() % 256;

			printf("%d, %d, %d\n", a, b, c);
		}
		//크기 충돌
		{
			if (IntersectRect(&tempRect, &player1, &brect1))
			{
				if (bigger1)
				{
					p1size++;
					if (p1size >= 4)
						bigger1 = false;
				}
				else
				{
					p1size--;
					if (p1size <= 1)
						bigger1 = true;
				}

			}
			else if (IntersectRect(&tempRect, &player1, &brect2))
			{
				if (bigger1)
				{
					p1size++;
					if (p1size >= 4)
						bigger1 = false;
				}
				else
				{
					p1size--;
					if (p1size <= 1)
						bigger1 = true;
				}

			}
			else if (IntersectRect(&tempRect, &player1, &brect3))
			{
				if (bigger1)
				{
					p1size++;
					if (p1size >= 4)
						bigger1 = false;
				}
				else
				{
					p1size--;
					if (p1size <= 1)
						bigger1 = true;
				}

			}
			else if (IntersectRect(&tempRect, &player1, &brect4))
			{
				if (bigger1)
				{
					p1size++;
					if (p1size >= 4)
						bigger1 = false;
				}
				else
				{
					p1size--;
					if (p1size <= 1)
						bigger1 = true;
				}

			}
			else if (IntersectRect(&tempRect, &player1, &brect5))
			{
				if (bigger1)
				{
					p1size++;
					if (p1size >= 4)
						bigger1 = false;
				}
				else
				{
					p1size--;
					if (p1size <= 1)
						bigger1 = true;
				}

			}
		}

	}

	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		
		if(!p1turn)
		{
			if (wParam == VK_LEFT)
			{
				if (0 < x2)
				{
					x2--;
					//충돌 처리
					{
						player2 = { x2 * SIZE + SIZE / 2 - p2size * PlayerSIZE, y2 * SIZE + SIZE / 2 - p2size * PlayerSIZE,
						x2 * SIZE + SIZE / 2 + p2size * PlayerSIZE, y2 * SIZE + SIZE / 2 + p2size * PlayerSIZE };
						if (IntersectRect(&tempRect, &player2, &orect1))
							x2++;
						if (IntersectRect(&tempRect, &player2, &orect2))
							x2++;
						if (IntersectRect(&tempRect, &player2, &orect3))
							x2++;
						if (IntersectRect(&tempRect, &player2, &orect4))
							x2++;
						if (IntersectRect(&tempRect, &player2, &orect5))
							x2++;
					}
				}
			}
			else if (wParam == VK_RIGHT)
			{
				if (x2 < SIDE - 1)
				{
					x2++;
					//충돌 처리
					{
						player2 = { x2 * SIZE + SIZE / 2 - p2size * PlayerSIZE, y2 * SIZE + SIZE / 2 - p2size * PlayerSIZE,
						x2 * SIZE + SIZE / 2 + p2size * PlayerSIZE, y2 * SIZE + SIZE / 2 + p2size * PlayerSIZE };
						if (IntersectRect(&tempRect, &player2, &orect1))
							x2--;
						if (IntersectRect(&tempRect, &player2, &orect2))
							x2--;
						if (IntersectRect(&tempRect, &player2, &orect3))
							x2--;
						if (IntersectRect(&tempRect, &player2, &orect4))
							x2--;
						if (IntersectRect(&tempRect, &player2, &orect5))
							x2--;
					}
				}
			}
			else if (wParam == VK_UP)
			{
				if (0 < y2)
				{
					y2--;
					//충돌 처리
					{
						player2 = { x2 * SIZE + SIZE / 2 - p2size * PlayerSIZE, y2 * SIZE + SIZE / 2 - p2size * PlayerSIZE,
						x2 * SIZE + SIZE / 2 + p2size * PlayerSIZE, y2 * SIZE + SIZE / 2 + p2size * PlayerSIZE };
						if (IntersectRect(&tempRect, &player2, &orect1))
							y2++;
						if (IntersectRect(&tempRect, &player2, &orect2))
							y2++;
						if (IntersectRect(&tempRect, &player2, &orect3))
							y2++;
						if (IntersectRect(&tempRect, &player2, &orect4))
							y2++;
						if (IntersectRect(&tempRect, &player2, &orect5))
							y2++;
					}
				}
			}
			else if (wParam == VK_DOWN)
			{
				if (y2 < UP - 1)
				{
					y2++;
					//충돌 처리
					{
						player2 = { x2 * SIZE + SIZE / 2 - p2size * PlayerSIZE, y2 * SIZE + SIZE / 2 - p2size * PlayerSIZE,
						x2 * SIZE + SIZE / 2 + p2size * PlayerSIZE, y2 * SIZE + SIZE / 2 + p2size * PlayerSIZE };
						if (IntersectRect(&tempRect, &player2, &orect1))
							y2--;
						if (IntersectRect(&tempRect, &player2, &orect2))
							y2--;
						if (IntersectRect(&tempRect, &player2, &orect3))
							y2--;
						if (IntersectRect(&tempRect, &player2, &orect4))
							y2--;
						if (IntersectRect(&tempRect, &player2, &orect5))
							y2--;
					}
				}

			}
		}
		
		if (wParam == VK_LEFT || wParam == VK_RIGHT || wParam == VK_UP || wParam == VK_DOWN)
		{
			error = false;
			if (p1turn)
			{
				error = true;
				ReleaseDC(hwnd, hdc);
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			}
			p1turn = true;

			//모양 충돌
			{
				if (IntersectRect(&tempRect, &player2, &srect1))
				{
					p2shape++;
					if (p2shape > 3)
						p2shape = 0;
				}
				if (IntersectRect(&tempRect, &player2, &srect2))
				{
					p2shape++;
					if (p2shape > 3)
						p2shape = 0;
				}
				if (IntersectRect(&tempRect, &player2, &srect3))
				{
					p2shape++;
					if (p2shape > 3)
						p2shape = 0;
				}
				if (IntersectRect(&tempRect, &player2, &srect4))
				{
					p2shape++;
					if (p2shape > 3)
						p2shape = 0;
				}
				if (IntersectRect(&tempRect, &player2, &srect5))
				{
					p2shape++;
					if (p2shape > 3)
						p2shape = 0;
				}
			}

			//색 충돌
			{
				if (IntersectRect(&tempRect, &player2, &crect1))
					a2 = rand() % 256, b2 = rand() % 256, c2 = rand() % 256;
				else if (IntersectRect(&tempRect, &player2, &crect2))
					a2 = rand() % 256, b2 = rand() % 256, c2 = rand() % 256;
				else if (IntersectRect(&tempRect, &player2, &crect3))
					a2 = rand() % 256, b2 = rand() % 256, c2 = rand() % 256;
				else if (IntersectRect(&tempRect, &player2, &crect4))
					a2 = rand() % 256, b2 = rand() % 256, c2 = rand() % 256;
				else if (IntersectRect(&tempRect, &player2, &crect5))
					a2 = rand() % 256, b2 = rand() % 256, c2 = rand() % 256;
			}
			//크기 충돌
			{
				if (IntersectRect(&tempRect, &player2, &brect1))
				{
					if (bigger2)
					{
						p2size++;
						if (p2size >= 4)
							bigger2 = false;
					}
					else
					{
						p2size--;
						if (p2size <= 1)
							bigger2 = true;
					}

				}
				else if (IntersectRect(&tempRect, &player2, &brect2))
				{
					if (bigger2)
					{
						p2size++;
						if (p2size >= 4)
							bigger2 = false;
					}
					else
					{
						p2size--;
						if (p2size <= 1)
							bigger2 = true;
					}

				}
				else if (IntersectRect(&tempRect, &player2, &brect3))
				{
					if (bigger2)
					{
						p2size++;
						if (p2size >= 4)
							bigger2 = false;
					}
					else
					{
						p2size--;
						if (p2size <= 1)
							bigger2 = true;
					}

				}
				else if (IntersectRect(&tempRect, &player2, &brect4))
				{
					if (bigger2)
					{
						p2size++;
						if (p2size >= 4)
							bigger2 = false;
					}
					else
					{
						p2size--;
						if (p2size <= 1)
							bigger2 = true;
					}

				}
				else if (IntersectRect(&tempRect, &player2, &brect5))
				{
					if (bigger2)
					{
						p2size++;
						if (p2size >= 4)
							bigger2 = false;
					}
					else
					{
						p2size--;
						if (p2size <= 1)
							bigger2 = true;
					}

				}
			}
		}

		ReleaseDC(hwnd, hdc);
		InvalidateRect(hwnd, NULL, TRUE);
		break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}