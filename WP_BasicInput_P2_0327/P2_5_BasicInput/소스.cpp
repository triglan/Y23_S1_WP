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
		CreateCaret(hwnd, NULL, 5, 15); //--- ĳ�� �����
		ShowCaret(hwnd);				//--�� ȭ�鿡 ĳ�� ǥ��
		count = 0;
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);
		NotValid = true;

		if (wParam == VK_BACK) //--- �齺���̽��� �Է��ϸ�
			count--; //--- �� ĭ ����
		else if (wParam == VK_RETURN) //--- ����Ű�� �Է��ϸ�: ���ڿ��� �����ٿ� ���
		{
			count = 0; //--- �ε��� ����

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
			str[count++] = wParam; //--- �� �ܿ��� ���ڸ� ���ڿ� �� �ڿ� ���δ�.
		str[count] = '\0';

		//TextOut(hdc, 0, yPos, str, lstrlen(str));
		//TextOut(hdc, x, y, str, lstrlen(str));
		ReleaseDC(hwnd, hdc);

		InvalidateRect(hwnd, NULL, TRUE); //--- WM_PAINT �޽��� �߻�
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetTextExtentPoint32(hdc, str, lstrlen(str), &size); //--- ���ڿ� ���� �˾Ƴ���

		TextOut(hdc, 0, 0, str, lstrlen(str));//���

		SetCaretPos(size.cx, 0); //--- ĳ�� ��ġ�ϱ�


		if (bCal)
		{

			if (n > 20 || n <= 0 || m <= 0 || m > 30)
			{
				TextOut(hdc, 0, 30, L"�߸��� ��.", 6);//���
				break;
			}

			for (int i = 0; i < m; i++)
			{
				wsprintf(cal, L"%d * %d = %d", n, i + 1, n * (i + 1));
				TextOut(hdc, x, y + 20 * i, cal, lstrlen(cal));//���
			}
		}
		//SetCaretPos(x + size.cx, y); //--- x,y ��ġ�� ĳ�� ��ġ�ϱ�
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		HideCaret(hwnd); //--- ĳ�� �����
		DestroyCaret(); //--- ĳ�� �����ϱ�
		PostQuitMessage(0);
		break;


	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}