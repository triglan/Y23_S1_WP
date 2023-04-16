
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam
)
{
	PAINTSTRUCT ps;
	static int Timer1Count = 0, Timer2Count = 0;
	static int wonSpeed = 200;
	HDC hdc;
	switch (iMsg) // 메시지 번호 
	{
		case WM_CREATE:
			SetTimer(hwnd, 1, wonSpeed, NULL); //---1번 아이디를 가진 타이머: 0.06초 간격
			SetTimer(hwnd, 2, 100, NULL); //---2번 아이디를 가진 타이머 : 0.1초 간격
			break;
			case WM_TIMER:
					switch (wParam) {
					case 1:
						Timer1Count++;
						break;
					case 2:
						Timer2Count++;
						break;
					}
					InvalidateRect(hwnd, NULL, TRUE);
					break;
			case WM_PAINT:
				hdc = BeginPaint(hwnd, &ps);
				if (Timer1Count % 2 == 0)
					TextOut(hdc, Timer1Count * 10, 0, L"Timer1 Count", 12);
				//if (Timer2Count % 2 == 0)
				//	TextOut(hdc, Timer2Count * 10, 100, L"Timer2 Count", 12);
				EndPaint(hwnd, &ps);
				break;
}
return DefWindowProc
(hwnd, iMsg, wParam, lParam);
}
