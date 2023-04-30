#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>
#include <random>
#include "resource.h"

#define WINDOWSIZE 800
#define XSIZE 30
#define YSIZE 15
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 1";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

struct BreakBrick {
	int x;
	int y;
	int xsize;
	int ysize;

	int a, b, c;
	int life;
	int dir;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevIsntace, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU2);

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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 300, 200, WINDOWSIZE + 18, WINDOWSIZE + 41, NULL, (HMENU)NULL, hInstance, NULL);
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

	//벽돌 만들기
	static BreakBrick player;
	static BreakBrick brick[100];
	static BreakBrick ball;
	static RECT rect[30];
	static RECT colball;
	static RECT colplayer;
	RECT rcTemp; //임시 Rect

	static int brickCount = 0;
	static bool drag = false;
	static bool start = true;
	static bool ballstart = false;
	static bool brickdir = false;
	int brickc = 0;

	static int Speed = 3;
	static int Timer1Count = 0;
	static int Timer2Count = 0;

	TCHAR str[100];
	switch (uMsg)
	{
	case WM_CREATE:
		//초기값
	{
		SetTimer(hwnd, 1, Speed, NULL);
		player = { 400,700,40,15,30,200,200 };
		ball = { 400,670,15,15,250,250,150,0,0 };
		for (int i = 0; i < 30; i++)
		{//x,y,sizex,y,r,g,b life
			brick[i] = { i % 10 * XSIZE * 2 + 100, (i / 10 * 20) + 100 + 20, 30, 10, 100, 100, 250, 1 };
			brickCount++;
		}
		for (int i = 0; i < 30; i++)
			rect[i] = { brick[i].x - brick[i].xsize, brick[i].y - brick[i].ysize, brick[i].x + brick[i].xsize, brick[i].y + brick[i].ysize };
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		//case ID_Start:
		//	break;
		//case ID_Reset:
		//	break;
		//case ID_End:
		//	break;
		//case ID_Fast:
		//	break;
		//case ID_Medium:
		//	break;
		//case ID_Slow:
		//	break;
		//case ID_Cyan:
		//	break;
		//case ID_Magenta:
		//	break;
		//case ID_Yellow:
		//	break;
		//case ID_Small:
		//	break;
		//case ID_Big:
		//	break;
		//case ID_3:
		//	break;
		//case ID_4:
		//	break;
		//case ID_5:
		//	break;
		}
	case WM_TIMER:

		switch (wParam)
		{
		case 1:
			Timer1Count++;
			Timer2Count++;

			break;
		case 2:
			break;

		default:
			break;
		}



		//블럭 이동
		if (Timer2Count % 100 == 0)
		{
			if (brickdir == true)
				brickdir = false;
			else
				brickdir = true;
		}
		//공튀기기
		if (start)
		{
			if (Timer1Count % 2 == 0)
			{
				//블럭 옮기기
				for (int i = 0; i < 30; i++)
				{
					if (brickdir)
						brick[i].x += 2;
					else
						brick[i].x -= 2;
				}

				if (ballstart)
				{
					if (ball.dir == 0)
					{
						ball.x += 5;
						ball.y -= 5;
					}
					else if (ball.dir == 1)
					{
						ball.x -= 5;
						ball.y -= 5;
					}
					else if (ball.dir == 2)
					{
						ball.x += 5;
						ball.y += 5;
					}
					else if (ball.dir == 3)
					{
						ball.x -= 5;
						ball.y += 5;
					}
				}
				for (int i = 0; i < 30; i++)
				{
					if (brick[i].life == 0 && brick[i].xsize > 0)
					{
						brick[i].xsize -= 3;
						brick[i].ysize -= 1;
					}
				}

			}
		}

		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_PAINT:
		//기본 생성
		hdc = BeginPaint(hwnd, &ps);

		printf("x : %d y : %d Timer1Count : %d Speed : %d\n", ball.x, ball.y, Timer1Count, Speed);
		for (int i = 0; i < 30; i++)
		{
			if (brick[i].life != 0)
				brickc++;
		}


		wsprintf(str, L"블럭 개수 : %d", brickc);
		if (start == false)
		{
			TextOut(hdc, 0, 0, str, lstrlen(str));
		}

		//충돌 이벤트
		{
			//Collision
			if (ball.x > WINDOWSIZE - ball.xsize)//오른쪽 충돌 시
			{
				if (ball.dir == 2)
				{
					ball.dir = 3;
				}
				if (ball.dir == 0)
				{
					ball.dir = 1;
				}
			}
			else if (ball.x < ball.xsize)//왼쪽
			{
				if (ball.dir == 1)
				{
					ball.dir = 0;
				}
				if (ball.dir == 3)
				{
					ball.dir = 2;
				}
			}
			else if (ball.y < ball.ysize)//위
			{
				if (ball.dir == 1)
				{
					ball.dir = 3;
				}
				if (ball.dir == 0)
				{
					ball.dir = 2;
				}
			}
			else if (ball.y > WINDOWSIZE - ball.ysize)//바닥으로 떨어졌을 때
			{
				ball.x = player.x;
				ball.y = player.y - player.ysize;
				ball.dir = 0;
			}

			colball = { ball.x - ball.xsize, ball.y - ball.ysize, ball.x + ball.xsize, ball.y + ball.ysize };
			//life = 0 이면 x,y사이즈 줄여서 사라지게 하기
			for (int i = 0; i < brickCount; i++)
			{
				if (IntersectRect(&rcTemp, &rect[i], &colball))
				{
					brick[i].life = 0;
					brick[i].a = rand() % 256, brick[i].b = rand() % 256, brick[i].c = rand() % 256;
				}
			}
		}
		//공과 플레이어 충돌
		colplayer = { player.x - player.xsize, player.y - player.ysize, player.x + player.xsize, player.y + player.ysize };
		colball = { ball.x - ball.xsize, ball.y - ball.ysize, ball.x + ball.xsize, ball.y + ball.ysize };
		if (IntersectRect(&rcTemp, &colplayer, &colball))
		{
			if ((rcTemp.right + rcTemp.left) < (colplayer.left + colplayer.right))//왼쪽에서 부딪쳤을 때
			{
				if (ball.dir == 2 || ball.dir == 3)//내려오는 공이면
				{
					ball.dir = 1;
				}
				else//올라오면
				{
					ball.dir = 3;
				}
			}
			else//오른쪽에서 부딪치면
			{
				if (ball.dir == 2 || ball.dir == 3)//내려오는 공이면
				{
					ball.dir = 0;
				}
				else//올라오면
				{
					ball.dir = 2;
				}
			}
		}

		//Paint
		{
			//SetROP2(hdc, R2_XORPEN);
			//hBrush = CreateSolidBrush(RGB(brick[0].a, brick[0].b, brick[0].c));
			//oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			for (int i = 0; i < brickCount; i++)
			{
				hBrush = CreateSolidBrush(RGB(brick[i].a, brick[i].b, brick[i].c));
				oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
				Rectangle(hdc, brick[i].x - brick[i].xsize, brick[i].y - brick[i].ysize, brick[i].x + brick[i].xsize, brick[i].y + brick[i].ysize);
				SelectObject(hdc, oldBrush); // 이전의 펜으로 돌아감
				DeleteObject(hBrush);
			}

			hBrush = CreateSolidBrush(RGB(player.a, player.b, player.c));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, player.x - player.xsize, player.y - player.ysize, player.x + player.xsize, player.y + player.ysize);
			SelectObject(hdc, oldBrush); // 이전의 펜으로 돌아감
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(RGB(ball.a, ball.b, ball.c));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, ball.x - ball.xsize, ball.y - ball.ysize, ball.x + ball.xsize, ball.y + ball.ysize);
			SelectObject(hdc, oldBrush); // 이전의 펜으로 돌아감
			DeleteObject(hBrush);
		}


		EndPaint(hwnd, &ps);
		break;
	case WM_MOUSEMOVE:
		if (drag)
		{
			player.x = LOWORD(lParam);
			player.y = HIWORD(lParam);
			InvalidateRect(hwnd, NULL, TRUE);
		}
		break;
	case WM_LBUTTONDOWN:
		drag = true;

		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONUP:
		drag = false;
		player = { 400,700,40,15,30,200,200 };
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:

		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_CHAR:
		if (wParam == 's' || wParam == 'S')
		{
			if (ballstart == true)
				ballstart = false;
			else
				ballstart = true;
		}
		if (wParam == 'p' || wParam == 'P')
		{
			if (start == true)
				start = false;
			else
				start = true;
		}
		if (wParam == '+' && Speed > 10)
		{
			Speed -= 10;
			SetTimer(hwnd, 1, Speed, NULL);
		}
		if (wParam == '-' && Speed < 100)
		{
			Speed += 10;
			SetTimer(hwnd, 1, Speed, NULL);
		}
		if (wParam == 'n' || wParam == 'N')
		{
			start = false;
			SetTimer(hwnd, 1, Speed, NULL);
			player = { 400,700,40,15,30,200,200 };
			ball = { 400,670,15,15,250,250,150,0,0 };
			for (int i = 0; i < 30; i++)
			{//x,y,sizex,y,r,g,b life
				brick[i] = { i % 10 * XSIZE * 2 + 100, (i / 10 * 20) + 100 + 20, 30, 10, 100, 100, 250, 1 };
				brickCount++;
			}
			for (int i = 0; i < 30; i++)
				rect[i] = { brick[i].x - brick[i].xsize, brick[i].y - brick[i].ysize, brick[i].x + brick[i].xsize, brick[i].y + brick[i].ysize };
		}
		if (wParam == 'q' || wParam == 'Q')
		{
			PostQuitMessage(0);
			break;
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
