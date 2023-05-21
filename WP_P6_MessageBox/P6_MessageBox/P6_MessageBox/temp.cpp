#include <windows.h> //--- 윈도우 헤더 파일
#include <tchar.h>
#include<stdio.h>
#include "resource.h"
#include<cmath>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlalog_Proc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);//
//HINSTANCE g_hInst;//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
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
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
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
int curvenum;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc, mdc;
	HBITMAP hBitmap;
	HBRUSH hbr, oldbr;
	HPEN hPen, oldPen;
	double PI = 3.14159;
	RECT rect;
	int clientWidth = 0;
	int clientHeight = 0;
	//--- 메시지 처리하기
	switch (uMsg) {
	case WM_CREATE:
		curvenum = 0;
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//
		GetClientRect(hWnd, &rect);
		clientWidth = rect.right - rect.left;
		clientHeight = rect.bottom - rect.top;
		//더블버퍼링
		mdc = CreateCompatibleDC(hdc); //--- 메모리 DC 만들기
		hBitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom); //--- 메모리 DC와 연결할 비트맵 만들기
		SelectObject(mdc, (HBITMAP)hBitmap);
		//흰색 배경
		hbr = CreateSolidBrush(RGB(255, 255, 255));
		oldbr = (HBRUSH)SelectObject(mdc, hbr);
		FillRect(mdc, &rect, hbr);
		SelectObject(mdc, oldbr);
		DeleteObject(hbr);
		//+
		hPen = CreatePen(PS_DOT, 3, RGB(135, 206, 250)); // GDI: 펜 만들기
		oldPen = (HPEN)SelectObject(mdc, hPen); // 새로운 펜 선택하기
		MoveToEx(mdc, clientWidth / 2, 0, NULL);
		LineTo(mdc, clientWidth / 2, clientHeight);
		MoveToEx(mdc, 0, clientHeight / 2, NULL);
		LineTo(mdc, clientWidth, clientHeight / 2);
		SelectObject(mdc, oldPen); // 이전의 펜으로 돌아감
		DeleteObject(hPen);

		// sin 함수 그리기
		if (curvenum == 0) {
			MoveToEx(mdc, 0, clientHeight / 2, NULL);
			for (int x = 0; x <= clientWidth; x++)
			{

				double radian = x * 3.14159265 / 180.0;
				int y = clientHeight / 2 + (200 * sin(radian));
				LineTo(mdc, x, y);
			}
		}
		else if (curvenum == 1) {

		}
		else if (curvenum == 2) {

		}
		else if (curvenum == 3) {

		}

		BitBlt(hdc, 0, 0, rect.right, rect.bottom, mdc, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)&Dlalog_Proc);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam); //--- 위의 세 메시지 외의 나머지 메시지는 OS로
}
BOOL CALLBACK Dlalog_Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hbutton;
	switch (iMsg) {
	case WM_INITDIALOG:
		//hbutton = GetDlgItem(hDlg, ID_TEST); //--- ID_TEST 라는 id의 버튼 핸들 가져오기
		//EnableWindow(hbutton, FALSE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDC_RADIO_sin:
			curvenum = 0;
			break;
		case IDC_RADIO_spr:
			curvenum = 1;
			break;
		case IDC_RADIO_zig:
			curvenum = 2;
			break;
		case IDC_RADIO_pie:
			curvenum = 3;
			break;
		case IDOK: //--- 버튼
			MessageBox(hDlg, L"test", L"test, ", MB_OK);
			break;
		case IDCANCEL: //--- 버튼
			PostQuitMessage(0);
			//EndDialog(hDlg, 0);
			break;
		}
		InvalidateRect(GetParent(hDlg), NULL, FALSE);
		break;
	case WM_CLOSE:
		EndDialog(hDlg, 0);
		break;
	}
	return 0;
}