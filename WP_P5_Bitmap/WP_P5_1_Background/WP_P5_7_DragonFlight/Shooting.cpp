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
	int x, y;
	int size;
	RECT rc;
}Player;
typedef struct {
	int x, y;
	int size;
	bool dead;
	int deadtime;
	RECT rc;
}Enemy;
typedef struct {
	int x, y;
	int size;
	RECT rc;
}Bullet;

static Player won;
static Enemy enemy[100];
static Bullet bullet[100];
static int enemyc = 0;
static int bulletc = 0;
static int bulletSize = 15;

void NewEnemy();
void NewBullet();
void DeleteBullet(int s);
void DeleteEnemy(int s);

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
	HBRUSH hbrush, oldbrush;
	HPEN hPen, oldPen;

	static CImage back1, back2, player, enemyp, dying, boom;
	static RECT rt;//
	RECT rtemp;//�浹 �˻�

	static float angle;
	static int w1, h1;//��� 1 ���� ����
	static int w2, h2;//��� 2 ���� ����
	//Ÿ�̸� �� Ÿ�̸� �ӵ�
	static int back1timer = 0;
	static int back2timer = 0;
	static int back1speed = 100;
	static int back2speed = 50;

	static int playerAnim = 0;
	static int playerSpeed = 100;
	static int enemyAnim = 0;
	static int enemySpeed = 100;

	static int boomSpeed = 200;
	static int boomAnim = 0;
	static bool wonboom = false;//�� �ִϸ��̼�

	static int bulletSpeed = 100;
	static int CreateBullet = 100;
	static int bulletcount = 100;//�Ѿ� ���� ī��Ʈ

	static int jumping = 0;//�Ѿ� ���� ī��Ʈ
	static bool wonjump = false;//�� �ִϸ��̼�
	switch (uMsg) {
	case WM_CREATE:
	{
		//�̹����ε�
		back1.Load(TEXT("Pictures/back1.jpg"));
		back2.Load(TEXT("Pictures/back2.jpg"));
		player.Load(TEXT("Pictures/PilotIdle.bmp"));
		enemyp.Load(TEXT("Pictures/Idle.bmp"));
		dying.Load(TEXT("Pictures/Lying.bmp"));
		boom.Load(TEXT("Pictures/boom.jpg"));
		GetClientRect(hwnd, &rt);
		//Ÿ�̸� ����
		SetTimer(hwnd, 1, back1speed, NULL);
		SetTimer(hwnd, 2, back2speed, NULL);
		SetTimer(hwnd, 10, playerSpeed, NULL);
		SetTimer(hwnd, 11, enemySpeed, NULL);
		SetTimer(hwnd, 12, bulletSpeed, NULL);
		SetTimer(hwnd, 13, boomSpeed, NULL);
		SetTimer(hwnd, 20, CreateBullet, NULL);
		//��� ���� �� ����
		w2 = back2.GetWidth();
		h2 = back2.GetHeight();
		w1 = back1.GetWidth();
		h1 = back1.GetHeight();
		//�ʱⰪ
		won.x = 400, won.y = WINDOWSIZE * 3 / 4, won.size = 80;
		NewEnemy();
		NewEnemy();
		NewEnemy();
		NewEnemy();
		NewEnemy();
		NewEnemy();
		NewEnemy();
		NewEnemy();
		NewEnemy();
	}
	break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1://��׶���1
		printf("x : %d y : %d\n", 150 * boomAnim % 4, 189 * boomAnim / 4);
		{
			back1timer++;
			if (back1timer > h1 / 2)
				back1timer = 0;
		}
		break;
		case 2://��׶���2
		{
			back2timer++;
			if (back2timer > h2 / 2)
				back2timer = 0;
		}
		break;
		case 10://ĳ���� �ִϸ��̼� 0~5�� �ִϸ��̼�
		{
			playerAnim++;
			if (playerAnim > 5)
				playerAnim = 0;
			if (wonjump) {
				if (jumping < 9) {
					won.size += 5;
				}
				else if (jumping >= 9 && jumping < 18) {
					won.size -= 5;
				}
				else {
					wonjump = false;
					jumping = -1;
				}
				jumping++;
			}
		}
		break;
		case 11://�� �ִϸ��̼� 0~3�� �ִϸ��̼�
		{
			enemyAnim++;
			if (enemyAnim > 3)
				enemyAnim = 0;
			for (int i = 0; i < enemyc; i++)
			{
				if (enemy[i].dead == false)
					enemy[i].y += 10;
				else {
					enemy[i].size -= 5;
					if (enemy[i].size < 0)
						DeleteEnemy(i);
				}
				if (enemy[i].y > WINDOWSIZE)
					enemy[i].y = 0;
			}
		}
		//���� �÷��̾� �浹
		{
			won.rc.left = won.x;
			won.rc.top = won.y;
			won.rc.right = won.x + won.size;
			won.rc.bottom = won.y + won.size;
			for (int i = 0; i < enemyc; i++)
			{
				enemy[i].rc.left = enemy[i].x;
				enemy[i].rc.top = enemy[i].y;
				enemy[i].rc.right = enemy[i].x + enemy[i].size;
				enemy[i].rc.bottom = enemy[i].y + enemy[i].size;
				if (IntersectRect(&rtemp, &enemy[i].rc, &won.rc) && !wonjump)
					wonboom = true;
			}
		}
		break;
		case 12://�Ѿ�
		{
			for (int i = 0; i < bulletc; i++)
			{
				bullet[i].y -= 20;
				if (bullet[i].y < 0)
					DeleteBullet(i);
			}
		}
		//���� �Ѿ� �浹
		for (int i = 0; i < enemyc; i++)
		{
			enemy[i].rc.left = enemy[i].x;
			enemy[i].rc.top = enemy[i].y;
			enemy[i].rc.right = enemy[i].x + enemy[i].size;
			enemy[i].rc.bottom = enemy[i].y + enemy[i].size;
			for (int j = 0; j < bulletc; j++)
			{
				bullet[j].rc.left = bullet[j].x;
				bullet[j].rc.top = bullet[j].y;
				bullet[j].rc.right = bullet[j].x + bullet[j].size;
				bullet[j].rc.bottom = bullet[j].y + bullet[j].size;
				if (IntersectRect(&rtemp, &enemy[i].rc, &bullet[j].rc)) {
					enemy[i].dead = true;
					DeleteBullet(j);
				}
			}
		}
		break;
		case 13://����
			if (wonboom) {
				if (boomAnim > 8) {
					boomAnim = 0;
					wonboom = false;
				}
				boomAnim++;
			}
			break;
		case 20:
		{
			if (bulletcount < 4) {
				NewBullet();
				bulletcount++;
			}
		}
		break;
		}
		InvalidateRect(hwnd, NULL, false);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		mdc = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
		(HBITMAP)SelectObject(mdc, hBitmap);
		//���
		back2.Draw(mdc, 0, 0,				WINDOWSIZE, WINDOWSIZE,			0, back2timer, w2 / 2, h2 / 2); //�� �� ���
		back1.Draw(mdc, WINDOWSIZE / 4, 0,	WINDOWSIZE * 2 / 4, WINDOWSIZE,	0, back1timer, w1, h1 / 2); //2��° ���
		//ĳ����
		for (int i = 0; i < enemyc; i++)//��
		{
			if (!enemy[i].dead) {//���� ������
				TransparentBlt(mdc, enemy[i].x, enemy[i].y, enemy[i].size, enemy[i].size, enemyp.GetDC(), 19 * enemyAnim, 0, 19, 18, RGB(235, 197, 241));
				enemyp.ReleaseDC();
			}
			else {//�׾� ������
				TransparentBlt(mdc, enemy[i].x, enemy[i].y, enemy[i].size, enemy[i].size, dying.GetDC(), 19 * enemyAnim, 0, 19, 18, RGB(235, 197, 241));
				dying.ReleaseDC();
			}
		}
		TransparentBlt(mdc, won.x, won.y, won.size, won.size, player.GetDC(), 20 * playerAnim, 0, 20, 30, RGB(144, 187, 187));//�÷��̾�
		player.ReleaseDC();
		if (wonboom) {
			TransparentBlt(mdc, won.x, won.y, won.size, won.size, boom.GetDC(), boomAnim % 4 * 150, boomAnim / 4 * 189, 150, 189, RGB(69, 86, 106));//����
			boom.ReleaseDC();
		}
		for (int i = 0; i < bulletc; i++)//�Ѿ�
		{
			hbrush = CreateSolidBrush(RGB(255, 255, 0));
			oldbrush = (HBRUSH)SelectObject(mdc, hbrush);
			Rectangle(mdc, bullet[i].x, bullet[i].y, bullet[i].x + bullet[i].size, bullet[i].y + bullet[i].size);
			SelectObject(mdc, oldbrush);
			DeleteObject(hbrush);
		}

		BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY); //--- �޸� DC�� �׸��� ȭ�� DC�� �����ϱ�

		DeleteObject(hBitmap);
		DeleteDC(mdc);
		InvalidateRect(hwnd, NULL, false);
		EndPaint(hwnd, &ps);
		break;
	case WM_CHAR:
		InvalidateRect(hwnd, NULL, false);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_LEFT && won.x > 0) {
			won.x -= 40;
		}
		if (wParam == VK_RIGHT && won.x < WINDOWSIZE - won.size) {
			won.x += 40;
		}
		if (wParam == VK_SPACE) {
			bulletcount = 0;
		}
		if (wParam == VK_UP) {
			wonjump = true;
		}
		InvalidateRect(hwnd, NULL, false);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam); //--- ���� �� �޽��� ���� ������ �޽����� OS��
}

void NewEnemy()
{
	enemy[enemyc].x = rand() % 600 + 100;
	enemy[enemyc].y = 100;
	enemy[enemyc].dead = false;
	enemy[enemyc].size = 40;
	enemyc++;
}
void NewBullet()
{
	bullet[bulletc].x = won.x + won.size / 2;
	bullet[bulletc].y = won.y;
	bullet[bulletc].size = bulletSize;
	bulletc++;
}
void DeleteEnemy(int s)
{
	for (int i = s; i < enemyc; i++)
	{
		enemy[i] = enemy[i + 1];
	}
	enemyc--;
}
void DeleteBullet(int s)
{
	for (int i = s; i < bulletc; i++)
	{
		bullet[i] = bullet[i + 1];
	}
	bulletc--;
}