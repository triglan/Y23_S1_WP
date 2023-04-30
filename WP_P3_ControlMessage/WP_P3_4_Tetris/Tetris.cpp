#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>
#include <random>

#define SIDE 450
#define UP 900

//TODO : Delete, oldBrush�� ������� �������ٰ� �Ͻ�.
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 1";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

struct mainCharacter {
	int x, y;

	int shape;
	int id;
	int a, b, c;
	bool move = true;
	bool life = true;
};



//�� �Ӹ� + ������ ����ü
static mainCharacter brick[1000];

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

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 600, 200, SIDE + 18, UP + 41, NULL, (HMENU)NULL, hInstance, NULL);
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

	HDC mdc;
	HBITMAP hBitmap;
	RECT rt;

	//Ÿ�̸�
	static int Timer1Count = 0;
	static int wonSpeed = 100;
	
	//�⺻ ũ��
	static int xspace = 6;
	static int yspace = 12;
	static int size = UP / yspace;
	int scoord = 3;//���� x��ǥ
	//����
	int random;//��� ����
	static int brcount = 0;//�� ĭ ����
	static int idcount = 0;//ū �� ����
	static int a = 0, b = 0, c = 0;

	static bool createBrick = false;
	srand(time(NULL));
	switch (uMsg)
	{
	case WM_CREATE:
		SetTimer(hwnd, 1, wonSpeed, NULL);
		srand(time(NULL));
		//�� ����
		if (true) {
			random = rand() % 5;
			a = rand() % 256, b = rand() % 256, c = rand() % 256;
			switch (random)
			{
			case 0:
			{
				brick[brcount].shape = random;//���
				brick[brcount].a = a, brick[brcount].b = b, brick[brcount].c = c;//����
				brick[brcount].x = 3, brick[brcount].y = 0;//��ǥ
				brick[brcount++].id = idcount++;
			}
			break;
			case 1:
				for (int i = 0; i < 2; i++)//2�� �ݺ�
				{
					brick[brcount].shape = random;
					brick[brcount].a = a, brick[brcount].b = b, brick[brcount].c = c;//����
					brick[brcount].x = 3 - i, brick[brcount].y = 0;//��ǥ	
					brick[brcount++].id = idcount;
				}
				idcount++;
				break;
			case 2:
				for (int i = 0; i < 2; i++)//2�� �ݺ�
				{
					brick[brcount].shape = random;
					brick[brcount].a = a, brick[brcount].b = b, brick[brcount].c = c;//����
					brick[brcount].x = 3, brick[brcount].y = 1 - i;//��ǥ	
					brick[brcount++].id = idcount;
				}
				idcount++;
				break;
			case 3:
				for (int i = 0; i < 3; i++)//2�� �ݺ�
				{
					brick[brcount].shape = random;
					brick[brcount].a = a, brick[brcount].b = b, brick[brcount].c = c;//����
					brick[brcount].x = 3 - i, brick[brcount].y = 0;//��ǥ	
					brick[brcount++].id = idcount;
				}
				idcount++;
				break;
			case 4:
				for (int i = 0; i < 3; i++)//2�� �ݺ�
				{
					brick[brcount].shape = random;
					brick[brcount].a = a, brick[brcount].b = b, brick[brcount].c = c;//����
					brick[brcount].x = 3, brick[brcount].y = 2 - i;//��ǥ	
					brick[brcount++].id = idcount;
				}
				idcount++;
				break;
			default:
				break;
			}
		}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			Timer1Count++;
			break;
		default:
			break;
		}
		if (Timer1Count % 10) {
			for (int i = 0; i < brcount; i++)
			{
				if (brick[i].y >= yspace - 1 && brick[i].id == idcount - 1) //�ٴڰ� �浹 �� ����, ������ ID�϶���, TODO : ���� �浹 �� �� �־���, �浹 �� �� ����
				{
					for (int j = 0; j < brcount; j++)
					{
						if (brick[i].id == brick[j].id)//�ش� ID �� ����
						{
							brick[j].move = false;
							createBrick = true;
						}
					}
				}
				if (brick[i].move == true) //��������
					brick[i].y++;
			}
			for (int i = 0; i < brcount; i++)
			{
				//i�� �÷��̾� ID�� idcount - 1�̸� �÷��̾�, �ƴϸ� �ٸ� ��
				//�÷��̾�� �ٸ� ���� �浹 üũ �� �浹�̸� �÷��̾� �� ���� ����
				if (brick[i].id == idcount - 1) {//�÷��̾��
					for (int j = 0; j < brcount; j++) {
						if (brick[i].x == brick[j].x && brick[i].y == brick[j].y && brick[j].id != idcount - 1) {//�÷��̾�� �÷��̾� �ƴ� ��
							for (int k = 0; k < brcount; k++) {
								if (brick[i].id == brick[k].id) {
									brick[k].move = false;
									brick[k].y--;
									createBrick = true;
								}
							}
						}
					}
				}
			}
		}

		if (createBrick == true) {
			if (true) {
				random = rand() % 5;
				a = rand() % 256, b = rand() % 256, c = rand() % 256;
				switch (random)
				{
				case 0:
				{
					brick[brcount].shape = random;//���
					brick[brcount].a = a, brick[brcount].b = b, brick[brcount].c = c;//����
					brick[brcount].x = 3, brick[brcount].y = 0;//��ǥ
					brick[brcount++].id = idcount++;
				}
				break;
				case 1:
					for (int i = 0; i < 2; i++)//2�� �ݺ�
					{
						brick[brcount].shape = random;
						brick[brcount].a = a, brick[brcount].b = b, brick[brcount].c = c;//����
						brick[brcount].x = 3 - i, brick[brcount].y = 0;//��ǥ	
						brick[brcount++].id = idcount;
					}
					idcount++;
					break;
				case 2:
					for (int i = 0; i < 2; i++)//2�� �ݺ�
					{
						brick[brcount].shape = random;
						brick[brcount].a = a, brick[brcount].b = b, brick[brcount].c = c;//����
						brick[brcount].x = 3, brick[brcount].y = 1 - i;//��ǥ	
						brick[brcount++].id = idcount;
					}
					idcount++;
					break;
				case 3:
					for (int i = 0; i < 3; i++)//2�� �ݺ�
					{
						brick[brcount].shape = random;
						brick[brcount].a = a, brick[brcount].b = b, brick[brcount].c = c;//����
						brick[brcount].x = 3 - i, brick[brcount].y = 0;//��ǥ	
						brick[brcount++].id = idcount;
					}
					idcount++;
					break;
				case 4:
					for (int i = 0; i < 3; i++)//2�� �ݺ�
					{
						brick[brcount].shape = random;
						brick[brcount].a = a, brick[brcount].b = b, brick[brcount].c = c;//����
						brick[brcount].x = 3, brick[brcount].y = 2 - i;//��ǥ	
						brick[brcount++].id = idcount;
					}
					idcount++;
					break;
				default:
					break;
				}
			}
			createBrick = false;
		}
		
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_PAINT:
		printf("count : %d\n", brcount);
		GetClientRect(hwnd, &rt);
		hdc = BeginPaint(hwnd, &ps);
		mdc = CreateCompatibleDC(hdc); //--- �޸� DC �����
		hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom); //--- �޸� DC�� ������ ��Ʈ�� �����
		SelectObject(mdc, (HBITMAP)hBitmap);


		//������
		{
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
			Rectangle(mdc, 0, 0, SIDE, UP);
			SelectObject(mdc, oldBrush);
			DeleteObject(hBrush);
		}
		//������ �׸���
		{
			for (int x = 0; x <= xspace; x++)
			{
				MoveToEx(mdc, x * size, 0, NULL);
				LineTo(mdc, x * size, UP);
			}
			for (int y = 0; y <= yspace; y++)
			{
				MoveToEx(mdc, 0, y * size, NULL);
				LineTo(mdc, SIDE, y * size);
			}
		}
		//�� �׸���
		for (int i = 0; i < brcount; i++)
		{
			int x = ((2 * brick[i].x + 1) * size) / 2;
			int y = ((2 * brick[i].y + 1) * size) / 2;
			hBrush = CreateSolidBrush(RGB(brick[i].a, brick[i].b, brick[i].c));
			oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
			if (brick[i].life == true) {
				Rectangle(mdc, x - size / 2, y - size / 2, x + size / 2, y + size / 2);
			}
			SelectObject(mdc, oldBrush); // ������ ������ ���ư�
			DeleteObject(hBrush);
		}


		BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
		break;
	case WM_RBUTTONDOWN:
		
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONDOWN:
		
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		//printf("x : %d	Speed : %d\n", won[0].x, wonSpeed);
		if (wParam == VK_UP)
		{
			for (int i = 0; i < brcount; i++)
			{
				if (brick[i].move == true)
					brick[i].y--;
			}
		}
		if (wParam == VK_DOWN)
		{
			for (int i = 0; i < brcount; i++)
			{
				if (brick[i].move == true)
					brick[i].y++;
			}
		}
		if (wParam == VK_LEFT)
		{
			for (int i = 0; i < brcount; i++)
			{
				if (brick[i].move == true)
					brick[i].x--;
			}
		}
		if (wParam == VK_RIGHT)
		{
			for (int i = 0; i < brcount; i++)
			{
				if (brick[i].move == true)
					brick[i].x++;
			}
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_CHAR:
		
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
