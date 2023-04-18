
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int startX, startY, oldX, oldY;
	static BOOL Drag;
	int endX, endY;
	switch (iMsg)
	{
	case WM_CREATE:
		startX = oldX = 0; //--- 시작 좌표
		startY = oldY = 0;
		Drag = FALSE;
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		MoveToEx(hdc, startX, startY, NULL); //--- 이동하고 선으로 연결
		LineTo(hdc, oldX, oldY);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_LBUTTONDOWN: //--- 버튼을 누르면 드래그 동작 시작
		Drag = TRUE;
		break;
	case WM_LBUTTONUP: //--- 버튼을 놓으면 드래그 종료
		Drag = FALSE;
		break;
	case WM_MOUSEMOVE:
		hdc = GetDC(hwnd);
		if (Drag)
		{ //--- 흰 바탕
			SetROP2(hdc, R2_XORPEN); //--- 펜의 XOR 연산
			SelectObject(hdc, (HPEN)GetStockObject(WHITE_PEN)); //--- 흰 펜
			//--- 흰 바탕 XOR 흰 펜 = 검은색
			//--- 검정 바탕 XOR 흰 펜 = 흰 색
			endX = LOWORD(lParam);
			endY = HIWORD(lParam);
			MoveToEx(hdc, startX, startY, NULL);
			LineTo(hdc, oldX, oldY); //--- 지우기 : 검정 바탕 XOR 흰 펜 = 흰 선
			MoveToEx(hdc, startX, startY, NULL);
			LineTo(hdc, endX, endY); //--- 그리기 : 흰 바탕 XOR 흰 펜 = 검은 선  화면의 결과 선
			oldX = endX; oldY = endY; //--- 현 지점을 이전 지점으로 설정
		}
		ReleaseDC(hwnd, hdc);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
