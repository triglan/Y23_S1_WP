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
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass; // lpszClass;
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

LRESULT CALLBACK WndProc
(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam
)
{
	PAINTSTRUCT ps;
	HDC hdc;
	HPEN hPen, oldPen
		;
	static int draw = 1;
	switch (iMessage) {
		case WM_PAINT:
				hdc = BeginPaint(hwnd, &ps);
				if
					(draw) {
					hPen = CreatePen(PS_DOT, 1, RGB(255, 0, 0));
					oldPen = (HPEN)SelectObject
						(hdc, hPen); 
						Ellipse(hdc, 20, 20, 300, 300); // 선택한 펜으로 도형 그리기
					SelectObject(hdc, oldPen); 
					DeleteObject(hPen);
				}
				EndPaint
				(hwnd, &ps);// DC 해제하기
				break;
				case WM_LBUTTONDBLCLK
					:
						draw++;
						draw %= 2;
						InvalidateRect
						(hwnd, NULL, TRUE);
						break;
						case WM_DESTROY
							:
								PostQuitMessage(0);
								break;
	}
	return (DefWindowProc
	(hwnd, iMessage, wParam, lParam));
}
