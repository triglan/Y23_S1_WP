#include <windows.h>
#include <tchar.h>
#include <random>

std::random_device rd;
std::uniform_int_distribution<> uid(0, 255);

#define MAXSHAPE 10

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 1";

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

struct Shapes {
	char order;
	int x1;
	int	y1;
	int	x2;
	int	y2;
	
	int a;
	int b;
	int c;
	
	int	thick;
	int ra;
	int rb;
	int rc;
};
static Shapes sp[MAXSHAPE];
//Temp 실험

	sp[0].a = 255;
	sp[0].b = 0;
	sp[0].c = 0;

	sp[0].ra = 0;
	sp[0].rb = 250;
	sp[0].rc = 0;

	sp[0].x1 = 20;
	sp[0].y1 = 20;
	sp[0].x2 = 100;
	sp[0].y2 = 100;
	sp[0].thick = 10;

	sp[0].order = '4';


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
	
	HBRUSH hBrush[MAXSHAPE];
	HBRUSH rhBrush[MAXSHAPE];
	HPEN hPen[MAXSHAPE];

	//RECT rect[MAXSHAPE];
	//rect[i] = { sp[i].x1, sp[i].y1, sp[i].x2, sp[i].y2 };

	static SIZE size;
	
	static int shapeCount = 1;

	
	
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		

		

		for (int i = 0; i < shapeCount; i++)
		{
			POINT TriPoint[10] = { {(sp[i].x1 + sp[i].x2) / 2, sp[i].y1}, { sp[i].x1, sp[i].y2 }, { sp[i].x2, sp[i].y2 } };
			

			switch (sp[i].order)
			{
			case '1':
				hPen[i] = CreatePen(PS_DOT, sp[i].thick, RGB(sp[i].a, sp[i].b, sp[i].c));
				SelectObject(hdc, hPen[i]);

				MoveToEx(hdc, sp[i].x1, sp[i].y1, NULL);
				LineTo(hdc, sp[i].x2, sp[i].y2);
				break;
			case '2':
				
				//사각형
				hPen[i] = CreatePen(PS_DOT, sp[i].thick, RGB(sp[i].ra, sp[i].rb, sp[i].rc));
				hBrush[i] = CreateSolidBrush(RGB(sp[i].a, sp[i].b, sp[i].c));

				SelectObject(hdc, hPen[i]);
				SelectObject(hdc, hBrush[i]);

				Rectangle(hdc, sp[i].x1, sp[i].y1, sp[i].x2, sp[i].y2);
				break;
			case '3':
				hPen[i] = CreatePen(PS_DOT, sp[i].thick, RGB(sp[i].ra, sp[i].rb, sp[i].rc));
				hBrush[i] = CreateSolidBrush(RGB(sp[i].a, sp[i].b, sp[i].c));

				SelectObject(hdc, hPen[i]);
				SelectObject(hdc, hBrush[i]);

				Polygon(hdc, TriPoint, 3);
			case '4':
				hPen[i] = CreatePen(PS_DOT, sp[i].thick, RGB(sp[i].ra, sp[i].rb, sp[i].rc));
				hBrush[i] = CreateSolidBrush(RGB(sp[i].a, sp[i].b, sp[i].c));

				SelectObject(hdc, hPen[i]);
				SelectObject(hdc, hBrush[i]);

				Ellipse(hdc, sp[i].x1, sp[i].y1, sp[i].x2, sp[i].y2);

			default:
				break;
			}
		}

		ReleaseDC(hwnd, hdc);
		EndPaint(hwnd, &ps);
		break;
	case WM_KEYDOWN:

	case WM_CHAR:
		hdc = GetDC(hwnd);
		
		printf("%d %d %d\n", sp[shapeCount - 1].a, sp[shapeCount - 1].b, sp[shapeCount - 1].c);

		if (wParam == 'c' || wParam == 'C')//내부 색 바꾸기
			sp[shapeCount - 1].a = uid(rd), sp[shapeCount - 1].b = uid(rd), sp[shapeCount - 1].c = uid(rd);
		if(wParam == 'b'||wParam == 'B')//테두리 바꾸기
			sp[shapeCount - 1].a = uid(rd), sp[shapeCount - 1].rb = uid(rd), sp[shapeCount - 1].rc = uid(rd);

		ReleaseDC(hwnd, hdc);
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}