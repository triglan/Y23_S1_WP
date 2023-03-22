#include <windows.h>
#include <tchar.h>
#include <time.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 2";

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
	WndClass.hIcon = LoadCursor(NULL, IDI_HAND);
	WndClass.hCursor = LoadCursor(NULL, IDC_HAND);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_QUESTION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_THICKFRAME | WS_SYSMENU | WS_VSCROLL | WS_HSCROLL | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
		100, 50, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
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
	RECT rect1;
	RECT rect2;
	RECT rect3;
	RECT rect4;
	RECT rect5;
	RECT rect6;

	TCHAR lpOut[100];
	srand(time(NULL));

	int r1 = rand() % 257, g1 = rand() % 257, b1 = rand() % 257;
	int r2 = rand() % 257, g2 = rand() % 257, b2 = rand() % 257;
	int r3 = rand() % 257, g3 = rand() % 257, b3 = rand() % 257;
	int r4 = rand() % 257, g4 = rand() % 257, b4 = rand() % 257;
	int r5 = rand() % 257, g5 = rand() % 257, b5 = rand() % 257;
	int r6 = rand() % 257, g6 = rand() % 257, b6 = rand() % 257;
	
	int br1 = rand() % 257, bg1 = rand() % 257, bb1 = rand() % 257;
	int br2 = rand() % 257, bg2 = rand() % 257, bb2 = rand() % 257;
	int br3 = rand() % 257, bg3 = rand() % 257, bb3 = rand() % 257;
	int br4 = rand() % 257, bg4 = rand() % 257, bb4 = rand() % 257;
	int br5 = rand() % 257, bg5 = rand() % 257, bb5 = rand() % 257;
	int br6 = rand() % 257, bg6 = rand() % 257, bb6 = rand() % 257;

	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		rect1.left = 0;
		rect1.top = 0;
		rect1.right = 260;
		rect1.bottom = 290;
		SetBkColor(hdc, RGB(br1, bg1, bb1));
		SetTextColor(hdc, RGB(r1, g1, b1));
		wsprintf(lpOut, L"abcdefghijklmnopqrstuvwxyzsl;gjreghioilajsdajsufhoefhweioufbhoabcdefghij");
		DrawText(hdc, lpOut, lstrlen(lpOut), &rect1, DT_WORDBREAK | DT_CENTER | DT_EDITCONTROL); //--- 한 라인, 수직/수평 중앙=

		rect2.left = 260;
		rect2.top = 0;
		rect2.right = 520;
		rect2.bottom = 290;
		SetBkColor(hdc, RGB(br2, bg2, bb2));
		SetTextColor(hdc, RGB(r2, g2, b2));
		wsprintf(lpOut, L"ABCDEFGHIJKLMNOPQRSTUVWXY");
		DrawText(hdc, lpOut, lstrlen(lpOut), &rect2, DT_WORDBREAK | DT_CENTER | DT_EDITCONTROL); //--- 한 라인, 수직/수평 중앙=

		rect3.left = 520;
		rect3.top = 0;
		rect3.right = 720;
		rect3.bottom = 290;
		SetBkColor(hdc, RGB(br3, bg3, bb3));
		SetTextColor(hdc, RGB(r3, g3, b3));
		wsprintf(lpOut, L"abcde2354334626hoefhweioufbhoabcdefghij");
		DrawText(hdc, lpOut, lstrlen(lpOut), &rect3, DT_WORDBREAK | DT_CENTER | DT_EDITCONTROL); //--- 한 라인, 수직/수평 중앙=

		rect4.left = 0;
		rect4.top = 290;
		rect4.right = 260;
		rect4.bottom = 580;
		SetBkColor(hdc, RGB(br4, bg4, bb4));
		SetTextColor(hdc, RGB(r4, g4, b4));
		wsprintf(lpOut, L"abcdefgtjpiojpdofegnbcdefghij");
		DrawText(hdc, lpOut, lstrlen(lpOut), &rect4, DT_WORDBREAK | DT_CENTER | DT_EDITCONTROL); //--- 한 라인, 수직/수평 중앙=

		rect1.left = 260;
		rect1.top = 290;
		rect1.right = 520;
		rect1.bottom = 580;
		SetBkColor(hdc, RGB(br5, bg5, bb5));
		SetTextColor(hdc, RGB(r5, g5, b5));
		wsprintf(lpOut, L"abcdeiofjgdjioufbhoabcdefghij");
		DrawText(hdc, lpOut, lstrlen(lpOut), &rect1, DT_WORDBREAK | DT_CENTER | DT_EDITCONTROL); //--- 한 라인, 수직/수평 중앙=

		rect1.left = 520;
		rect1.top = 290;
		rect1.right = 720;
		rect1.bottom = 580;
		SetBkColor(hdc, RGB(br1, bg1, bb1));
		SetTextColor(hdc, RGB(r1, g1, b1));
		wsprintf(lpOut, L"abcdefghijklmnopqrstuvwxyzsl;gjreghioilajsdajsufhoefhweioufbhoabcdefghij");
		DrawText(hdc, lpOut, lstrlen(lpOut), &rect1, DT_WORDBREAK | DT_CENTER | DT_EDITCONTROL); //--- 한 라인, 수직/수평 중앙=


		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}