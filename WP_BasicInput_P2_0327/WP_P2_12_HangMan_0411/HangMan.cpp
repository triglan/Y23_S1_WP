
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>

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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 300, 200, 1200, 700, NULL, (HMENU)NULL, hInstance, NULL);
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
	srand(time(NULL));

	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	RECT rect[26];
	RECT srect[26];
	TCHAR lpOut[26][2];
	{
		lpOut[0][0] = 'a';
		lpOut[1][0] = 'b';
		lpOut[2][0] = 'c';
		lpOut[3][0] = 'd';
		lpOut[4][0] = 'e';
		lpOut[5][0] = 'f';
		lpOut[6][0] = 'g';
		lpOut[7][0] = 'h';
		lpOut[8][0] = 'i';
		lpOut[9][0] = 'j';
		lpOut[10][0] = 'k';
		lpOut[11][0] = 'l';
		lpOut[12][0] = 'm';
		lpOut[13][0] = 'n';
		lpOut[14][0] = 'o';
		lpOut[15][0] = 'p';
		lpOut[16][0] = 'q';
		lpOut[17][0] = 'r';
		lpOut[18][0] = 's';
		lpOut[19][0] = 't';
		lpOut[20][0] = 'u';
		lpOut[21][0] = 'v';
		lpOut[22][0] = 'w';
		lpOut[23][0] = 'x';
		lpOut[24][0] = 'y';
		lpOut[25][0] = 'z';
	}

	static bool Ans[26];
	static bool nAns[26];

	static bool getAns = false;

	static int count = 0;
	static int select = rand() % 10;

	static bool endGame = false;
	static bool failGame = false;

	static TCHAR clear[100];
	static TCHAR qstr[10][100];
	static TCHAR tempstr[10][100];
	{
		wsprintf(qstr[0], L"apple");
		wsprintf(qstr[1], L"ballon");
		wsprintf(qstr[2], L"camera");
		wsprintf(qstr[3], L"diary");
		wsprintf(qstr[4], L"example");
		wsprintf(qstr[5], L"famous");
		wsprintf(qstr[6], L"ground");
		wsprintf(qstr[7], L"interest");
		wsprintf(qstr[8], L"knock");
		wsprintf(qstr[9], L"lesson");
	}
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		//행맨
		{
			hBrush = CreateSolidBrush(RGB(30, 200, 200));
			hPen = CreatePen(PS_DOT, 2, RGB(30, 100, 200));
			SelectObject(hdc, hBrush);
			SelectObject(hdc, hPen);

			Rectangle(hdc, 25, 550, 600, 650);
			MoveToEx(hdc, 50, 550, NULL);
			LineTo(hdc, 50, 50);
			MoveToEx(hdc, 50, 50, NULL);
			LineTo(hdc, 450, 50);
			MoveToEx(hdc, 250, 50, NULL);
			LineTo(hdc, 250, 100);

			if (count > 0)
				Ellipse(hdc, 200, 100, 300, 200);
			if (count > 1)
			{
				MoveToEx(hdc, 250, 200, NULL);
				LineTo(hdc, 250, 350);
			}
			if (count > 2)
			{
				MoveToEx(hdc, 250, 200, NULL);
				LineTo(hdc, 350, 300);
			}
			if (count > 3)
			{
				MoveToEx(hdc, 250, 200, NULL);
				LineTo(hdc, 150, 300);
			}
			if (count > 4)
			{
				MoveToEx(hdc, 250, 350, NULL);
				LineTo(hdc, 350, 500);
			}
			if (count > 5)
			{
				MoveToEx(hdc, 250, 350, NULL);
				LineTo(hdc, 150, 500);
				failGame = true;
			}
		}

		for (int i = 0; i < 26; i++)
		{
			rect[i].left = 600 + (i % 5) * 50;
			rect[i].right = 600 + (i % 5 + 1) * 50;
			rect[i].top = 200 + (i / 5) * 50;
			rect[i].bottom = 200 + (i / 5 + 1) * 50;
		}
		for (int i = 0; i < lstrlen(qstr[select]); i++)
		{
			srect[i].left = 600 + i  * 50;
			srect[i].right = 650 + i * 50;
			srect[i].top = 50;
			srect[i].bottom = 100;
		}

		for (int i = 0; i < 26; i++)
		{
			hBrush = CreateSolidBrush(RGB(30, 170, 170));
			hPen = CreatePen(PS_DOT, 2, RGB(30, 100, 200));

			SetBkColor(hdc, RGB(30, 170, 170));
			SetTextColor(hdc, RGB(255, 255, 255));
			if (nAns[i] == true)
			{
				hBrush = CreateSolidBrush(RGB(15, 100, 100));
				SetBkColor(hdc, RGB(15, 100, 100));
				SetTextColor(hdc, RGB(100, 100, 100));
			}
			if (Ans[i] == true)
			{
				hBrush = CreateSolidBrush(RGB(50, 250, 250));
				SetBkColor(hdc, RGB(50, 250, 250));
				for (int c = 0; c < lstrlen(qstr[select]); c++)
				{
					if (i + 97 == qstr[select][c])
					{
						tempstr[c][0] = qstr[select][c];
					}
				}
			}
			SelectObject(hdc, hBrush);
			
			Rectangle(hdc, rect[i].left, rect[i].top - 20, rect[i].right, rect[i].bottom - 20);

			DrawText(hdc, lpOut[i], 1, &rect[i], DT_WORDBREAK | DT_CENTER | DT_EDITCONTROL); //--- 한 라인, 수직/수평 중앙=
		}

		for (int i = 0; i <= lstrlen(qstr[select]); i++)
		{
			hBrush = CreateSolidBrush(RGB(30, 170, 170));
			SelectObject(hdc, hBrush);
			SetBkColor(hdc, RGB(30, 170, 170));
			SetTextColor(hdc, RGB(255, 255, 255));

			Rectangle(hdc, srect[i].left, srect[i].top - 20, srect[i].right, srect[i].bottom - 20);
			if (tempstr[i][0] != '\0')
			{
				SetBkColor(hdc, RGB(30, 170, 170));
				SetTextColor(hdc, RGB(255, 255, 255));
				DrawText(hdc, tempstr[i], 1, &srect[i], DT_WORDBREAK | DT_CENTER | DT_EDITCONTROL);
			}
		}
		//클리어 확인
		endGame = true;
		for (int i = 0; i < lstrlen(qstr[select]); i++)
		{
			if (tempstr[i][0] == '\0')
				endGame = false;
		}

		hBrush = CreateSolidBrush(RGB(0, 0, 0));
		SelectObject(hdc, hBrush);
		SetBkColor(hdc, RGB(255, 255, 255));
		SetTextColor(hdc, RGB(0, 0, 0));

		if (endGame)
		{
			wsprintf(clear, L"Game Clear");
			TextOut(hdc, 400, 300, clear, lstrlen(clear));
		}
		if (failGame)
		{
			wsprintf(clear, L"YOU LOSE");
			TextOut(hdc, 400, 260, clear, lstrlen(clear));
		}
		EndPaint(hwnd, &ps);
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);
		printf("%c : %d // select : %d\n",wParam, wParam, select);
		printf("lstrlen : % d", lstrlen(qstr[select]));
		if (wParam == '1')
		{
			for (int i = 0; i < 26; i++)
			{
				lpOut[i][0] = 0;
				lpOut[i][1] = 0;
				Ans[i] = 0;
				nAns[i] = 0;
			}
			getAns = false;
			count = 0;
			select = rand() % 10;
			endGame = false;
			failGame = false;

			for (int i = 0; i < 100; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					qstr[j][i] = 0;
					tempstr[j][i] = 0;
				}
			clear[i] = 0;
			}
		}
		if (wParam == '2')
		{
			PostQuitMessage(0);
			break;
		}
		if (!endGame && !failGame)
		{
			if (wParam >= 'A' && wParam <= 'z')
			{
				getAns = false;

				for (int i = 0; i < lstrlen(qstr[select]); i++)
				{
					if (qstr[select][i] == wParam)
					{
						Ans[wParam - 97] = true;
						getAns = true;
					}
				}
				if (!getAns)
				{
					nAns[wParam - 97] = true;
					count++;
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