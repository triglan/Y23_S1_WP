#include <windows.h>
#include <tchar.h>
#include <stdio.h>

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

	TCHAR cal[100];
	static int count;

	static int x;
	static int y;
	static int n;
	static int m;

	static bool bCal = false;
	static bool NotValid = false;

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
		NotValid = true;

		if (wParam == VK_BACK) //--- 백스페이스를 입력하면
			count--; //--- 한 칸 삭제
		else if (wParam == VK_RETURN) //--- 엔터키를 입력하면: 문자열을 다음줄에 출력
		{
			count = 0; //--- 인덱스 변경

			int i, j, k, l;
			x = 0;
			y = 0;
			m = 0;
			n = 0;
			for (i = 0; i < lstrlen(str); i++)
			{
				if (str[i] == ' ')
					break;
				x = x * 10 + str[i] - 48;
			}
			for (j = i + 1; j < lstrlen(str); j++)
			{
				if (str[j] == ' ')
					break;
				y = y * 10 + str[j] - 48;
			}
			for (k = j + 1; k < lstrlen(str); k++)
			{
				if (str[k] == ' ')
					break;
				n = n * 10 + str[k] - 48;
			}
			for (l = k + 1; l < lstrlen(str); l++)
			{
				if (str[l] == ' ')
					break;
				m = m * 10 + str[l] - 48;
			}
			bCal = true;
		}
		else if (wParam == 'q')
		{
			PostQuitMessage(0);
			break;

		}
		else
			str[count++] = wParam; //--- 그 외에는 문자를 문자열 맨 뒤에 붙인다.
		str[count] = '\0';

		//TextOut(hdc, 0, yPos, str, lstrlen(str));
		//TextOut(hdc, x, y, str, lstrlen(str));
		ReleaseDC(hwnd, hdc);

		InvalidateRect(hwnd, NULL, TRUE); //--- WM_PAINT 메시지 발생
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetTextExtentPoint32(hdc, str, lstrlen(str), &size); //--- 문자열 길이 알아내기

		TextOut(hdc, 0, 0, str, lstrlen(str));//출력

		SetCaretPos(size.cx, 0); //--- 캐럿 위치하기


		if (bCal)
		{

			if (n > 20 || n <= 0 || m <= 0 || m > 30)
			{
				TextOut(hdc, 0, 30, L"잘못된 값.", 6);//출력
				break;
			}

			for (int i = 0; i < m; i++)
			{
				wsprintf(cal, L"%d * %d = %d", n, i + 1, n * (i + 1));
				TextOut(hdc, x, y + 20 * i, cal, lstrlen(cal));//출력
			}
		}
		//SetCaretPos(x + size.cx, y); //--- x,y 위치에 캐럿 위치하기
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