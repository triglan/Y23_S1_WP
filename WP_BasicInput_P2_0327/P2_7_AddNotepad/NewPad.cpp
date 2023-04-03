#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#define MAXWORD 10
#define COUNTNUM 10

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

	static TCHAR str[10][MAXWORD + 1];	//기본 저장 장소
	//static TCHAR caretstr[10][100];//화살표 이동을 위한 

	//총 줄, 워드 카운트
	static int linecount = 0;
	static int wordcount[COUNTNUM] = { 0 };
	
	//캐럿 위치
	static int lineNum = 0;
	static int wordNum = 0;

	//캐럿 좌표
	static int xPos = 0;//캐럿 xPos
	static int yPos = 0;//캐럿 yPos, 줄 위치는 yPos/20


	switch (uMsg)
	{
	case WM_CREATE:
		CreateCaret(hwnd, NULL, 5, 15); //--- 캐럿 만들기
		ShowCaret(hwnd);				//--빈 화면에 캐럿 표시
		SetCaretBlinkTime(300);
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);

		if (wParam == VK_BACK)
		{//캐럿 위치에서 앞 글자 하나 지우기
			//lineNum, wordNum이 0이면 break
			//wordNum이 0이면 윗줄로
			if (wordNum <= 0)
			{

			}
			str[lineNum][wordNum--] = ' ';
			wordcount[lineNum]--;
			yPos = yPos - 20;
		}

		ReleaseDC(hwnd, hdc);
		InvalidateRect(hwnd, NULL, TRUE); //--- WM_PAINT 메시지 발생
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetTextExtentPoint32(hdc, str[lineNum], xPos, &size); //--- 캐럿 위치 알아내기

		SetCaretPos(size.cx, yPos); //--- 캐럿 위치하기
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		HideCaret(hwnd); //--- 캐럿 숨기기
		DestroyCaret(); //--- 캐럿 삭제하기
		PostQuitMessage(0);
		break;


	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}