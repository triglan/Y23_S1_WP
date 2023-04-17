#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>
#include <random>

#define WINDOWSIZE 800
//TODO : Delete, oldBrush�� ������� �������ٰ� �Ͻ�.
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 1";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

struct mainCharacter {
	int x;
	int y;
	int size;

	int shape;
	int a, b, c;
	bool feed;
	int ai;
};

//�� �Ӹ� + ������ ����ü
static mainCharacter won[100] = { {10,10,5,0,100,200,200}, {9,10,5,1,150,0,250}, {8,10,5,2,100,30,250}, {7,10,5,1,30,230,40} };
static mainCharacter obj[100] = { };
static mainCharacter obs[100] = {  };

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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 300, 200, WINDOWSIZE + 18, WINDOWSIZE + 41, NULL, (HMENU)NULL, hInstance, NULL);
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

	//Ÿ�̸�
	static int Timer1Count = 0;
	static int Timer2Count = 0;
	static int wonSpeed = 200;
	//�¿�
	static bool wonright = true;
	static bool wonleft = false;
	static bool wonup = false;
	static bool wondown = false;
	static bool jump = false;
	static bool jump2 = false;
	//ĭ ����, ĭ ����
	static int space = 40;
	static int boardsize = WINDOWSIZE / space;
	// ���ΰ� ��������
	static int wonCount = 0;
	static int objCount = 0;
	static int obsCount = 0;

	// ���콺 ������ ��ġ
	static int mx;
	static int my;
	static bool clicked = false;
	static bool wonclicked = false;
	static bool playerMove = false;
	//����׸��� ī��Ʈ
	static int count = 0;
	srand(time(NULL));
	switch (uMsg)
	{
	case WM_CREATE:
		SetTimer(hwnd, 1, wonSpeed, NULL);
		SetTimer(hwnd, 2, wonSpeed, NULL);
		//������Ʈ ����
		for (int i = 0; i < 20; i++)
		{
			obj[i].x = rand() % 35 + 4;
			obj[i].y = rand() % 35 + 4;
			obj[i].shape = rand() % 3;
			obj[i].size = rand() % 2 + 5;
			obj[i].feed = false;
			obj[i].ai = rand() % 9;
			obj[i].a = rand() % 256, obj[i].b = rand() % 256, obj[i].c = rand() % 256;
			objCount++;
		}
		//TEMP
		wonCount = 4;
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			Timer1Count++;
			Timer2Count++;

			break;
		default:
			break;
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		hBrush = CreateSolidBrush(RGB(100, 100, 100));
		for (int i = 0; i < objCount; i++)
		{
			if (obj[i].x == won[0].x && obj[i].y == won[0].y && obj[i].feed == false)//�Ӹ��� �浹 ��
			{
				obj[i].feed = true;
				obj[i].x += 1;//�ε�ġ�ڸ��� �ٷ� �������� �ǹ����ϱ�;
			}
			else if (obj[i].x == won[0].x && obj[i].y == won[0].y && obj[i].feed == true)//���̰� �Ӹ��� �浹 ��
			{
				obj[i].feed = false;
				won[wonCount++] = obj[i];
				for (int j = i; j < objCount; j++)
				{
					obj[j] = obj[j + 1];
				}
				objCount--;
			}
		}


		for (int objc = 0; objc < objCount; objc++)
		{
			for (int wonc = 1; wonc < wonCount; wonc++)
			{
				if (won[wonc].x == obj[objc].x && won[wonc].y == obj[objc].y && obj[objc].feed == true)
				{
					obj[objCount++] = won[wonc];
					obj[objCount - 1].feed = true;
					obj[objCount - 1].ai = obj[objc].ai;
					obj[objCount - 1].x--;
					for (int i = wonc; i < wonCount; i++)
					{
						won[i] = won[i + 1];
					}
					wonCount--;
				}
			}
		}


		if (wonclicked == true && Timer2Count % 3 == 0)
		{
			wonclicked = false;
			won[0].size = 5;
			mx = 0;
			my = 0;
		}
		//Ÿ�̸�
		if (Timer1Count % 2 == 0)
		{
			
			if (playerMove == true)
			{
				for (int i = wonCount - 2; i >= 0; i--)//���� ��ǥ ���� �ű�� �״����� �Ӹ� ��ǥ �̵�
				{
					won[i + 1].x = won[i].x;
					won[i + 1].y = won[i].y;
				}
				if (clicked == true)//Ŭ���� �������� ��������
				{
					if (won[0].x > mx / boardsize)
						won[0].x--;
					else if (won[0].x < mx / boardsize)
						won[0].x++;
					else if (won[0].y < my / boardsize)
						won[0].y++;
					else if (won[0].y > my / boardsize)
						won[0].y--;
					if (won[0].x == mx / 20 && won[0].y == my / 20)
					{
						clicked = false;
						wonleft = false;
						wonright = true;
						wonup = false;
						wondown = false;
						mx = 0;
						my = 0;
					}
				}
				else if (wonright == true)
				{
					if (won[0].x >= space - 1)//�����ڸ� �̵� ��
					{
						won[0].x = 0;
					}
					else if (jump2 == true)
					{
						won[0].x++;
						won[0].y++;
						jump2 = false;
					}
					else if (jump == true)//����
					{
						won[0].x++;
						won[0].y--;
						jump = false;
						jump2 = true;
					}
					else if (clicked == true)
					{
						if (won[0].x > mx / boardsize)
							won[0].x--;
						else if (won[0].x < mx / boardsize)
							won[0].x++;
						else if (won[0].y < my / boardsize)
							won[0].y++;
						else if (won[0].y > my / boardsize)
							won[0].y--;
						else if (won[0].x == mx / 20 && won[0].y == my / 20)
							clicked == false;
					}
					else
						won[0].x++;
					for (int i = 0; i < obsCount; i++)//��ֹ��� �浹 ��
					{
						if (obs[i].x == won[0].x && obs[i].y == won[0].y && won[0].y < space / 2)
						{
							won[0].x--;
							won[0].y++;
							wondown = true;
							wonright = false;
						}
						else if (obs[i].x == won[0].x && obs[i].y == won[0].y && won[0].y >= space / 2)
						{
							won[0].x--;
							won[0].y--;
							wondown = true;
							wonright = false;
						}
					}
				}
				else if (wonleft == true)
				{
					if (won[0].x <= 0)//�����ڸ� �̵� ��
					{
						won[0].x = space - 1;
					}
					else if (jump2 == true)
					{
						won[0].x--;
						won[0].y++;
						jump2 = false;
					}
					else if (jump == true)//����
					{
						won[0].x--;
						won[0].y--;
						jump = false;
						jump2 = true;
					}
					else if (clicked == true)//Ŭ���� �������� ��������
					{
						if (won[0].x > mx / boardsize)
							won[0].x--;
						else if (won[0].x < mx / boardsize)
							won[0].x++;
						else if (won[0].y < my / boardsize)
							won[0].y++;
						else if (won[0].y > my / boardsize)
							won[0].y--;
						else if (won[0].x == mx / 20 && won[0].y == my / 20)
							clicked == false;
					}
					else
						won[0].x--;
					for (int i = 0; i < obsCount; i++)//��ֹ��� �浹 ��
					{
						if (obs[i].x == won[0].x && obs[i].y == won[0].y && won[0].y < space / 2)
						{
							won[0].x++;
							won[0].y++;
							wondown = true;
							wonleft = false;
						}
						else if (obs[i].x == won[0].x && obs[i].y == won[0].y && won[0].y >= space / 2)
						{
							won[0].x++;
							won[0].y--;
							wondown = true;
							wonleft = false;
						}
					}
				}
				else if (wonup == true)
				{
					if (won[0].y <= 0)//�����ڸ� �̵� ��
					{
						won[0].y = space - 1;
					}
					else if (jump2 == true)
					{
						won[0].x++;
						won[0].y--;
						jump2 = false;
					}
					else if (jump == true)//����
					{
						won[0].x--;
						won[0].y--;
						jump = false;
						jump2 = true;
					}
					else if (clicked == true)//Ŭ���� �������� ��������
					{
						if (won[0].x > mx / boardsize)
							won[0].x--;
						else if (won[0].x < mx / boardsize)
							won[0].x++;
						else if (won[0].y < my / boardsize)
							won[0].y++;
						else if (won[0].y > my / boardsize)
							won[0].y--;
						else if (won[0].x == mx / 20 && won[0].y == my / 20)
							clicked == false;
					}
					else
						won[0].y--;
					for (int i = 0; i < obsCount; i++)//��ֹ��� �浹 ��
					{
						if (obs[i].x == won[0].x && obs[i].y == won[0].y && won[0].x < space / 2)
						{
							won[0].x++;
							won[0].y++;
							wonright = true;
							wonup = false;
						}
						else if (obs[i].x == won[0].x && obs[i].y == won[0].y && won[0].x >= space / 2)
						{
							won[0].x--;
							won[0].y++;
							wonleft = true;
							wonup = false;
						}
					}
				}
				else if (wondown == true)
				{
				if (won[0].y >= space - 1)//�����ڸ� �̵� ��
				{
					won[0].y = 0;
				}
				else if (jump2 == true)
				{
					won[0].x--;
					won[0].y++;
					jump2 = false;
				}
				else if (jump == true)//����
				{
					won[0].x++;
					won[0].y++;
					jump = false;
					jump2 = true;
				}
				
				else
					won[0].y++;
				for (int i = 0; i < obsCount; i++)//��ֹ��� �浹 ��
				{
					if (obs[i].x == won[0].x && obs[i].y == won[0].y && won[0].x < space / 2)
					{
						won[0].x++;
						won[0].y--;
						wonright = true;
						wondown = false;
					}
					else if (obs[i].x == won[0].x && obs[i].y == won[0].y && won[0].x >= space / 2)
					{
						won[0].x--;
						won[0].y--;
						wonleft = true;
						wondown = false;
					}
				}
				}
			}


			//������Ʈ ������
			for (int i = 0; i < objCount; i++)
			{
				if (obj[i].feed == false)
				{
					if (obj[i].ai == 0)//��� �̵�
					{
						obj[i].x++;
						if (obj[i].x >= space - 1)
							obj[i].ai = 1;
					}
					else if (obj[i].ai == 1)//�·� �̵�
					{
						obj[i].x--;
						if (obj[i].x <= 0)
							obj[i].ai = 0;
					}
					else if (obj[i].ai == 2)
					{
						obj[i].y++;
						if (obj[i].y >= space - 1)
							obj[i].ai = 3;
					}
					else if (obj[i].ai == 3)
					{
						obj[i].y--;
						if (obj[i].y <= 0)
							obj[i].ai = 2;
					}
					else if (obj[i].ai == 8)
					{

					}
					if (count % 3 == 0)
					{
						if (obj[i].ai == 4)
							obj[i].ai = 5;
						else if (obj[i].ai == 5)
							obj[i].ai = 6;
						else if (obj[i].ai == 6)
							obj[i].ai = 7;
						else if (obj[i].ai == 7)
							obj[i].ai = 4;
					}
					if (obj[i].ai == 4)//����?
					{
						obj[i].x--;
						obj[i].y++;
					}
					else if (obj[i].ai == 5)//����?
					{
						obj[i].x++;
					}
					else if (obj[i].ai == 6)//����?
					{
						obj[i].x++;
					}
					else if (obj[i].ai == 7)//����?
					{
						obj[i].x--;
						obj[i].y--;
					}
					count++;

				}
				
			}


		}


		//������ �׸���
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
		//��ֹ�
		for (int i = 0; i < obsCount; i++)
		{
			int x = ((2 * obs[i].x + 1) * boardsize) / 2;
			int y = ((2 * obs[i].y + 1) * boardsize) / 2;
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hBrush);
			Rectangle(hdc, x - 8, y - 8, x + 8, y + 8);
		}
		//������Ʈ
		for (int i = 0; i < objCount; i++)
		{
			int x = ((2 * obj[i].x + 1) * boardsize) / 2;
			int y = ((2 * obj[i].y + 1) * boardsize) / 2;
			hBrush = CreateSolidBrush(RGB(obj[i].a, obj[i].b, obj[i].c));
			SelectObject(hdc, hBrush);
			//if (won[i].shape == 0)
			Ellipse(hdc, x - obj[i].size, y - obj[i].size, x + obj[i].size, y + obj[i].size);
			//else if (obj[i].shape == 1)
			//	Rectangle(hdc, x - obj[i].size, y - obj[i].size, x + obj[i].size, y + obj[i].size);
			//else if (obj[i].shape == 2)
			//	Pie(hdc, x - obj[i].size, y - obj[i].size, x + obj[i].size, y + obj[i].size, x + obj[i].size, y - obj[i].size, x + obj[i].size, y + obj[i].size);
		}

		//���ΰ� x,y
		for (int i = 0; i < wonCount; i++)
		{
			int x = ((2 * won[i].x + 1) * boardsize) / 2;
			int y = ((2 * won[i].y + 1) * boardsize) / 2;
			hBrush = CreateSolidBrush(RGB(won[i].a, won[i].b, won[i].c));
			SelectObject(hdc, hBrush);
			/*if (won[i].shape == 0)*/
			Ellipse(hdc, x - won[i].size, y - won[i].size, x + won[i].size, y + won[i].size);
			//else if (won[i].shape == 1)
			//	Rectangle(hdc, x - won[i].size, y - won[i].size, x + won[i].size, y + won[i].size);
			//else if (won[i].shape == 2)
			//	Pie(hdc, x - won[i].size, y - won[i].size, x + won[i].size, y + won[i].size, x + won[i].size, y - won[i].size, x + won[i].size, y + won[i].size);
		}

		EndPaint(hwnd, &ps);
		break;

	case WM_RBUTTONDOWN:
		if (obsCount >= 19)
		{
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		for (int i = 0; i < wonCount; i++)
		{
			if (mx / boardsize == won[i].x && my / boardsize == won[i].y)
			{
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			}
		}
		for (int i = 0; i < objCount; i++)
		{
			if (mx / boardsize == obj[i].x && my / boardsize == my / boardsize == obj[i].y)
			{
				InvalidateRect(hwnd, NULL, TRUE);
				break;
			}
		}
		obs[obsCount].x = mx / boardsize;
		obs[obsCount++].y = my / boardsize;
		mx = 0;
		my = 0;
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONDOWN:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (mx / boardsize == won[0].x && my / boardsize == won[0].y)
		{
			won[0].size = 10;
			wonclicked = true;
		}
		else if (mx / boardsize == won[wonCount - 1].x && my / boardsize == won[wonCount - 1].y)//������ Ŭ��
		{
			obj[objCount++] = won[wonCount - 1];
			wonCount--;
		}
		else
			clicked = true;

		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		printf("x : %d	Speed : %d\n", won[0].x, wonSpeed);
		if (wParam == VK_UP)//���� �ٲٴ� �ɷ� �ٲ��ְ� �����ڸ� �����ϸ� �������, �ڱ� ������ �̵� ����
		{
			wonright = false;
			wonleft = false;
			wonup = true;
			wondown = false;
		}
		if (wParam == VK_DOWN)//���� �ٲٴ� �ɷ� �ٲ��ְ� �����ڸ� �����ϸ� �������, �ڱ� ������ �̵� ����
		{
			wonright = false;
			wonleft = false;
			wonup = false;
			wondown = true;
		}
		if (wParam == VK_RIGHT)//���� �ٲٴ� �ɷ� �ٲ��ְ� �����ڸ� �����ϸ� �������, �ڱ� ������ �̵� ����
		{
			wonright = true;
			wonleft = false;
			wonup = false;
			wondown = false;
		}
		if (wParam == VK_LEFT)//���� �ٲٴ� �ɷ� �ٲ��ְ� �����ڸ� �����ϸ� �������, �ڱ� ������ �̵� ����
		{
			wonright = false;
			wonleft = true;
			wonup = false;
			wondown = false;
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_CHAR:
		if(wParam == 'j' || wParam == 'J')
		{
			jump = true;
		}
		if (wParam == 't' || wParam == 'T')
		{
			won[wonCount] = won[0];
			for (int i = 0; i < wonCount; i++)
			{
				won[i] = won[i + 1];
			}
		}
		if (wParam == 's' || wParam == 'S')
		{
			if (playerMove == true)
				playerMove = false;
			else
				playerMove = true;
		}
		if (wParam == 'q' || wParam == 'Q')
		{
			PostQuitMessage(0);
		}
		if (wParam == '+')
		{
			if (wonSpeed > 100)
				wonSpeed -= 50;
			SetTimer(hwnd, 1, wonSpeed, NULL);
			SetTimer(hwnd, 2, wonSpeed, NULL);
		}
		else if (wParam == '-')
		{
			wonSpeed += 50;
			SetTimer(hwnd, 1, wonSpeed, NULL);
			SetTimer(hwnd, 2, wonSpeed, NULL);
		}
		
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
