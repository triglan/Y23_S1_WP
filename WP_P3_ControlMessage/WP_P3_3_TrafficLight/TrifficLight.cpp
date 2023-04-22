#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>
#include <random>

#define WINDOWSIZE 1000
#define XSIZE 30
#define YSIZE 15
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 1";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

struct socar{
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
	WndClass.lpszMenuName = NULL;
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

	static socar car[8];
	static socar car2[8];

	static int Speed = 25;
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
	}
	case WM_TIMER:

		switch (wParam)
		{
		case 1:
			Timer1Count++;

			break;
		case 2:
			if(!stop)
				Timer2Count++;
			break;
		default:
			break;
		}
		//끝자락 지났는지 검사
		{
			printf("TimerCount1 : %d, TimerCount2 : %d\n", Timer1Count, Timer2Count);
			

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
			if (Timer1Count % 1 == 0)
			{
				car[0].y++;
				car[1].y++;
				if (traffic == 0 || traffic == 3)
				{
					if (car[1].y == 325)
					{
						car[0].y--;
						car[1].y--;
					}
					if (car[1].y > 325 && car[1].y < 600)
					{
						if (car[1].y >= 325)
						{
							car[0].y-=5;
							car[1].y-=5;
						}
					}
					if (car[1].y > 600 && car[1].y < 800)
					{
						if (car[1].y <= 800)
						{
							car[0].y+=5;
							car[1].y+=5;
						}
					}
				}
				if (car0pass)
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
				car[2].y--;
				car[3].y--;
				if (traffic == 0 || traffic == 3)
				{
					if (car[2].y == 675)
					{
						car[2].y++;
						car[3].y++;
					}
					if (car[3].y > 325 && car[3].y < 600)
					{
						if (car[3].y >= 325)
						{
							car[2].y -= 5;
							car[3].y -= 5;
						}
					}
					if (car[3].y > 600 && car[3].y < 800)
					{
						if (car[3].y <= 800)
						{
							car[2].y += 5;
							car[3].y += 5;
						}
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
			if (Timer1Count % 1 == 0)
			{
				car[4].x++;
				car[5].x++;
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
				car[6].x--;
				car[7].x--;
				if (traffic == 2 || traffic == 1)
				{
					if (car[6].x == 675)
					{
						car[6].x--;
						car[7].x--;
					}
					if (car[7].x > 325 && car[7].x < 600)
					{
						if (car[7].x >= 325)
						{
							car[6].x -= 5;
							car[7].x -= 5;
						}
					}
					if (car[7].x > 600 && car[7].x < 800)
					{
						if (car[7].x <= 800)
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

		//Traffic
		{
			if (Timer2Count % 275 == 0)
			{
				if (traffic == 0)//빨간불 -> 노란불
				{
					traffic = 1;
				}
			}
			if (Timer2Count % 114 == 0)
			{
				if (traffic == 1)//노란불 -> 파란불
				{
					traffic = 2;
				}
			}
			if (Timer2Count % 257 == 0)
			{
				if (traffic == 2)//파란불 -> 노란불
				{
					traffic = 3;
				}
			}
			if (Timer2Count % 116 == 0)
			{
				if (traffic == 3)//노란불 -> 빨간불
				{
					traffic = 0;
				}
			}
		}
		
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_PAINT:
		//기본 생성
		hdc = BeginPaint(hwnd, &ps);
		//경계선
		{
			hPen = CreatePen(PS_DOT, 1, BLACK_PEN);
			oldPen = (HPEN)SelectObject(hdc, hPen);
			MoveToEx(hdc, 400, 400, NULL);
			LineTo(hdc, 400, 600);
			MoveToEx(hdc, 400, 400, NULL);
			LineTo(hdc, 600, 400);
			MoveToEx(hdc, 600, 400, NULL);
			LineTo(hdc, 600, 600);
			MoveToEx(hdc, 400, 600, NULL);
			LineTo(hdc, 600, 600);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);

			hPen = CreatePen(PS_SOLID, 3, BLACK_PEN);
			SelectObject(hdc, hPen);
			MoveToEx(hdc, 400, 0, NULL);
			LineTo(hdc, 400, 400);
			MoveToEx(hdc, 600, 0, NULL);
			LineTo(hdc, 600, 400);
			MoveToEx(hdc, 400, 600, NULL);
			LineTo(hdc, 400, 1000);
			MoveToEx(hdc, 600, 600, NULL);
			LineTo(hdc, 600, 1000);
			MoveToEx(hdc, 0, 400, NULL);
			LineTo(hdc, 400, 400);
			MoveToEx(hdc, 0, 600, NULL);
			LineTo(hdc, 400, 600);
			MoveToEx(hdc, 600, 400, NULL);
			LineTo(hdc, 1000, 400);
			MoveToEx(hdc, 600, 600, NULL);
			LineTo(hdc, 1000, 600);
			SelectObject(hdc, oldPen);
			DeleteObject(hPen);
		}

		//신호등
		{
			Rectangle(hdc, 650, 100, 950, 200);
			if(traffic == 0)
				hBrush = CreateSolidBrush(RGB(255, 0, 0));
			else
				hBrush = CreateSolidBrush(RGB(50, 0, 0));
			SelectObject(hdc, hBrush);
			Ellipse(hdc, 665, 115, 735, 185);

			if (traffic == 1 || traffic == 3)
				hBrush = CreateSolidBrush(RGB(255, 255, 0));
			else
				hBrush = CreateSolidBrush(RGB(50, 50, 0));
			SelectObject(hdc, hBrush);
			Ellipse(hdc, 765, 115, 835, 185);
			
			if (traffic == 2)
				hBrush = CreateSolidBrush(RGB(0, 0, 255));
			else
				hBrush = CreateSolidBrush(RGB(0, 0, 50));
			SelectObject(hdc, hBrush);
			Ellipse(hdc, 865, 115, 935, 185);
		}

		//자동차
		hBrush = CreateSolidBrush(RGB(30, 250, 250));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		for (int i = 0; i < 8; i++)
		{
			Rectangle(hdc, car[i].x - car[i].xsize, car[i].y - car[i].ysize, car[i].x + car[i].xsize, car[i].y + car[i].ysize);
			Rectangle(hdc, car2[i].x - car2[i].xsize, car2[i].y - car2[i].ysize, car2[i].x + car2[i].xsize, car2[i].y + car2[i].ysize);
		}

		SelectObject(hdc, oldBrush); // 이전의 펜으로 돌아감
		DeleteObject(hBrush);
		EndPaint(hwnd, &ps);
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
			SetTimer(hwnd, 2, Speed, NULL);
			SetTimer(hwnd, 3, Speed, NULL);
			SetTimer(hwnd, 4, Speed, NULL);
		}
		if (wParam == '-' && Speed < 100)
		{
			Speed += 10;
			SetTimer(hwnd, 1, Speed, NULL);
			SetTimer(hwnd, 2, Speed, NULL);
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
