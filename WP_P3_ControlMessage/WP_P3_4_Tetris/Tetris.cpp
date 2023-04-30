#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>
#include <random>

#define SIDE 450
#define UP 900

//TODO : Delete, oldBrush로 지워줘야 안터진다고 하심.
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



//각 머리 + 꼬리당 구조체
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

	//타이머
	static int Timer1Count = 0;
	static int wonSpeed = 100;
	
	//기본 크기
	static int xspace = 6;
	static int yspace = 12;
	static int size = UP / yspace;
	int scoord = 3;//시작 x좌표
	//개수
	int random;//모양 결정
	static int brcount = 0;//블럭 칸 개수
	static int idcount = 0;//큰 블럭 개수
	static int a = 0, b = 0, c = 0;

	static bool createBrick = false;
	srand(time(NULL));
	switch (uMsg)
	{
	case WM_CREATE:
		SetTimer(hwnd, 1, wonSpeed, NULL);
		srand(time(NULL));
		//블럭 생성
		if (true) {
			random = rand() % 5;
			a = rand() % 256, b = rand() % 256, c = rand() % 256;
			switch (random)
			{
			case 0:
			{
				brick[brcount].shape = random;//모양
				brick[brcount].a = a, brick[brcount].b = b, brick[brcount].c = c;//색상
				brick[brcount].x = 3, brick[brcount].y = 0;//좌표
				brick[brcount++].id = idcount++;
			}
			break;
			case 1:
				for (int i = 0; i < 2; i++)//2번 반복
				{
					brick[brcount].shape = random;
					brick[brcount].a = a, brick[brcount].b = b, brick[brcount].c = c;//색상
					brick[brcount].x = 3 - i, brick[brcount].y = 0;//좌표	
					brick[brcount++].id = idcount;
				}
				idcount++;
				break;
			case 2:
				for (int i = 0; i < 2; i++)//2번 반복
				{
					brick[brcount].shape = random;
					brick[brcount].a = a, brick[brcount].b = b, brick[brcount].c = c;//색상
					brick[brcount].x = 3, brick[brcount].y = 1 - i;//좌표	
					brick[brcount++].id = idcount;
				}
				idcount++;
				break;
			case 3:
				for (int i = 0; i < 3; i++)//2번 반복
				{
					brick[brcount].shape = random;
					brick[brcount].a = a, brick[brcount].b = b, brick[brcount].c = c;//색상
					brick[brcount].x = 3 - i, brick[brcount].y = 0;//좌표	
					brick[brcount++].id = idcount;
				}
				idcount++;
				break;
			case 4:
				for (int i = 0; i < 3; i++)//2번 반복
				{
					brick[brcount].shape = random;
					brick[brcount].a = a, brick[brcount].b = b, brick[brcount].c = c;//색상
					brick[brcount].x = 3, brick[brcount].y = 2 - i;//좌표	
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
				if (brick[i].y >= yspace - 1 && brick[i].id == idcount - 1) //바닥과 충돌 시 정지, 마지막 ID일때만, TODO : 블럭과 충돌 시 도 넣어줘, 충돌 후 블럭 생성
				{
					for (int j = 0; j < brcount; j++)
					{
						if (brick[i].id == brick[j].id)//해당 ID 블럭 정지
						{
							brick[j].move = false;
							createBrick = true;
						}
					}
				}
				if (brick[i].move == true) //떨어지기
					brick[i].y++;
			}
			for (int i = 0; i < brcount; i++)
			{
				//i는 플레이어 ID가 idcount - 1이면 플레이어, 아니면 다른 블럭
				//플레이어와 다른 블럭의 충돌 체크 후 충돌이면 플레이어 블럭 전부 정지
				if (brick[i].id == idcount - 1) {//플레이어면
					for (int j = 0; j < brcount; j++) {
						if (brick[i].x == brick[j].x && brick[i].y == brick[j].y && brick[j].id != idcount - 1) {//플레이어랑 플레이어 아닌 블럭
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
					brick[brcount].shape = random;//모양
					brick[brcount].a = a, brick[brcount].b = b, brick[brcount].c = c;//색상
					brick[brcount].x = 3, brick[brcount].y = 0;//좌표
					brick[brcount++].id = idcount++;
				}
				break;
				case 1:
					for (int i = 0; i < 2; i++)//2번 반복
					{
						brick[brcount].shape = random;
						brick[brcount].a = a, brick[brcount].b = b, brick[brcount].c = c;//색상
						brick[brcount].x = 3 - i, brick[brcount].y = 0;//좌표	
						brick[brcount++].id = idcount;
					}
					idcount++;
					break;
				case 2:
					for (int i = 0; i < 2; i++)//2번 반복
					{
						brick[brcount].shape = random;
						brick[brcount].a = a, brick[brcount].b = b, brick[brcount].c = c;//색상
						brick[brcount].x = 3, brick[brcount].y = 1 - i;//좌표	
						brick[brcount++].id = idcount;
					}
					idcount++;
					break;
				case 3:
					for (int i = 0; i < 3; i++)//2번 반복
					{
						brick[brcount].shape = random;
						brick[brcount].a = a, brick[brcount].b = b, brick[brcount].c = c;//색상
						brick[brcount].x = 3 - i, brick[brcount].y = 0;//좌표	
						brick[brcount++].id = idcount;
					}
					idcount++;
					break;
				case 4:
					for (int i = 0; i < 3; i++)//2번 반복
					{
						brick[brcount].shape = random;
						brick[brcount].a = a, brick[brcount].b = b, brick[brcount].c = c;//색상
						brick[brcount].x = 3, brick[brcount].y = 2 - i;//좌표	
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
		mdc = CreateCompatibleDC(hdc); //--- 메모리 DC 만들기
		hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom); //--- 메모리 DC와 연결할 비트맵 만들기
		SelectObject(mdc, (HBITMAP)hBitmap);


		//바탕색
		{
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
			Rectangle(mdc, 0, 0, SIDE, UP);
			SelectObject(mdc, oldBrush);
			DeleteObject(hBrush);
		}
		//보드판 그리기
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
		//블럭 그리기
		for (int i = 0; i < brcount; i++)
		{
			int x = ((2 * brick[i].x + 1) * size) / 2;
			int y = ((2 * brick[i].y + 1) * size) / 2;
			hBrush = CreateSolidBrush(RGB(brick[i].a, brick[i].b, brick[i].c));
			oldBrush = (HBRUSH)SelectObject(mdc, hBrush);
			if (brick[i].life == true) {
				Rectangle(mdc, x - size / 2, y - size / 2, x + size / 2, y + size / 2);
			}
			SelectObject(mdc, oldBrush); // 이전의 펜으로 돌아감
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
