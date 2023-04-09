
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
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

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	HBRUSH hBrush, oldBrush;
	HPEN hPen, oldPen;

	POINT Tripoint[10] = { {80, 340}, {160, 230}, {240, 340} };
	POINT STripoint[10] = { {300, 335}, {380, 225}, {460, 335} };
	POINT QTripoint[10] = { {330, 305}, {380, 250}, {430, 305} };

	POINT Fivpoint[10] = { {620, 220}, {700, 280}, {660, 340}, {580, 340}, {540, 280} };
	POINT SFivpoint[10] = { {380, 220}, {460, 280}, {420, 340}, {340, 340}, {300, 280} };
	POINT QFivpoint[10] = { {380, 240}, {430, 280}, {405, 320}, {355, 320}, {330, 280} };

	POINT Sandpoint[10] = { {320, 60}, {440, 170}, {320, 170}, {440, 60} };
	POINT SSandpoint[10] = { {320, 230}, {440, 330}, {320, 330}, {440, 230} };
	POINT QSandpoint[10] = { {360, 250}, {400, 300}, {360, 300}, {400, 250} };

	static bool press = false;

	static bool pressT = false;
	static bool pressS = false;
	static bool pressP = false;
	static bool pressE = false;

	static bool left = false;
	static bool right = false;
	static bool up = false;
	static bool down = false;

	static int choice;
	static bool Onetime = true;
	if (Onetime)
	{
		srand(time(NULL));
		choice = rand() % 4;
		Onetime = false;
	}
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		int a, b, c;
		//기본 도형
		{
			hBrush = CreateSolidBrush(RGB(100, 100, 100));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

			//기본 도형 그리기
			Rectangle(hdc, 280, 200, 480, 360);

			hBrush = CreateSolidBrush(RGB(0, 0, 200));
			SelectObject(hdc, hBrush);
			Polygon(hdc, Tripoint, 3);

			hBrush = CreateSolidBrush(RGB(200, 0, 0));
			SelectObject(hdc, hBrush);
			Polygon(hdc, Fivpoint, 5);

			hBrush = CreateSolidBrush(RGB(0, 200, 0));
			SelectObject(hdc, hBrush);
			Polygon(hdc, Sandpoint, 4);

			hBrush = CreateSolidBrush(RGB(0, 150, 150));
			SelectObject(hdc, hBrush);
			Pie(hdc, 320, 400, 440, 520, 380, 400, 440, 460);

		}

		if (press)
		{
			if (pressT == true)
			{
				a = rand() % 256, b = rand() % 256, c = rand() % 256;
				hBrush = CreateSolidBrush(RGB(a, b, c));
				SelectObject(hdc, hBrush);
				Polygon(hdc, Tripoint, 3);
				Polygon(hdc, STripoint, 3);
			}
			else if (pressS == true)
			{
				a = rand() % 256, b = rand() % 256, c = rand() % 256;
				hBrush = CreateSolidBrush(RGB(a, b, c));
				SelectObject(hdc, hBrush);
				Polygon(hdc, Sandpoint, 4);
				Polygon(hdc, SSandpoint, 4);
			}
			else if (pressP == true)
			{
				a = rand() % 256, b = rand() % 256, c = rand() % 256;
				hBrush = CreateSolidBrush(RGB(a, b, c));
				SelectObject(hdc, hBrush);
				Polygon(hdc, Fivpoint, 5);
				Polygon(hdc, SFivpoint, 5);
			}
			else if (pressE == true)
			{
				a = rand() % 256, b = rand() % 256, c = rand() % 256;
				hBrush = CreateSolidBrush(RGB(a, b, c));
				SelectObject(hdc, hBrush);
				Pie(hdc, 320, 400, 440, 520, 380, 400, 440, 460);

				Pie(hdc, 320, 220, 440, 340, 380, 220, 440, 280);
			}
			else if (left == true)
			{
				hBrush = CreateSolidBrush(RGB(0, 0, 200));
				SelectObject(hdc, hBrush);
				Polygon(hdc, Tripoint, 3);
				Polygon(hdc, QTripoint, 3);
			}
			else if (up == true)
			{
				hBrush = CreateSolidBrush(RGB(0, 200, 0));
				SelectObject(hdc, hBrush);
				Polygon(hdc, Sandpoint, 4);
				Polygon(hdc, QSandpoint, 4);
			}
			else if (right == true)
			{
				hBrush = CreateSolidBrush(RGB(200, 0, 0));
				SelectObject(hdc, hBrush);
				Polygon(hdc, Fivpoint, 5);
				Polygon(hdc, QFivpoint, 5);
			}
			else if (down == true)
			{
				hBrush = CreateSolidBrush(RGB(0, 150, 150));
				SelectObject(hdc, hBrush);
				Pie(hdc, 320, 400, 440, 520, 380, 400, 440, 460);
				Pie(hdc, 340, 240, 420, 320, 380, 240, 420, 280);
			}
		}
		else
		{
			switch (choice)
			{
			case 0:
				hBrush = CreateSolidBrush(RGB(0, 0, 200));
				SelectObject(hdc, hBrush);
				Polygon(hdc, STripoint, 3);
				break;
			case 1:
				hBrush = CreateSolidBrush(RGB(200, 0, 0));
				SelectObject(hdc, hBrush);
				Polygon(hdc, SFivpoint, 5);
				break;
			case 2:
				hBrush = CreateSolidBrush(RGB(0, 200, 0));
				SelectObject(hdc, hBrush);
				Polygon(hdc, SSandpoint, 4);
				break;
			case 3:
				hBrush = CreateSolidBrush(RGB(0, 150, 150));
				SelectObject(hdc, hBrush);
				Pie(hdc, 320, 220, 440, 340, 380, 220, 440, 280);
				break;

			default:
				break;
			}
		}




		SelectObject(hdc, oldBrush);

		EndPaint(hwnd, &ps);
		break;

	case WM_CHAR:
	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		printf("wParam : %c\n", wParam);

		if (wParam == 't' || wParam == 'T')//삼각형의 색 랜덤 변경, 중앙에 도형 넣기
		{
			pressT = true;
			press = true;
		}
		else if (wParam == 's' || wParam == 'S')
		{
			pressS = true;
			press = true;
		}

		else if (wParam == 'p' || wParam == 'P')
		{
			pressP = true;
			press = true;
		}
		else if (wParam == 'e' || wParam == 'E')
		{
			pressE = true;
			press = true;
		}
		else if (wParam == VK_LEFT)
		{
			left = true;
			press = true;
		}
		else if (wParam == VK_RIGHT)
		{
			right = true;
			press = true;
		}
		else if (wParam == VK_UP)
		{
			up = true;
			press = true;
		}
		else if (wParam == VK_DOWN)
		{
			down = true;
			press = true;
		}
		else if (wParam == 'q')
		{
			PostQuitMessage(0);

		}
		
		
		ReleaseDC(hwnd, hdc);
		InvalidateRect(hwnd, NULL, TRUE);
		break;


	case WM_KEYUP:
		hdc = GetDC(hwnd);

		press = false;

		if (wParam == 't' || wParam == 'T')//삼각형의 색 랜덤 변경, 중앙에 도형 넣기
			pressT = false;
		else if (wParam == 's' || wParam == 'S')
			pressS = false;
		else if (wParam == 'p' || wParam == 'P')
			pressP = false;
		else if (wParam == 'e' || wParam == 'E')
			pressE = false;
		else if (wParam == VK_LEFT)
			left = false;
		else if (wParam == VK_RIGHT)
			right = false;
		else if (wParam == VK_UP)
			up = false;
		else if (wParam == VK_DOWN)
			down = false;

		ReleaseDC(hwnd, hdc);
		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}