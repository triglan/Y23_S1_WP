#include <windows.h>
#include <tchar.h>
#include<stdio.h>

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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 400, 200, 1280, 800, NULL, (HMENU)NULL, hInstance, NULL);
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
	static SIZE size;
	PAINTSTRUCT ps;
	HDC hdc;
	static TCHAR str[100];
	static int count;

	static int x;
	static int y[10];
	static int n[3];
	static int m[3];


	static int yPos = 0;


	//Test
	static TCHAR test[100];

	switch (uMsg)
	{
	case WM_CREATE:
		CreateCaret(hwnd, NULL, 5, 15); //--- 캐럿 만들기
		ShowCaret(hwnd);				//--빈 화면에 캐럿 표시
		count = 0;
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);
		if (wParam == VK_BACK) //--- 백스페이스를 입력하면
			count--; //--- 한 칸 삭제
		else if (wParam == VK_RETURN) //--- 엔터키를 입력하면: 문자열을 다음줄에 출력
		{
			count = 0; //--- 인덱스 변경
			yPos = yPos + 20; //--- y 위치 변경: 한 줄 아래에 출력
		}
		else
			str[count++] = wParam; //--- 그 외에는 문자를 문자열 맨 뒤에 붙인다.
		str[count] = '\0';
		TextOut(hdc, 0, yPos, str, lstrlen(str));
		ReleaseDC(hwnd, hdc);

		InvalidateRect(hwnd, NULL, TRUE); //--- WM_PAINT 메시지 발생
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetTextExtentPoint32(hdc, str, lstrlen(str), &size); //--- 문자열 길이 알아내기
		TextOut(hdc, 0, yPos, str, lstrlen(str));
		SetCaretPos(size.cx, yPos); //--- 캐럿 위치하기
		EndPaint
		(hwnd, &ps);
		break;
	case WM_DESTROY:
		HideCaret(hwnd); //--- 캐럿 숨기기
		DestroyCaret(); //--- 캐럿 삭제하기
		PostQuitMessage(0);
		break;


	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}