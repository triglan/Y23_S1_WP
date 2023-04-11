#include <windows.h>
#include <tchar.h>
#include <time.h>
#include <random>

std::random_device rd;
std::uniform_int_distribution<> uid(0, 255);

#define MAXSHAPE 1600
#define WINDOWSIZE 600
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 1";

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

struct Shapes {
	char order;
	int x;
	int	y;

	int a;
	int b;
	int c;

	int size;
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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 600, 200, WINDOWSIZE + 18, WINDOWSIZE + 41, NULL, (HMENU)NULL, hInstance, NULL);
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
	srand(time(NULL));

	HBRUSH hBrush[MAXSHAPE];
	HPEN hPen[MAXSHAPE];
	HPEN oldPen;

	static SIZE size;
	//space : 보드 칸 수 boardsize : 칸당 크기
	static int space = 40;
	int boardsize = WINDOWSIZE / space;

	static Shapes sp[MAXSHAPE];
	static Shapes temp[MAXSHAPE];

	static int shapeCount = 0;
	static int select = 0;

	static int changeColor = 1;
	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		//보드판 그리기
		{
			for (int x = 0; x <= space; x++)
			{
				MoveToEx(hdc, x * boardsize, 0, NULL);
				LineTo(hdc, x * boardsize, WINDOWSIZE);
			}
			for (int y = 0; y <= space; y++)
			{
				MoveToEx(hdc, 0, y * boardsize, NULL);
				LineTo(hdc, WINDOWSIZE, y * boardsize);
			}
		}
		oldPen = CreatePen(PS_DOT, 0, RGB(255, 255, 255));
		for (int i = 0; i < shapeCount; i++)
		{
			SelectObject(hdc, oldPen);

			POINT TriPoint[10] = { {(2 * sp[i].x * boardsize + boardsize) / 2, (2 * sp[i].y * boardsize + boardsize) / 2 - (sp[i].size * boardsize / 8)},
				{(2 * sp[i].x * boardsize + boardsize) / 2 - (sp[i].size * boardsize / 8), (2 * sp[i].y * boardsize + boardsize) / 2 + (sp[i].size * boardsize / 8) },
				{(2 * sp[i].x * boardsize + boardsize) / 2 + (sp[i].size * boardsize / 8), (2 * sp[i].y * boardsize + boardsize) / 2 + (sp[i].size * boardsize / 8)} };
			if (i == select)//선택된 도형에 강조 표시
			{
				hPen[i] = CreatePen(PS_DOT, 3, RGB(230, 30, 30));
				SelectObject(hdc, hPen[i]);
			}
			switch (sp[i].order)
			{
			case 'r':
				hBrush[i] = CreateSolidBrush(RGB(sp[i].a, sp[i].b, sp[i].c));
				SelectObject(hdc, hBrush[i]);
				Rectangle(hdc, (2 * sp[i].x * boardsize + boardsize) / 2 - (sp[i].size * boardsize / 8), (2 * sp[i].y * boardsize + boardsize) / 2 - (sp[i].size * boardsize / 8),
					(2 * sp[i].x * boardsize + boardsize) / 2 + (sp[i].size * boardsize / 8), (2 * sp[i].y * boardsize + boardsize) / 2 + (sp[i].size * boardsize / 8));
				break;
			case 't':
				hBrush[i] = CreateSolidBrush(RGB(sp[i].a, sp[i].b, sp[i].c));
				SelectObject(hdc, hBrush[i]);
				Polygon(hdc, TriPoint, 3);
				break;
			case 'e':
				hBrush[i] = CreateSolidBrush(RGB(sp[i].a, sp[i].b, sp[i].c));
				SelectObject(hdc, hBrush[i]);
				Ellipse(hdc, (2 * sp[i].x * boardsize + boardsize) / 2 - (sp[i].size * boardsize / 8), (2 * sp[i].y * boardsize + boardsize) / 2 - (sp[i].size * boardsize / 8),
					(2 * sp[i].x * boardsize + boardsize) / 2 + (sp[i].size * boardsize / 8), (2 * sp[i].y * boardsize + boardsize) / 2 + (sp[i].size * boardsize / 8));
				break;
			default:
				break;
			}
			SelectObject(hdc, oldPen);
		}
		
		
		ReleaseDC(hwnd, hdc);
		EndPaint(hwnd, &ps);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_LEFT)
		{
			if (sp[select].x > 0)
				sp[select].x--;
			for (int i = 0; i < shapeCount; i++)
			{
				if(sp[select].x == sp[i].x && sp[select].y == sp[i].y)//충돌하면
					if (i != select)//본인께 아니면
					{
						sp[select].x++;
						break;
					}
			}
		}
		if (wParam == VK_RIGHT)
		{
			if (sp[select].x < space - 1)
				sp[select].x++;
			for (int i = 0; i < shapeCount; i++)
			{
				if (sp[select].x == sp[i].x && sp[select].y == sp[i].y)//충돌하면
					if (i != select)//본인께 아니면
					{
						sp[select].x--;
						break;
					}
			}
		}
		if (wParam == VK_UP)
		{
			if (sp[select].y > 0)
				sp[select].y--;
			for (int i = 0; i < shapeCount; i++)
			{
				if (sp[select].x == sp[i].x && sp[select].y == sp[i].y)//충돌하면
					if (i != select)//본인께 아니면
					{
						sp[select].y++;
						break;
					}
			}
		}
		if (wParam == VK_DOWN)
		{
			if (sp[select].y < space - 1)
				sp[select].y++;
			for (int i = 0; i < shapeCount; i++)
			{
				if (sp[select].x == sp[i].x && sp[select].y == sp[i].y)//충돌하면
					if (i != select)//본인께 아니면
					{
						sp[select].y--;
						break;
					}
			}
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_CHAR:
		hdc = GetDC(hwnd);
		//printf("order : %c x : %d y : %d size : %d select : %d shapeCount : %d \n", sp[shapeCount - 1].order, sp[shapeCount - 1].x, sp[shapeCount - 1].y, sp[shapeCount - 1].size, select, shapeCount);

		
		//도형 생성
		if (wParam == 'r' || wParam == 'R')
		{
			if (shapeCount > 9)//10개가 넘으면
			{
				for (int i = 0; i < shapeCount; i++)
				{
					sp[i] = sp[i + 1];
				}
				shapeCount = 9;
				select = 9;
			}
			int randx;
			int randy;
			bool over = false;
			while (true)
			{
				//std::uniform_int_distribution<> uid(0, space);
				over = false;
				randx = rand()%space;
				randy = rand()%space;
				//x,y좌표가 둘다 같으면 다시 실행 아니면 탈출
				for (int i = 0; i < shapeCount; i++)
				{
					printf("%d", over);

					if (sp[i].x == randx && sp[i].y == randy)
					{
						over = true;
						break;
					}
				}
				//중복 없으면 탈출해
				if (!over)
					break;
			}
			printf("\n\n");
			sp[shapeCount].order = 'r';
			sp[shapeCount].x = randx;
			sp[shapeCount].y = randy;
			sp[shapeCount].a = rand()%256, sp[shapeCount].b = rand()%256, sp[shapeCount].c = rand()%256;
			sp[shapeCount++].size = 2;
			if (select == shapeCount - 1)
				select = shapeCount;

		}
		if (wParam == 't' || wParam == 'T')
		{
			if (shapeCount > 9)//10개가 넘으면
			{
				for (int i = 0; i < shapeCount; i++)
				{
					sp[i] = sp[i + 1];
				}
				shapeCount = 9;
				select = 9;
			}
			int randx;
			int randy;
			bool over = false;
			while (true)
			{
				over = false;
				std::uniform_int_distribution<> uid(0, space);
				randx = rand() % space;
				randy = rand() % space;
				//x,y좌표가 둘다 같으면 다시 실행 아니면 탈출
				for (int i = 0; i < shapeCount; i++)
				{
					if (sp[i].x == randx && sp[i].y == randy)
					{
						over = true;
						break;
					}
				}
				//중복 없으면 탈출해
				if (!over)
					break;
			}
			sp[shapeCount].order = 't';
			sp[shapeCount].x = randx;
			sp[shapeCount].y = randy;
			sp[shapeCount].a = rand() % 256, sp[shapeCount].b = rand() % 256, sp[shapeCount].c = rand() % 256;
			sp[shapeCount++].size = 2;
			if (select == shapeCount - 1)
				select = shapeCount;
		}
		if (wParam == 'e' || wParam == 'E')
		{
			if (shapeCount > 9)//10개가 넘으면
			{
				for (int i = 0; i < shapeCount; i++)
				{
					sp[i] = sp[i + 1];
				}
				shapeCount = 9;
				select = 9;
			}
			int randx;
			int randy;
			bool over = false;
			while (true)
			{
				over = false;
				randx = rand() % space;
				randy = rand() % space;
				//x,y좌표가 둘다 같으면 다시 실행 아니면 탈출
				for (int i = 0; i < shapeCount; i++)
				{
					if (sp[i].x == randx && sp[i].y == randy)
					{
						over = true;
						break;
					}
				}
				//중복 없으면 탈출해
				if (!over)
					break;
			}
			sp[shapeCount].order = 'e';
			sp[shapeCount].x = randx;
			sp[shapeCount].y = randy;
			sp[shapeCount].a = rand() % 256, sp[shapeCount].b = rand() % 256, sp[shapeCount].c = rand() % 256;
			sp[shapeCount++].size = 2;
			if (select == shapeCount - 1)
				select = shapeCount;
		}
		//보드 칸 사이즈 zxc
		if (wParam == 'z' || wParam == 'Z')
			if(space > 5)
				space -= 5;
		if (wParam == 'x' || wParam == 'X')
			space = 15;
		if (wParam == 'c' || wParam == 'C')
			space += 5;
		if ('0' <= wParam && wParam <= '9')
		{
			select = wParam - 48;
		}
		if (wParam == '+')
		{
			if(sp[select].size < 4)
			sp[select].size++;
		}
		if (wParam == '-')
		{
			if (sp[select].size > 1)
				sp[select].size--;
		}
		if (wParam == 'f' || wParam == 'F')
		{
			if (changeColor == 1)
			{
				int a1 = rand() % 256, b1 = rand() % 256, c1 = rand() % 256;
				int a2 = rand() % 256, b2 = rand() % 256, c2 = rand() % 256;
				int a3 = rand() % 256, b3 = rand() % 256, c3 = rand() % 256;
				for (int i = 0; i < shapeCount; i++)
				{
					temp[i] = sp[i];
					if (sp[i].order == 'e')
					{//temp에 미리 저장해놓고 색을 다 바꿈
						sp[i].a = a1;
						sp[i].b = b1;
						sp[i].c = c1;
					}
					if (sp[i].order == 'r')
					{
						sp[i].a = a2;
						sp[i].b = b2;
						sp[i].c = c2;
					}
					if (sp[i].order == 't')
					{
						sp[i].a = a3;
						sp[i].b = b3;
						sp[i].c = c3;
					}
				}
			}
			else
			{
				for (int i = 0; i < shapeCount; i++)
				{
					sp[i] = temp[i];
				}
			}
			changeColor *= -1;
		}
		if (wParam == 'd' || wParam == 'D')
		{
			for (int i = select; i < shapeCount; i++)
			{
				sp[i] = sp[i + 1];
			}
				shapeCount--;
		}
		if (wParam == 'p' || wParam == 'P')
		{
			shapeCount = 0;
			select = 0;
		}
		if (wParam == 'q' || wParam == 'Q')
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