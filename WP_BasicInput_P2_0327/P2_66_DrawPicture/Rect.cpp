#include <windows.h>
#include <tchar.h>
#include <time.h>
#include <stdio.h>

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 1";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int randDivX;
int randDivY;

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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 300, 200, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
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
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	SIZE size;

	srand(time(NULL));
	randDivX = rand() % 9 + 2;
	randDivY = rand() % 9 + 2;
	int dx = 760 / randDivX;
	int dy = 560 / randDivY;

	static TCHAR str[100][1000];

	//int tdx = dx * 0.1;
	//int tdy = dy * 0.1;
	//
	//int ndx = dx * 0.9;
	//int ndy = dy * 0.9;

	int r1, g1, b1;
	int r2, g2, b2;


	TCHAR temp[100] = { 'X' };

	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//randDivY, randDivX
		for (int Bigy = 0; Bigy < randDivY; Bigy++)
		{
			for (int Bigx = 0; Bigx < randDivX; Bigx++)
			{
				//Box
				/*
					TODO :
					1. 공백과 문자로 문자열을 채워넣어서 만든다.
					2. 배경을 먼저 그리고 문자만 따로 그린다.
				*/
				{
					r1 = rand() % 257, g1 = rand() % 257, b1 = rand() % 257;
					r2 = rand() % 257, g2 = rand() % 257, b2 = rand() % 257;

					SetBkColor(hdc, RGB(r1, g1, b1));
					SetTextColor(hdc, RGB(r2, g2, b2));
				}

				for (int y = 0; y < dy / 16; y++)
				{
					rect.left = Bigx * dx;
					rect.top = Bigy * dy + y * 16;
					rect.right = (Bigx + 1) * dx;
					rect.bottom = Bigy * dy + (y + 1) * 16;

					for (int x = 0; x < dx / 9; x++)
					{
						if (x == y || x == (dy / 16 - y - 1))
							str[y][x] = '*';
						else
							str[y][x] = ' ';
					}

					//TextOut(hdc, (Bigx * dx), (Bigy * dy) + y * 16, str[y], lstrlen(str[y]));//출력
					DrawText(hdc, str[y], lstrlen(str[y]), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

				}

#ifdef tempman
				//꽉채우는 도형
				for (int y = tdy; y < dy - tdy; y = y + 16)
				{
					for (int x = tdx; x < dx - tdx; x = x + 9)
					{
						TextOut(hdc, (Bigx * dx) + x, (Bigy * dy) + y, temp, lstrlen(temp));//출력
					}
				}
				//꽉채우는 도형, ver.함수내에서 계산
				for (int y = tdy / 16; y < (dy - tdy) / 16; y++)
				{
					for (int x = tdx / 9; x < (dx - tdx) / 9; x++)
					{
						TextOut(hdc, (Bigx * dx) + x * 9, (Bigy * dy) + y * 16, temp, lstrlen(temp));//출력
					}
				}

				//DefaultX
				for (int y = 0; y < dy / 16; y++)
				{
					for (int x = 0; x < dx / 9; x++)
					{
						if (x == y || x == (dy / 16 - y - 1))
							TextOut(hdc, (Bigx * dx) + x * 9, (Bigy * dy) + y * 16, temp, lstrlen(temp));//출력
					}
				}
				//DefaultX
				for (int y = 2; y < dy / 16; y++)
				{
					for (int x = 2; x < dx / 9; x++)
					{
						if (x == y || x == (dy / 16 - y - 1))
							TextOut(hdc, (Bigx * dx) + x * 9, (Bigy * dy) + y * 16, temp, lstrlen(temp));//출력
					}
				}

#endif


			}
		}


		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}