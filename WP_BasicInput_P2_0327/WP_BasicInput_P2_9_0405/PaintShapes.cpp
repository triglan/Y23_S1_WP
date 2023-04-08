
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 300, 200, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
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

	POINT Tripoint[10] = { {80, 340}, {160, 230}, {240, 340} };
	POINT Fivpoint[10] = { {620, 220}, {700, 280}, {660, 340}, {580, 340}, {540, 280} };
	POINT Sandpoint[10] = { {320, 60}, {440, 170}, {320, 170}, {440, 60} };

	switch (uMsg)
	{
	case WM_CREATE:
		break;

	case WM_CHAR:

	case WM_KEYDOWN:
		hdc = GetDC(hwnd);

		if (wParam == VK_LEFT)
		{
			
		}
		if (wParam == VK_RIGHT)
		{
			
		}
		if (wParam == VK_UP)
		{
			
		}
		if (wParam == VK_DOWN)
		{
			printf("Pressed Q\n");

		}
		if (wParam == 'q')//삼각형의 색 랜덤 변경, 중앙에 도형 넣기
		{
			printf("Pressed Q\n");
			PostQuitMessage(0);
		}

		ReleaseDC(hwnd, hdc);

		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		int a, b, c; 

		a = rand() % 256;
		b = rand() % 256;
		c = rand() % 256;

		hBrush = CreateSolidBrush(RGB(100, 100, 100));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

		//기본 도형 그리기
		Rectangle(hdc, 300, 220, 460, 340);

		hBrush = CreateSolidBrush(RGB(0, 0, 200));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Polygon(hdc, Tripoint, 3);

		hBrush = CreateSolidBrush(RGB(200, 0, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Polygon(hdc, Fivpoint, 5);

		hBrush = CreateSolidBrush(RGB(0, 200, 0));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Polygon(hdc, Sandpoint, 4);

		hBrush = CreateSolidBrush(RGB(0, 150, 150));
		oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
		Pie(hdc, 300, 400, 460, 520,    380, 400, 460, 460);






		SelectObject(hdc, oldBrush);

		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}