#include <windows.h>
#include <tchar.h>
#include <time.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming 2 3";

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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 600, 300, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
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

	TCHAR lpOut[100];
	srand(time(NULL));

	int x = rand() % 701;
	int y = rand() % 501;
	int n;	
	int count = rand() % 41 + 10;
	int r1 = rand() % 257, g1 = rand() % 257, b1 = rand() % 257;
	int br1 = rand() % 257, bg1 = rand() % 257, bb1 = rand() % 257;

	int i;
	for (i = 0; i < count; i++)
	{
		n = rand() % 10;
		lpOut[i] = n + 48;
	}
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		rect.left = x;
		rect.top = y;
		rect.right = x+100;
		rect.bottom = y+100;
		SetBkColor(hdc, RGB(br1, bg1, bb1));
		SetTextColor(hdc, RGB(r1, g1, b1));
		//wsprintf(lpOut, L"abcdefghijklmnopqrstuvwxyzsl;gjreghioilajsdajsufhoefhweioufbhoabcdefghij");
		DrawText(hdc, lpOut, i, &rect, DT_WORDBREAK | DT_CENTER | DT_EDITCONTROL); //--- 한 라인, 수직/수평 중앙=

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}