#include <windows.h>
#include <tchar.h>
#include <time.h>
#include <stdio.h>

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 1";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int randDivX;
int randDivY;
int randPicture[10000];

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	SIZE size;

	srand(time(NULL));
	randDivX = rand() % 9 + 2;
	randDivY = randDivX / 2 + 2;

	static TCHAR str[100][1000];
	int r1, g1, b1;
	int r2, g2, b2;

	int dx = 760 / randDivX;
	int dy = 560 / randDivY;

	for (int i = 0; i < 10000; i++)
	{
		randPicture[i] = rand() % 6;
	}

	TCHAR ystr[100] = { 'X' };
	TCHAR nstr[100] = { ' ', ' '};

	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//randDivY, randDivX
		for (int Bigy = 0; Bigy < randDivY; Bigy++)
		{
			for (int Bigx = 0; Bigx < randDivX; Bigx++)
			{
				//Box
				{
					r1 = rand() % 257, g1 = rand() % 257, b1 = rand() % 257;
					r2 = rand() % 257, g2 = rand() % 257, b2 = rand() % 257;
					rect.left = Bigx * dx;
					rect.top = Bigy * dy;
					rect.right = (Bigx + 1) * dx;
					rect.bottom = (Bigy + 1) * dy;

					SetBkColor(hdc, RGB(r1, g1, b1));
					SetTextColor(hdc, RGB(r2, g2, b2));
				}

				
				switch (randPicture[Bigy * randDivX + Bigx])
				{
				case 0:	//X
					for (int y = 0; y < dy / 16; y++)
					{
						for (int x = 0; x < dx / 8; x++)
						{
							if (x == y || x == (dy / 16 - y - 1))
								TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, ystr, 1);//출력
							else
								TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, nstr, 2);//출력
						}
					}
					break;
				case 1:	//삼각형
					for (int y = 0; y < dy / 16; y++)
					{
						for (int x = 0; x < dx / 8; x++)
						{
							if (x > y && x < (dy / 8 - y - 1))
								TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, ystr, 1);//출력
							else
								TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, nstr, 2);//출력
						}
					}
					break;
				case 2: // diamond
					for (int y = 0; y < dy / 32; y++)
					{
						for (int x = 0; x < dx / 8; x++)
						{
							if (x >= dy / 16 - y &&
								x <= dy / 16 + y)
								TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, ystr, 1);//출력
							else
								TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, nstr, 2);//출력
						}
					}
					for (int y = dy / 32; y < dy / 16; y++)
					{
						for (int x = 0; x < dx / 8; x++)
						{
							if (x > y &&
								x < (dy / 8 - y - 1))
								TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, ystr, 1);//출력
							else
								TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, nstr, 2);//출력
						}
					}

				case 3://butterFly
					for (int y = 0; y < dy / 32; y++)
					{
						for (int x = 0; x < dx / 8; x++)
						{
							if ((x <= y ||
								x > dy / 16 - y - 1) && x < dy / 16 + 1)
								TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, ystr, 1);//출력
							else
								TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, nstr, 2);//출력
						}
					}
					for (int y = dy / 32; y < dy / 16; y++)
					{
						for (int x = 0; x < dx / 8; x++)
						{
							if ((x >= 0 && x < dy / 16 - y) ||
								(x > y && x <= dy / 16))
								TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, ystr, 1);//출력
							else
								TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, nstr, 2);//출력
						}
					}

				case 4: // SandClock
					for (int y = 0; y < dy / 32; y++)
					{
						for (int x = 0; x < dx / 8; x++)
						{
							if ((y <= x &&
								x < dy / 16 - y) && x < dy / 16 + 1)
								TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, ystr, 1);//출력
							else
								TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, nstr, 2);//출력
						}
					}//x > y && x < (dy / 8 - y - 1)
					for (int y = dy / 32; y < dy / 16; y++)
					{
						for (int x = 0; x < dx / 8; x++)
						{
							if ((dy / 16 - y - 1 <= x &&
								x < y + 1) && x < dy / 16 + 1)
								TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, ystr, 1);//출력
							else
								TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, nstr, 2);//출력
						}
					}
					break;

				case 5://double Rect
					for (int y = 0; y < dy / 16; y++)
					{
						for (int x = 0; x < dx / 8; x++)
						{
							if (x == 0 || x == dy / 32 || x == dy / 32 + 1 || x == dy / 16)
								TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, ystr, 1);//출력
							else
								TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy) + y * 16, nstr, 2);//출력
						}
					}
					for (int x = 0; x < dx / 8; x++)
					{
						if (x < dy / 16 + 1)
							TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy), ystr, 1);//출력
						else
							TextOut(hdc, (Bigx * dx) + x * 8, (Bigy * dy), nstr, 2);//출력
					}
					for (int x = 0; x < dx / 8; x++)
					{
						if (x < dy / 16 + 1)
							TextOut(hdc, (Bigx * dx) + x * 8, ((Bigy + 1) * dy - 16), ystr, 1);//출력
						else
							TextOut(hdc, (Bigx * dx) + x * 8, ((Bigy + 1) * dy - 16), nstr, 2);//출력
					}


					break;
				default:
					break;
				}
					

			}
		}


		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}