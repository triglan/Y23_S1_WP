#include <windows.h> //--- ������ ��� ����
#include <tchar.h>
#include<stdio.h>
#include"resource.h"
#include <atlimage.h>

//���� ��Ʈ�� ó�� 
#pragma comment(lib, "msimg32.lib")
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#define WINDOWSIZE 800

typedef struct {
}pictures;
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

static HBITMAP hBitmap, hBitmap2, oldmap;


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
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 500, 100, WINDOWSIZE + 16, WINDOWSIZE + 35, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

//CImage�� ����� �̹��� ���
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{//5���� ���콺 �̵�x
	PAINTSTRUCT ps;
	HDC hdc, mdc;
	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	static CImage img, imgSprite;
	static int xPos = 0, yPos = 0;
	static RECT rt;//
	static DWORD scopy = SRCCOPY;//���������� �ƴ���

	static int timer1 = 0;
	static int w, h;
	switch (uMsg) {
	case WM_CREATE:
	{
		img.LoadFromResource(g_hInst, IDB_BITMAP2); //--- background
		//imgSprite.LoadFromResource(g_hInst, IDB_BITMAP3); //--- sprite image
		imgSprite.Load(L"Idle.bmp");
		GetClientRect(hwnd, &rt);

		SetTimer(hwnd, 1, 100, NULL);
	}
	break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			timer1++;
			timer1 = timer1 % 4;
			printf("timer : %d %d\n", timer1 * 52, (timer1 + 1) * 52);
			xPos++;
			break;
		}
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		mdc = CreateCompatibleDC(hdc);

		(HBITMAP)SelectObject(mdc, hBitmap);

		w = img.GetWidth();
		h = img.GetHeight();

		img.Draw(mdc, 0, 0, rt.right, rt.bottom, 0, 0, w, h); //--- �޸� DC�� ��� �׸���
		//imgSprite.Draw(mdc, xPos, yPos, 52, 60,		52 * timer1, 0, 52, 50); //--- �޸� DC�� ��������Ʈ �׸���
		imgSprite.Draw(mdc, 0, 0, 100, 100, 0, 0, 30, 30); //--- �޸� DC�� ��������Ʈ �׸���

		BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY); //--- �޸� DC�� �׸��� ȭ�� DC�� �����ϱ�

		DeleteObject(hBitmap);
		DeleteDC(mdc);

		InvalidateRect(hwnd, NULL, false);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(hBitmap);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam); //--- ���� �� �޽��� ���� ������ �޽����� OS��
}

