#include <windows.h> 
#include <tchar.h>
#include<stdio.h>
#include<math.h>
#include <time.h>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#define WINDOWSIZE 800
#define MAXUNIT 100
#define VIRUSSIZE 20
#define TRAPSIZE 50
#define WONSIZE 10

typedef struct {
	float x, y;	//x,y
	int s;		//size x,y
	int ai;
	int c;//�и��� ī��Ʈ
	int speed;//�ӷ�
	int owner;//���̷��� �и����� ���� ��
	float px, py;//������ ������ ��� �ﰢ�Լ�
	bool devided;//���̷��� �������� �и� ����
	bool life;
}agar;

//ĳ����
static agar won;
static agar feed[MAXUNIT];
static agar virus[MAXUNIT];
static agar trap[MAXUNIT];
//�п� ĳ����
static agar dwon[MAXUNIT];
static agar dvirus[MAXUNIT * 4];
//��ü ��
static int feedc = 0;//���� ��
static int virusc = 0;//���̷��� ��
static int trapc = 0;//���� ��
static int dwonc = 0;//�п��� ĳ���� ��
static int dvirusc = 0;//�п��� �� ��ü ��

//�̵��ӵ�
static float moveSpeed = 2.5f;

//���� ���� ����
static bool start = false;
static bool stop = false;
static int camera = 1;

float GetDistance(float x1, float y1, float x2, float y2);
bool CheckCollision(float x1, float y1, float r1, float x2, float y2, float r2);

//���� �� ����
void newfeed();
void delfeed(int s);
void delVirus(int i);
//�п� �� ��ü
void devidewon(int num);
void devidevirus(int k, int num);
void deldwon(int s);
void deldvirus(int s);
void deltrap(int s);

