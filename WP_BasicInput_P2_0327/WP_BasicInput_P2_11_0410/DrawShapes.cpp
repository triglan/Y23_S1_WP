#include <windows.h>
#include <tchar.h>
#include <random>

std::random_device rd;
std::uniform_int_distribution<> uid(0, 255);

#define MAXSHAPE 10
#define WINDOWUP 600
#define WINDOWSIDE 800
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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 600, 200, WINDOWSIDE, WINDOWUP, NULL, (HMENU)NULL, hInstance, NULL);
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
	
	static int shapeCount = 0;
	static Shapes sp[MAXSHAPE];

	RECT rect[MAXSHAPE];

	static TCHAR str[100];
	static TCHAR tempstr[100][100];
	TCHAR lpOut[100];
	wsprintf(lpOut, L"ERROR : Incorrect Spell");


	static int cword = 0;
	static int yPos = 0;
	static int select = 0;
	
	static int DrawAll = -1;
	static bool temp = true;
	static bool error = false;

	//그리기 x 0~760, y 0~520
	//1, 2번 -> b, c로 바뀜
	
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);


		//모두 그릴 건지 마지막 거만 그릴 건지 선택
		if (DrawAll == 1)
		{
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
					break;
				case '4':
					hBrush[i] = CreateSolidBrush(RGB(sp[i].a, sp[i].b, sp[i].c));
					hPen[i] = CreatePen(PS_DOT, sp[i].thick, RGB(sp[i].ra, sp[i].rb, sp[i].rc));

					SelectObject(hdc, hBrush[i]);
					SelectObject(hdc, hPen[i]);

					Ellipse(hdc, sp[i].x1, sp[i].y1, sp[i].x2, sp[i].y2);
					break;
				default:
					break;
				}
			}
		}
		else
		{
			POINT TriPoint[10] = { {(sp[select].x1 + sp[select].x2) / 2, sp[select].y1}, { sp[select].x1, sp[select].y2 }, { sp[select].x2, sp[select].y2 } };


			switch (sp[select].order)
			{
			case '1':
				hPen[select] = CreatePen(PS_DOT, sp[select].thick, RGB(sp[select].a, sp[select].b, sp[select].c));
				SelectObject(hdc, hPen[select]);

				MoveToEx(hdc, sp[select].x1, sp[select].y1, NULL);
				LineTo(hdc, sp[select].x2, sp[select].y2);
				break;
			case '2':

				//사각형
				hPen[select] = CreatePen(PS_DOT, sp[select].thick, RGB(sp[select].ra, sp[select].rb, sp[select].rc));
				hBrush[select] = CreateSolidBrush(RGB(sp[select].a, sp[select].b, sp[select].c));

				SelectObject(hdc, hPen[select]);
				SelectObject(hdc, hBrush[select]);
				Rectangle(hdc, sp[select].x1, sp[select].y1, sp[select].x2, sp[select].y2);
				break;
			case '3':
				hPen[select] = CreatePen(PS_DOT, sp[select].thick, RGB(sp[select].ra, sp[select].rb, sp[select].rc));
				hBrush[select] = CreateSolidBrush(RGB(sp[select].a, sp[select].b, sp[select].c));

				SelectObject(hdc, hPen[select]);
				SelectObject(hdc, hBrush[select]);

				Polygon(hdc, TriPoint, 3);
				break;
			case '4':
				hBrush[select] = CreateSolidBrush(RGB(sp[select].a, sp[select].b, sp[select].c));
				hPen[select] = CreatePen(PS_DOT, sp[select].thick, RGB(sp[select].ra, sp[select].rb, sp[select].rc));

				SelectObject(hdc, hBrush[select]);
				SelectObject(hdc, hPen[select]);

				Ellipse(hdc, sp[select].x1, sp[select].y1, sp[select].x2, sp[select].y2);
				break;
			default:
				break;
			}
		}
		TextOut(hdc, 0, 540, str, lstrlen(str));

		if (error)
			TextOut(hdc, 300, 250, lpOut, lstrlen(lpOut));
		ReleaseDC(hwnd, hdc);
		EndPaint(hwnd, &ps);
		break;
	case WM_KEYDOWN:
		error = false;
		if (wParam == VK_LEFT && sp[shapeCount - 1].x1 > 0)
		{
			sp[shapeCount - 1].x1 -= 5;
			sp[shapeCount - 1].x2 -= 5;
		}
		else if (wParam == VK_RIGHT && sp[shapeCount - 1].x2 < WINDOWSIDE - 20)
		{
			sp[shapeCount - 1].x1 += 5;
			sp[shapeCount - 1].x2 += 5;
		}
		else if (wParam == VK_UP && sp[shapeCount - 1].y1 > 0)
		{
			sp[shapeCount - 1].y1 -= 5;
			sp[shapeCount - 1].y2 -= 5;
		}
		else if (wParam == VK_DOWN && sp[shapeCount - 1].y2 < WINDOWUP - 40)
		{
			sp[shapeCount - 1].y1 += 5;
			sp[shapeCount - 1].y2 += 5;
		}
		else if (wParam == VK_RETURN)
		{
			//숫자 값도 검사해줘
			int i = 0;
			bool NotValid = false;
			cword = 0;
			while (str[i] != ' ')
			{
				if (str[i] == '\0')
				{
					NotValid = true;
					error = true;
					break;
				}
				sp[shapeCount].order = str[i++];
				
			}
			if (sp[shapeCount].order < '1' || sp[shapeCount].order>'4')
			{
				NotValid = true;
				error = true;
				break;
			}
			i++;
			while (str[i] != ' ')
			{
				if (str[i] == '\0')
				{
					NotValid = true;
					error = true;
					break;
				}
				sp[shapeCount].x1 = sp[shapeCount].x1 * 10 + (str[i++] - 48);
			}
			if (sp[shapeCount].x1 < 0 || sp[shapeCount].x1>WINDOWSIDE - 40)
			{
				NotValid = true;
				error = true;
				break;
			}
			i++;
			while (str[i] != ' ')
			{
				if (str[i] == '\0')
				{
					NotValid = true;
					error = true;
					break;
				}
				sp[shapeCount].y1 = sp[shapeCount].y1 * 10 + (str[i++] - 48);
			}
			if (sp[shapeCount].y1 < 0 || sp[shapeCount].y1>WINDOWUP - 80)
			{
				NotValid = true;
				error = true;
				break;
			}
			i++;
			while (str[i] != ' ')
			{
				if (str[i] == '\0')
				{
					NotValid = true;
					error = true;
					break;
				}
				sp[shapeCount].x2 = sp[shapeCount].x2 * 10 + (str[i++] - 48);
			}
			if (sp[shapeCount].x2 < 0 || sp[shapeCount].x2>WINDOWSIDE - 40)
			{
				NotValid = true;
				error = true;
				break;
			}
			i++;
			while (str[i] != ' ')
			{
				if (str[i] == '\0')
				{
					NotValid = true;
					error = true;
					break;
				}
				sp[shapeCount].y2 = sp[shapeCount].y2 * 10 + (str[i++] - 48);
			}
			if (sp[shapeCount].y2 < 0 || sp[shapeCount].y2>WINDOWUP - 80)
			{
				NotValid = true;
				error = true;
				break;
			}
			i++;
			while (str[i] != ' ')
			{
				if (str[i] == '\0')
					break;
				sp[shapeCount].thick = sp[shapeCount].thick * 10 + str[i++] - 48;
			}
			if (sp[shapeCount].thick<0 || sp[shapeCount].thick>10)
			{
				NotValid = true;
				error = true;
				break;
			}
			for (int i = 0; i < 100; i++)
			{
				str[i] = '\0';
			}

			if (NotValid == true)
			{
				sp[shapeCount].order = 0;
				sp[shapeCount].x1 = 0;
				sp[shapeCount].y1 = 0;
				sp[shapeCount].x2 = 0;
				sp[shapeCount].y2 = 0;
				sp[shapeCount].thick = 0;
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			}
			else
			{
				sp[shapeCount].ra = rand() % 256, sp[shapeCount].rb = rand() % 256, sp[shapeCount].rc = rand() % 256;


				shapeCount++;
				select = shapeCount - 1;
			}

		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);
		//print
		{
			printf("color : %d %d %d\n", sp[shapeCount - 1].a, sp[shapeCount - 1].b, sp[shapeCount - 1].c);
			printf("x,y : %d %d %d %d\n", sp[shapeCount - 1].x1, sp[shapeCount - 1].x2, sp[shapeCount - 1].y1, sp[shapeCount - 1].y2);
			printf("thick : %d\n", sp[shapeCount - 1].thick);
			printf("select : %d\n", select);

		}
		if (('0' <= wParam && wParam <= '9') || wParam == ' ')
		{
			str[cword++] = wParam;
			str[cword] = '\0';
		}

		if (wParam == 'p' || wParam == 'P' ||
			wParam == 'n' || wParam == 'N' ||
			wParam == 'a' || wParam == 'A' ||
			wParam == '+' || wParam == '-' ||
			wParam == 'c' || wParam == 'C' ||
			wParam == 'b' || wParam == 'B')
		{
			if (shapeCount == 0)
			{
				error = true;
				ReleaseDC(hwnd, hdc);
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			}
		}
		if (wParam == 'p' || wParam == 'P')
		{
			if (select > 0)
				select--;
		}
		if (wParam == 'n' || wParam == 'N')
		{
			if (select < shapeCount - 1)
				select++;
		}
		if (wParam == 'a' || wParam == 'A')
		{
			DrawAll *= -1;
		}

		if (wParam == '+')
		{//두께 10이하면 늘려
			if (sp[select].thick < 10)
			{
				sp[select].thick++;
			}//아니면 도형 사이즈를 늘려
			else if(sp[select].x2 + 40 < WINDOWSIDE &&
				sp[select].y2 + 80 < WINDOWUP)
			{
				sp[select].x2 += 5;
				sp[select].y2 += 5;
			}
		}
		if (wParam == '-')
		{//Opposite
			if (sp[select].thick > 0)
			{
				sp[select].thick--;
			}
			else if (sp[select].x1 + 20 < sp[select].x2 &&
				sp[select].y1 + 20 < sp[select].y2)
			{
				sp[select].x2 -= 5;
				sp[select].y2 -= 5;
			}
		}
		if (wParam == 'c' || wParam == 'C')//내부 색 바꾸기
			sp[select].a = uid(rd), sp[select].b = uid(rd), sp[select].c = uid(rd);
		if(wParam == 'b'||wParam == 'B')//테두리 바꾸기
			sp[select].a = uid(rd), sp[select].rb = uid(rd), sp[select].rc = uid(rd);
		if (wParam == 'q')
		{
			PostQuitMessage(0);

		}
		ReleaseDC(hwnd, hdc);
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}