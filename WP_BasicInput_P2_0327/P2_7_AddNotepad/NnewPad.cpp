#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#define MAXWORD 10
#define MAXLINE 10

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

	static TCHAR str[MAXLINE][100];

	static int linecount = 0;
	static int wordcount;

	static int cword = 0;
	static int yPos = 0;

	static bool caps = false;

	switch (uMsg)
	{
	case WM_CREATE:
		CreateCaret(hwnd, NULL, 5, 15); //--- 캐럿 만들기
		ShowCaret(hwnd);				//--빈 화면에 캐럿 표시
		SetCaretBlinkTime(300);
		wordcount = 0;
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);


		if (linecount % 10 == 0 && linecount >= 10)//10이면
		{//linecount가 10이 되면 엔터*2에서 linecount++를 빼고 커서 위치에서 덮어쓰기
			yPos = 0;
			
		}

		if (wParam == VK_BACK) //--- 백스페이스를 입력하면
		{
			for (int i = 0; i < length; i++)
			{

			}
			str[yPos / 20][cword - 1] = ' ';
			wordcount--;
			cword--;
		}
		else if (wordcount >= MAXWORD)// 글자 초과
		{
			wordcount = 0; //--- 인덱스 변경
			cword = 0;
			linecount++;
			yPos = yPos + 20;
			str[linecount][wordcount++] = wParam;
		}
		else if (wParam == VK_RETURN) //--- 엔터키를 입력하면: 문자열을 다음줄에 출력
		{
			wordcount = 0; //--- 인덱스 변경
			cword = 0;
			linecount++;
			yPos = yPos + 20;
		}
		else if (wParam == VK_ESCAPE)
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < MAXWORD; j++)
				{
					str[i][j] = '\0';
				}
			}
			linecount = 0;
			wordcount = 0;
			cword = 0;
			yPos = 0;
		}
		else if (wParam == VK_TAB)
		{
			for (int i = 0; i < 4; i++)
			{
				if (wordcount >= MAXWORD - 1)
				{//인덱스 변경
					wordcount = 0; //--- 인덱스 변경
					cword = 0;
					linecount++;
					yPos = yPos + 20;
					break;
				}
				str[yPos / 20][cword++] = ' ';
				wordcount++;
			}
		}
		else
		{
			printf("cword : %d // wordcount : %d\nyPos/20 : %d // linecount : %d\n\n", cword, wordcount, yPos / 20, linecount);//CMD

			str[yPos/20][cword++] = wParam; //--- 그 외에는 문자를 캐럿 뒤에 붙인다.
			if(cword - 1 == wordcount)//문장 마지막에서만 문장길이가 늘어남
				wordcount++;
		}
		//str[linecount][wordcount] = '\0';
		ReleaseDC(hwnd, hdc);
		InvalidateRect(hwnd, NULL, TRUE); //--- WM_PAINT 메시지 발생

		break;

	case WM_KEYDOWN:
		hdc = GetDC(hwnd);

		if (wParam == VK_LEFT)
		{
			if (cword > 0)
			{
				cword--;
			}
		}
		else if (wParam == VK_RIGHT)
		{
			if (cword < wordcount)
			{
				cword++;
			}
		}
		else if (wParam == VK_UP)
		{
			if (yPos > 0)
			{
				yPos = yPos - 20;
			}
		}
		else if (wParam == VK_DOWN)
		{
			if (yPos < linecount * 20)
			{
				yPos = yPos + 20;
			}
		}
		else if (wParam == VK_F1)
		{
			caps = true;
		}

		ReleaseDC(hwnd, hdc);
		InvalidateRect(hwnd, NULL, TRUE); //--- WM_PAINT 메시지 발생

		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetTextExtentPoint32(hdc, str[linecount % 10], cword, &size); //--- 문자열 길이 알아내기
		
		//if (linecount >= 10)
		//{
		//	for (int i = 0; i < 10; i++)
		//	{
		//		TextOut(hdc, 0, i * 20, str[i], lstrlen(str[i]));//출력
		//	}
		//	for (int i = linecount % 10 * 10; i <= linecount; i++)
		//	{
		//		TextOut(hdc, 0, i * 20, str[i], lstrlen(str[i]));//출력
		//	}
		//	SetCaretPos(size.cx, yPos % 200); //--- 캐럿 위치하기
		//	EndPaint(hwnd, &ps);
		//	break;
		//}

		for (int i = 0; i <= linecount; i++)
		{
			TextOut(hdc, 0, i * 20, str[i], lstrlen(str[i]));//출력
		}
		//TextOut(hdc, 0, yPos, str[linecount], lstrlen(str[linecount]));//출력


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