//������ �� �ӵ� ����
void changeWonSize(int s, int size);
void changeVirusSize(int s, int i, int size);

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

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

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{//�⺻ ����
	PAINTSTRUCT ps;
	HDC hdc, mdc;
	HBRUSH hbrush, oldbrush;
	HPEN hpen, oldpen;
	static HBITMAP hBitmap;
	//���
	static RECT bg = { 0,0,WINDOWSIZE,WINDOWSIZE };
	//Ÿ�̸� �ӵ�
	static int testTimer = 100;
	static int wonTimer = 10;
	static int VirusTimer = 25;
	static int feedTimer = 3000;//3�ʿ� �ѹ� ���� �� ����
	//Ÿ�̸� ī��Ʈ
	static int spawnVirus = 0;
	static int spawnTrap = 0;
	static int swapTrapAI = 0;
	
	//���콺 ��ġ
	static int mx = -1;
	static int my = -1;
	//�̵� ����
	static float angle, moveX, moveY;

	static bool gameover = false;//
	static bool inform = false;//�÷��� Ÿ�� ����

	//UI����
	static float timer = 0;
	static TCHAR getTime[100];
	static TCHAR getSize[100];

	//���̷��� �п� ����
	int randomdevide = 0;
	switch (uMsg) {
	case WM_CREATE:
	{
		srand(time(NULL));
		//Ÿ�̸�
		SetTimer(hwnd, 0, testTimer, NULL);
		SetTimer(hwnd, 1, wonTimer, NULL);
		SetTimer(hwnd, 2, VirusTimer, NULL);
		SetTimer(hwnd, 3, feedTimer, NULL);
		//���ΰ� �ʱ� ��
		{
			won.x = WINDOWSIZE / 2, won.y = WINDOWSIZE / 2;
			won.s = WONSIZE;
		}
		//���� �ʱ� �� x,y 50~750
		for (int i = 0; i < 40; i++) {
			newfeed();
		}
		//���̷��� �ʱ� �� 0���� x,y 50~750
		{
			virus[virusc].x = rand() % (WINDOWSIZE - 100) + 50;
			virus[virusc].y = rand() % (WINDOWSIZE - 100) + 50;
			virus[virusc].devided = false;
			virus[virusc].s = VIRUSSIZE;
			virus[virusc].speed = 3-  virus[virusc].s / 20;
			virusc++;
		}
		//���� �ʱ� ��
		{
			trap[trapc].x = rand() % (WINDOWSIZE - 100) + 50;
			trap[trapc].y = rand() % (WINDOWSIZE - 100) + 50;
			trap[trapc].ai = rand() % 8;
			trap[trapc].life = true;
			trap[trapc++].s = TRAPSIZE;
		}
		//temp
	}
	break;
	case WM_TIMER:
		if (start && !stop && !gameover) {
			switch (wParam)
			{
			case 0://�׽�Ʈ��
			{
				timer+=0.1;
				//printf("gameover : %d\n", gameover);
			}
			case 1://���ΰ� �� �̵� + �п��� �̵�
			{
				angle = atan2(my - won.y, mx - won.x);
				won.x += moveSpeed * cos(angle);
				won.y += moveSpeed * sin(angle);
				//�п���
				for (int i = 0; i < dwonc; i++)
				{
					dwon[i].x += moveSpeed * cos(angle);
					dwon[i].y += moveSpeed * sin(angle);
				}
				//���� �Ա�
				for (int i = 0; i < feedc; i++)
				{
					if (CheckCollision(won.x, won.y, won.s, feed[i].x, feed[i].y, feed[i].s) == true) {
						changeWonSize(-1, 2);
						delfeed(i);
					}
				}
			}
			//���ΰ� �п��� AI
			{
				for (int i = 0; i < dwonc; i++)
				{
					dwon[i].c++;
					if (dwon[i].c > 0 && dwon[i].c < 60)//������
					{
						angle = atan2(dwon[i].y - won.y, dwon[i].x - won.x);
						dwon[i].x += (1 + dwon[i].c / 60) * cos(angle);
						dwon[i].y += (1 + dwon[i].c / 60) * sin(angle);
						dwon[i].life = false;
					}
					else if (dwon[i].c >= 60 && dwon[i].c < 200) {//�����
						dwon[i].life = true;
					}
					else if (dwon[i].c >= 200) {//��ü
						angle = atan2(dwon[i].y - won.y, dwon[i].x - won.x);
						dwon[i].x -= cos(angle);
						dwon[i].y -= sin(angle);
						dwon[i].life = true;
					}
				}
			}
			//���ΰ��� �п��� �浹
			{
				for (int i = 0; i < dwonc; i++)
				{//�浹�ϸ鼭 dwon�� life�� true�� ��(������ ������ �̻��� ��)
					if (CheckCollision(won.x, won.y, won.s, dwon[i].x, dwon[i].y, dwon[i].s) == true && dwon[i].life == true) {
						changeWonSize(i, dwon[i].s);
					}
				}
			}
			//�п����� ���� �浹
			{
				for (int i = 0; i < dwonc; i++) {
					for (int j = 0; j < feedc; j++)
					{
						if (CheckCollision(dwon[i].x, dwon[i].y, dwon[i].s, feed[j].x, feed[j].y, feed[j].s) == true) {
							dwon[i].s += 2;
							delfeed(j);
						}
					}
				}
			}
			//���� AI
			{
				for (int i = 0; i < feedc; i++)
				{
					if (feed[i].c >= 0 && feed[i].c <= 100)
						feed[i].c++;
					if (feed[i].c >= 0 && feed[i].c < 60)//���
					{
						feed[i].x += 2 * feed[i].px;
						feed[i].y += 2 * feed[i].py;
					}
				}
			}
			break;
			case 2://���̷��� 
			{
				//�п��� AI
				{
					for (int i = 0; i < dvirusc; i++)
					{
						dvirus[i].c++;
						if (dvirus[i].c > 0 && dvirus[i].c < 60)//������
						{
							angle = atan2(dvirus[i].y - virus[dvirus[i].owner].y, dvirus[i].x - virus[dvirus[i].owner].x);
							dvirus[i].x += (1 + dvirus[i].c / 60) * cos(angle);
							dvirus[i].y += (1 + dvirus[i].c / 60) * sin(angle);
							dvirus[i].life = false;
						}
						else if (dvirus[i].c >= 60 && dvirus[i].c < 200) {//�����
							dvirus[i].life = true;
						}
						else if (dvirus[i].c >= 200) {//��ü
							angle = atan2(dvirus[i].y - virus[dvirus[i].owner].y, dvirus[i].x - virus[dvirus[i].owner].x);
							dvirus[i].x -= cos(angle);
							dvirus[i].y -= sin(angle);
							dvirus[i].life = true;
						}
					}

				}

				//���� Ž�� AI, �߰� AI
				for (int i = 0; i < virusc; i++)
				{
					float min = 10000000;
					int target = 0;
					for (int j = 0; j < feedc; j++)
					{
						if (min > GetDistance(virus[i].x, virus[i].y, feed[j].x, feed[j].y)) {
							target = j;
							min = GetDistance(virus[i].x, virus[i].y, feed[j].x, feed[j].y);
						}
					}
					if (GetDistance(virus[i].x, virus[i].y, won.x, won.y) < 150) {
						angle = atan2(won.y - virus[i].y, won.x - virus[i].x);
					}
					else
						angle = atan2(feed[target].y - virus[i].y, feed[target].x - virus[i].x);
					virus[i].x += virus[i].speed * cos(angle);
					virus[i].y += virus[i].speed * sin(angle);

					//�п���
					for (int j = 0; j < dvirusc; j++)
					{
						if (i == dvirus[j].owner)
						{
							dvirus[j].x += virus[i].speed * cos(angle);
							dvirus[j].y += virus[i].speed * sin(angle);
						}
					}
				}
				//���̿� ���̷��� �浹 - ���̻��� ��
				for (int i = 0; i < virusc; i++) {
					for (int j = 0; j < feedc; j++)
					{
						if (CheckCollision(virus[i].x, virus[i].y, virus[i].s, feed[j].x, feed[j].y, feed[j].s) == true) {
							changeVirusSize(-1, i, 2);
							delfeed(j);
						}
					}
				}
				//�÷��̾�� ���̷��� �浹
				for (int i = 0; i < virusc; i++) {
					if (CheckCollision(virus[i].x, virus[i].y, virus[i].s, won.x, won.y, won.s) == true) {
						if (won.s >= virus[i].s) {//�÷��̾ �� ũ��
							changeWonSize(-1, virus[i].s);//���̷��� �������� ���ݸ�ŭ ����
							delVirus(i);
						}
						else {
							gameover = true;
						}
					}
				}
				for (int x = 0; x < virusc; x++)
				{
					for (int y = 0; y < virusc; y++)
					{
						if (x == y)
							y++;
						if (CheckCollision(virus[x].x, virus[x].y, virus[x].s, virus[y].x, virus[y].y, virus[y].s) == true) {
							changeVirusSize(-1, x, virus[y].s);
							delVirus(y);
						}
					}
				}
				//�÷��̾� �п����� ���̷��� �浹
				{
					for (int i = 0; i < virusc; i++) {
						for (int j = 0; j < dwonc; j++)
						{
							if (CheckCollision(virus[i].x, virus[i].y, virus[i].s, dwon[j].x, dwon[j].y, dwon[j].s) == true) {
								changeVirusSize(-1, i, dwon[j].s);
								deldwon(j);
							}
						}
					}
				}
				//dvirus - �÷��̾�
				{
					for (int i = 0; i < dvirusc; i++) {
						if (CheckCollision(dvirus[i].x, dvirus[i].y, dvirus[i].s, won.x, won.y, won.s) == true) {
							if (won.s >= dvirus[i].s) {//�÷��̾ �� ũ��
								changeWonSize(-1, dvirus[i].s);//���̷��� �������� ���ݸ�ŭ ����
								deldvirus(i);
							}
							else {
								gameover = true;
							}
						}
					}
				}
				//dvirus - ����
				{
					for (int i = 0; i < dvirusc; i++) {
						for (int j = 0; j < feedc; j++)
						{
							if (CheckCollision(dvirus[i].x, dvirus[i].y, dvirus[i].s, feed[j].x, feed[j].y, feed[j].s) == true) {
								dvirus[i].s += 2;
								delfeed(j);
							}
						}
					}
				}
				//dvirus - ���̷���
				{
					for (int j = 0; j < virusc; j++)
					{
						for (int i = 0; i < dvirusc; i++)
						{//�浹�ϸ鼭 dvirus�� life�� true�� ��(������ ������ �̻��� ��)
							if (CheckCollision(virus[j].x, virus[j].y, virus[j].s, dvirus[i].x, dvirus[i].y, dvirus[i].s) == true && dvirus[i].life == true) {
								changeVirusSize(i, j, dvirus[i].s);
							}
						}
					}

				}
				//dvirus - dwon
				{
					for (int i = 0; i < dvirusc; i++) {
						for (int j = 0; j < dwonc; j++)
						{
							if (CheckCollision(dvirus[i].x, dvirus[i].y, dvirus[i].s, dwon[j].x, dwon[j].y, dwon[j].s) == true) {
								dvirus[i].s += dwon[j].s;
								deldwon(j);
							}
						}
					}
				}
				//���̷����� ũ�� �п�
				for (int i = 0; i < virusc; i++)
				{
					if (virus[i].s > 100 && virus[i].devided == false) {
						randomdevide = rand() % 2;
						if (randomdevide == 1) {
							virus[i].devided = true;
							devidevirus(i, 3);
						}
						else
							virus[i].devided = true;
					}
				}
				spawnVirus++;//����Ÿ�̸�, ���̷��� ����
				if (spawnVirus % 200 == 0) {
					virus[virusc].x = rand() % (WINDOWSIZE - 100) + 50;
					virus[virusc].y = rand() % (WINDOWSIZE - 100) + 50;
					virus[virusc].devided = false;
					virus[virusc].s = VIRUSSIZE;
					virus[virusc].speed = 3 - virus[virusc].s / 20;
					virusc++;
				}
			}
			//����
			{
				spawnTrap++;
				swapTrapAI++;
				//���� ai ü����
				if (swapTrapAI % 150 == 0) {
					for (int i = 0; i < trapc; i++) {//ai ��� �������� �ٲٱ�
						trap[i].ai = rand() % 8;
					}
				}
				//���� + �ִϸ��̼�
				{
					if (spawnTrap == 150) {//TODO : �ִϸ��̼�
						trap[trapc].x = rand() % (WINDOWSIZE - 100) + 50;
						trap[trapc].y = rand() % (WINDOWSIZE - 100) + 50;
						trap[trapc].ai = rand() % 8;
						trap[trapc].life = false;
						trap[trapc++].s = TRAPSIZE * 1.4;
					}
					if (spawnTrap == 200) {
						trap[trapc - 1].s = TRAPSIZE * 1.2;
					}
					if (spawnTrap == 250) {
						trap[trapc - 1].s = TRAPSIZE * 1.1;
					}
					if (spawnTrap > 300)
					{
						trap[trapc - 1].s = TRAPSIZE;
						trap[trapc - 1].life = true;
						spawnTrap = 0;
					}
				}

				//AI
				{
					for (int i = 0; i < trapc; i++)//ai�� ���� ������, Ÿ�̸ӷ� ai ��� ���� ������
					{
						if (trap[i].life == false) {
							i++;
							continue;
						}
						switch (trap[i].ai)
						{
						case 0://��
							if (trap[i].y > trap[i].s)
								trap[i].y--;
							break;
						case 1://�����
							if (trap[i].y > trap[i].s)
								trap[i].y--;
							if (trap[i].x < WINDOWSIZE - trap[i].s)
								trap[i].x++;
							break;
						case 2://��
							if (trap[i].x < WINDOWSIZE - trap[i].s)
								trap[i].x++;
							break;
						case 3://������
							if (trap[i].y < WINDOWSIZE - trap[i].s)
								trap[i].y++;
							if (trap[i].x < WINDOWSIZE - trap[i].s)
								trap[i].x++;
							break;
						case 4://��
							if (trap[i].y < WINDOWSIZE - trap[i].s)
								trap[i].y++;
							break;
						case 5://������
							if (trap[i].y < WINDOWSIZE - trap[i].s)
								trap[i].y++;
							if (trap[i].x > trap[i].s)
								trap[i].x--;
							break;
						case 6://��
							if (trap[i].x > trap[i].s)
								trap[i].x--;
							break;
						case 7://�»���
							if (trap[i].y > trap[i].s)
								trap[i].y--;
							if (trap[i].x > trap[i].s)
								trap[i].x--;
							break;
						default:
							break;
						}
					}
				}
				//�浹
				{
					//���̷����� ����
					for (int i = 0; i < virusc; i++) {
						for (int j = 0; j < trapc; j++)
						{
							if (trap[j].life == false) {//������ ���� ���� �ȵ����� ++�ؼ� �˻� ����
								j++;
								continue;
							}
							if (CheckCollision(virus[i].x, virus[i].y, virus[i].s, trap[j].x, trap[j].y, trap[j].s) == true
								&& virus[i].s > trap[j].s) {//���̷����� �� ũ��
								devidevirus(i, 3);
								deltrap(j);
							}
						}
					}
					//�÷��̾�� ����
					for (int i = 0; i < trapc; i++) {
						if (trap[i].life == false) {//������ ���� ���� �ȵ����� ++�ؼ� �˻� ����
							i++;
							continue;
						}
						if (CheckCollision(trap[i].x, trap[i].y, trap[i].s, won.x, won.y, won.s) == true
							&& won.s > trap[i].s) {
							devidewon(3);
							deltrap(i);
						}
					}

				}

			}
			break;
			case 3://���� ������ ����
				for (int i = 0; i < 10; i++)
				{
					if (feedc > 40)
						delfeed(rand() % feedc);
					newfeed();
				}
				break;
			default:
				break;
			}
		}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_PAINT:
	{
		//�⺻ ��
		hdc = BeginPaint(hwnd, &ps);
		mdc = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, bg.right, bg.bottom);
		SelectObject(mdc, (HBITMAP)hBitmap);
		//���
		{
			hbrush = CreateSolidBrush(RGB(255, 255, 255));
			oldbrush = (HBRUSH)SelectObject(mdc, hbrush);
			FillRect(mdc, &bg, hbrush);
			SelectObject(mdc, oldbrush);
			DeleteObject(hbrush);
			for (int y = 0; y < WINDOWSIZE / 40; y++)
			{
				MoveToEx(mdc, y * 40, 0, NULL);
				LineTo(mdc, y * 40, WINDOWSIZE);
			}
			for (int x = 0; x < WINDOWSIZE / 40; x++)
			{
				MoveToEx(mdc, 0, x * 40, NULL);
				LineTo(mdc, WINDOWSIZE, x * 40);
			}
		}
		//ĳ����
		{
			//����
			{
				hbrush = CreateSolidBrush(RGB(0, 200, 200));
				oldbrush = (HBRUSH)SelectObject(mdc, hbrush);
				for (int i = 0; i < feedc; i++) {
					Ellipse(mdc, feed[i].x - feed[i].s, feed[i].y - feed[i].s, feed[i].x + feed[i].s, feed[i].y + feed[i].s);
				}
				SelectObject(mdc, oldbrush);
				DeleteObject(hbrush);
			}

			//���̷���
			{
				hbrush = CreateSolidBrush(RGB(255, 50, 50));
				oldbrush = (HBRUSH)SelectObject(mdc, hbrush);
				for (int i = 0; i < dvirusc; i++) {//�п���
					Ellipse(mdc, dvirus[i].x - dvirus[i].s, dvirus[i].y - dvirus[i].s, dvirus[i].x + dvirus[i].s, dvirus[i].y + dvirus[i].s);
				}
				for (int i = 0; i < virusc; i++) {
					Ellipse(mdc, virus[i].x - virus[i].s, virus[i].y - virus[i].s, virus[i].x + virus[i].s, virus[i].y + virus[i].s);
				}
				SelectObject(mdc, oldbrush);
				DeleteObject(hbrush);
			}
			//���ΰ���
			{
				hbrush = CreateSolidBrush(RGB(255, 255, 0));
				oldbrush = (HBRUSH)SelectObject(mdc, hbrush);
				for (int i = 0; i < dwonc; i++) {//�п���
					Ellipse(mdc, dwon[i].x - dwon[i].s, dwon[i].y - dwon[i].s, dwon[i].x + dwon[i].s, dwon[i].y + dwon[i].s);
				}
				Ellipse(mdc, won.x - won.s, won.y - won.s, won.x + won.s, won.y + won.s);
				SelectObject(mdc, oldbrush);
				DeleteObject(hbrush);
			}

			//Ʈ��
			{
				for (int i = 0; i < trapc; i++) {
					if (trap[i].life == true) {
						hbrush = CreateHatchBrush(HS_DIAGCROSS, RGB(50, 50, 255));
						oldbrush = (HBRUSH)SelectObject(mdc, hbrush);
					}
					else{
						hbrush = CreateHatchBrush(HS_DIAGCROSS, RGB(50, 255, 50));
						oldbrush = (HBRUSH)SelectObject(mdc, hbrush);
					}
					Ellipse(mdc, trap[i].x - trap[i].s, trap[i].y - trap[i].s, trap[i].x + trap[i].s, trap[i].y + trap[i].s);
					SelectObject(mdc, oldbrush);
					DeleteObject(hbrush);

					if (trap[i].life == true) {
						hbrush = CreateSolidBrush(RGB(50, 255, 255));
						oldbrush = (HBRUSH)SelectObject(mdc, hbrush);
					}
					else {
						hbrush = CreateSolidBrush(RGB(255, 30, 30));
						oldbrush = (HBRUSH)SelectObject(mdc, hbrush);
					}
					Ellipse(mdc, trap[i].x - trap[i].s / 2, trap[i].y - trap[i].s / 2, trap[i].x + trap[i].s / 2, trap[i].y + trap[i].s / 2);
					SelectObject(mdc, oldbrush);
					DeleteObject(hbrush);
				}

			}

		}
		//�ؽ�Ʈ
		{

			if (camera == 1) {//��Ŀ�� ȭ��
				if (gameover == true) {


					TextOut(mdc, 350, 380, L"GameOver", lstrlen(L"GameOver"));
					_stprintf_s(getTime, L"�ð� : %.2f��", timer);
					TextOut(mdc, 350, 400, getTime, lstrlen(getTime));
					wsprintf(getSize, L"���� ũ�� : %d", won.s);
					TextOut(mdc, 350, 420, getSize, lstrlen(getSize));
					BitBlt(hdc, 0, 0, bg.right, bg.bottom, mdc, 0, 0, SRCCOPY);//��üȭ��
				}
				else {
					//�ð�
					if (inform) {
						_stprintf_s(getTime, L"�ð� : %.2f��", timer);
						TextOut(mdc, won.x - 1.2 * won.s - 80, won.y - 1.2 * won.s - 80, getTime, lstrlen(getTime));
						wsprintf(getSize, L"���� ũ�� : %d", won.s);
						TextOut(mdc, won.x - 1.2 * won.s - 80, won.y - 1.2 * won.s - 80 + 20, getSize, lstrlen(getSize));
					}
					StretchBlt(hdc, 0, 0, bg.right, bg.bottom, mdc, won.x - 1.2 * won.s - 80, won.y - 1.2 * won.s - 80, 2.4 * won.s + 160, 2.4 * won.s + 160, SRCCOPY);//��Ŀ��ȭ��
				}
			}
			else if (camera == 2) {//��ü ȭ��
				if (gameover == true) {
					TextOut(mdc, 350, 380, L"GameOver", lstrlen(L"GameOver"));
					_stprintf_s(getTime, L"�ð� : %.2f��", timer);
					TextOut(mdc, 350, 400, getTime, lstrlen(getTime));
					wsprintf(getSize, L"���� ũ�� : %d", won.s);
					TextOut(mdc, 350, 420, getSize, lstrlen(getSize));
				}
				else {
					//�ð�
					if (inform) {
						_stprintf_s(getTime, L"�ð� : %.2f��", timer);
						TextOut(mdc, 10, 10, getTime, lstrlen(getTime));
						wsprintf(getSize, L"���� ũ�� : %d", won.s);
						TextOut(mdc, 10, 40, getSize, lstrlen(getSize));
					}
				}
				BitBlt(hdc, 0, 0, bg.right, bg.bottom, mdc, 0, 0, SRCCOPY);//��üȭ��
			}
		}
		DeleteDC(mdc);
		DeleteObject(hBitmap);
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_MOUSEMOVE:
	{
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		InvalidateRect(hwnd, NULL, FALSE);
	}
		break;
	case WM_CHAR:
		if (wParam == 'a') {
			
		}
		if (wParam == 'n') {
			start = true;
		}
		if (wParam == 's') {
			if (!stop)
				stop = true;
			else
				stop = false;
		}
		if (wParam == '1') {
			camera = 1;
		}
		if (wParam == '2') {
			camera = 2;
		}
		if (wParam == 'q') {
			gameover = true;
		}
		if (wParam == 'p') {
			if (inform)
				inform = false;
			else
				inform = true;
		}
		if (wParam == 'r') {
			feedc = 0;//���� ��
			virusc = 0;//���̷��� ��
			trapc = 0;//���� ��
			dwonc = 0;//�п��� ĳ���� ��
			dvirusc = 0;//�п��� �� ��ü ��
			 start = false;
			 stop = false;
			camera = 1;
			//���ΰ� �ʱ� ��
			{
				won.x = WINDOWSIZE / 2, won.y = WINDOWSIZE / 2;
				won.s = WONSIZE;
			}
			//���� �ʱ� �� x,y 50~750
			for (int i = 0; i < 40; i++) {
				newfeed();
			}
			//���̷��� �ʱ� �� 0���� x,y 50~750
			{
				virus[virusc].x = rand() % (WINDOWSIZE - 100) + 50;
				virus[virusc].y = rand() % (WINDOWSIZE - 100) + 50;
				virus[virusc].devided = false;
				virus[virusc].s = VIRUSSIZE;
				virus[virusc].speed = 3 -  virus[virusc].s / 20;
				virusc++;
			}
			//���� �ʱ� ��
			{
				trap[trapc].x = rand() % (WINDOWSIZE - 100) + 50;
				trap[trapc].y = rand() % (WINDOWSIZE - 100) + 50;
				trap[trapc].ai = rand() % 8;
				trap[trapc].life = true;
				trap[trapc++].s = TRAPSIZE;
			}
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_LEFT) {
			
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break;
	case WM_LBUTTONDOWN:
	{//����� 20���� ������ �п� ����
		if (won.s < 20) {
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		}
		//���ΰ��� ������ ����
		won.s = won.s / 2;

		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		angle = atan2(my - won.y, mx - won.x);

		//���ΰ��� �и��� ����
		dwon[dwonc].x = won.x + won.s * cos(angle);
		dwon[dwonc].y = won.y + won.s * sin(angle);
		dwon[dwonc].s = won.s;
		dwon[dwonc++].c = 0;

	}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_RBUTTONDOWN:
	{//����� 20���� ������ ���� �߽� ����
		if (won.s < 20) {
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		}
		won.s -= 2;

		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		angle = atan2(my - won.y, mx - won.x);

		if (feedc >= MAXUNIT)
			break;

		//���ΰ��� �и��� ����
		feed[feedc].x = won.x + 1.5 * (won.s * cos(angle));
		feed[feedc].y = won.y + 1.5 * (won.s * sin(angle));

		feed[feedc].px = cos(angle);
		feed[feedc].py = sin(angle);
		feed[feedc].s = 5;
		feed[feedc].c = 0;
		feed[feedc].life = false;
		feedc++;
	}

	InvalidateRect(hwnd, NULL, FALSE);
	break;
	case WM_DESTROY:
		DeleteObject(hBitmap);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam); //--- ���� �� �޽��� ���� ������ �޽����� OS��
}

float GetDistance(float x1, float y1, float x2, float y2) {
	float distance = sqrt(pow(fabs(y2 - y1), 2) + pow(fabs(x2 - x1), 2));
	return distance;
}
bool CheckCollision(float x1, float y1, float r1, float x2, float y2, float r2)
{
	// �� ���� �߽� ��ǥ ���� �Ÿ� ���
	float distX = x1 - x2;
	float distY = y1 - y2;
	float distance = sqrt(distX * distX + distY * distY);

	// �� ���� �������� �� ���
	float Radius = r1 + r2;

	// �浹 �˻�
	if (distance <= Radius) {
		// �浹�� ���
		return true;
	}
	else {
		// �浹���� ���� ���
		return false;
	}
}
void newfeed()
{
	if (feedc >= MAXUNIT)
		return;
	feed[feedc].x = rand() % (WINDOWSIZE - 100) + 50;
	feed[feedc].y = rand() % (WINDOWSIZE - 100) + 50;
	feed[feedc].s = 5;
	feed[feedc].c = -1;
	feed[feedc].life = -1;
	feedc++;
}
void delfeed(int s) {
	for (int i = s; i < feedc; i++)
	{
		feed[i] = feed[i + 1];
	}
	feedc--;
}
void delVirus(int s)
{
	for (int i = s; i < virusc; i++)
	{
		virus[i] = virus[i + 1];
	}
	virusc--;
}
void deltrap(int s)
{
	for (int i = s; i < virusc; i++)
	{
		trap[i] = trap[i + 1];
	}
	trapc--;
}
void changeWonSize(int s, int size)
{//true : size++ false : size--
	if (s >= 0)//-1�̸� �п��� ���� ���� ����
		deldwon(s);

	won.s += size;
	moveSpeed = 3 - won.s / 20;

	if (moveSpeed < 1) {
		moveSpeed = 1;
	}
}
void changeVirusSize(int s, int i, int size)
{
	if (s >= 0)
		deldvirus(s);

	virus[i].s += size;
	virus[i].speed = 3 - virus[i].s/20;

	if (virus[i].speed < 1) {
		virus[i].speed = 1;
	}
}
void devidewon(int num)//�п� ����
{
	//���ΰ��� ������ ����
	won.s = won.s / (num + 1);
	moveSpeed = 3 - won.s / 20;
	//���ΰ��� �и��� ����
	for (int i = 0; i < num; i++)
	{
		dwon[dwonc].x = won.x + 2 * (rand() % (2 * won.s) - won.s);
		dwon[dwonc].y = won.y + 2 * (rand() % (2 * won.s) - won.s);
		dwon[dwonc].s = won.s;
		dwon[dwonc].life = false;
		dwon[dwonc++].c = 0;
	}
	if (moveSpeed < 1) {
		moveSpeed = 1;
	}
}
void devidevirus(int k, int num)// k :��� �� ���̷�������
{
	virus[k].s = virus[k].s / (num + 1);
	virus[k].speed = 3 - virus[k].s / 20;
	for (int i = 0; i < num; i++)
	{
		dvirus[dvirusc].x = virus[k].x + 2 * (rand() % (2 * virus[k].s) - virus[k].s);
		dvirus[dvirusc].y = virus[k].y + 2 * (rand() % (2 * virus[k].s) - virus[k].s);
		dvirus[dvirusc].s = virus[k].s;
		dvirus[dvirusc].life = false;
		dvirus[dvirusc].owner = k;
		dvirus[dvirusc++].c = 0;
	}
}
void deldwon(int s)//-1�̸� ���� ����
{
	if (s == -1) {
		return;
	}
	for (int i = s; i < dwonc; i++)
	{
		dwon[i] = dwon[i + 1];
	}
	dwonc--;
}
void deldvirus(int s)//-1�̸� ���� ����
{
	if (s == -1) {
		return;
	}
	for (int i = s; i < dvirusc; i++)
	{
		dvirus[i] = dvirus[i + 1];
	}
	dvirusc--;
}