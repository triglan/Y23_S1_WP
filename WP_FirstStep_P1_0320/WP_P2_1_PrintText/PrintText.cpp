#include <windows.h>
#include <tchar.h>

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
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
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
	TCHAR lpOut[100];
	int x1 = (rand() % 70) * 10, y1 = (rand() % 50) * 10;
	int x2 = (rand() % 70) * 10, y2 = (rand() % 50) * 10;
	int x3 = (rand() % 70) * 10, y3 = (rand() % 50) * 10;
	int x4 = (rand() % 70) * 10, y4 = (rand() % 50) * 10;
	
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		wsprintf(lpOut, L"1st sentence : (%d, %d)", x1, y1);
		TextOut(hdc, x1, y1, lpOut, lstrlen(lpOut));

		wsprintf(lpOut, L"2nd sentence : (%d, %d)", x2, y2);
		TextOut(hdc, x2, y2, lpOut, lstrlen(lpOut));

		wsprintf(lpOut, L"3rd sentence : (%d, %d)", x3, y3);
		TextOut(hdc, x3, y3, lpOut, lstrlen(lpOut));

		wsprintf(lpOut, L"4st sentence : (%d, %d)", x4, y4);
		TextOut(hdc, x4, y4, lpOut, lstrlen(lpOut));

		wsprintf(lpOut, L"center : (400, 300)");
		TextOut(hdc, 400, 300, lpOut, lstrlen(lpOut));




		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}