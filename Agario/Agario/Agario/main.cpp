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
	int c;//분리원 카운트
	int speed;//속력
	int owner;//바이러스 분리원의 원래 원
	float px, py;//던져진 먹이의 출발 삼각함수
	bool devided;//바이러스 랜덤으로 분리 여부
	bool life;
}agar;

//캐릭터
static agar won;
static agar feed[MAXUNIT];
static agar virus[MAXUNIT];
static agar trap[MAXUNIT];
//분열 캐릭터
static agar dwon[MAXUNIT];
static agar dvirus[MAXUNIT * 4];
//개체 수
static int feedc = 0;//먹이 수
static int virusc = 0;//바이러스 수
static int trapc = 0;//함정 수
static int dwonc = 0;//분열된 캐릭터 수
static int dvirusc = 0;//분열된 적 개체 수

//이동속도
static float moveSpeed = 2.5f;

//게임 시작 관련
static bool start = false;
static bool stop = false;
static int camera = 1;

float GetDistance(float x1, float y1, float x2, float y2);
bool CheckCollision(float x1, float y1, float r1, float x2, float y2, float r2);

//생성 및 삭제
void newfeed();
void delfeed(int s);
void delVirus(int i);
//분열 및 합체
void devidewon(int num);
void devidevirus(int k, int num);
void deldwon(int s);
void deldvirus(int s);
void deltrap(int s);

//사이즈 및 속도 변경
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
{//기본 선언
	PAINTSTRUCT ps;
	HDC hdc, mdc;
	HBRUSH hbrush, oldbrush;
	HPEN hpen, oldpen;
	static HBITMAP hBitmap;
	//배경
	static RECT bg = { 0,0,WINDOWSIZE,WINDOWSIZE };
	//타이머 속도
	static int testTimer = 100;
	static int wonTimer = 10;
	static int VirusTimer = 25;
	static int feedTimer = 3000;//3초에 한번 삭제 후 생성
	//타이머 카운트
	static int spawnVirus = 0;
	static int spawnTrap = 0;
	static int swapTrapAI = 0;
	
	//마우스 위치
	static int mx = -1;
	static int my = -1;
	//이동 변수
	static float angle, moveX, moveY;

	static bool gameover = false;//
	static bool inform = false;//플레이 타임 정보

	//UI변수
	static float timer = 0;
	static TCHAR getTime[100];
	static TCHAR getSize[100];

	//바이러스 분열 여부
	int randomdevide = 0;
	switch (uMsg) {
	case WM_CREATE:
	{
		srand(time(NULL));
		//타이머
		SetTimer(hwnd, 0, testTimer, NULL);
		SetTimer(hwnd, 1, wonTimer, NULL);
		SetTimer(hwnd, 2, VirusTimer, NULL);
		SetTimer(hwnd, 3, feedTimer, NULL);
		//주인공 초기 값
		{
			won.x = WINDOWSIZE / 2, won.y = WINDOWSIZE / 2;
			won.s = WONSIZE;
		}
		//먹이 초기 값 x,y 50~750
		for (int i = 0; i < 40; i++) {
			newfeed();
		}
		//바이러스 초기 값 0번에 x,y 50~750
		{
			virus[virusc].x = rand() % (WINDOWSIZE - 100) + 50;
			virus[virusc].y = rand() % (WINDOWSIZE - 100) + 50;
			virus[virusc].devided = false;
			virus[virusc].s = VIRUSSIZE;
			virus[virusc].speed = 3-  virus[virusc].s / 20;
			virusc++;
		}
		//함정 초기 값
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
			case 0://테스트용
			{
				timer+=0.1;
				//printf("gameover : %d\n", gameover);
			}
			case 1://주인공 원 이동 + 분열원 이동
			{
				angle = atan2(my - won.y, mx - won.x);
				won.x += moveSpeed * cos(angle);
				won.y += moveSpeed * sin(angle);
				//분열원
				for (int i = 0; i < dwonc; i++)
				{
					dwon[i].x += moveSpeed * cos(angle);
					dwon[i].y += moveSpeed * sin(angle);
				}
				//먹이 먹기
				for (int i = 0; i < feedc; i++)
				{
					if (CheckCollision(won.x, won.y, won.s, feed[i].x, feed[i].y, feed[i].s) == true) {
						changeWonSize(-1, 2);
						delfeed(i);
					}
				}
			}
			//주인공 분열원 AI
			{
				for (int i = 0; i < dwonc; i++)
				{
					dwon[i].c++;
					if (dwon[i].c > 0 && dwon[i].c < 60)//나가기
					{
						angle = atan2(dwon[i].y - won.y, dwon[i].x - won.x);
						dwon[i].x += (1 + dwon[i].c / 60) * cos(angle);
						dwon[i].y += (1 + dwon[i].c / 60) * sin(angle);
						dwon[i].life = false;
					}
					else if (dwon[i].c >= 60 && dwon[i].c < 200) {//대기대기
						dwon[i].life = true;
					}
					else if (dwon[i].c >= 200) {//합체
						angle = atan2(dwon[i].y - won.y, dwon[i].x - won.x);
						dwon[i].x -= cos(angle);
						dwon[i].y -= sin(angle);
						dwon[i].life = true;
					}
				}
			}
			//주인공과 분열원 충돌
			{
				for (int i = 0; i < dwonc; i++)
				{//충돌하면서 dwon의 life가 true일 때(나오고 대기상태 이상일 때)
					if (CheckCollision(won.x, won.y, won.s, dwon[i].x, dwon[i].y, dwon[i].s) == true && dwon[i].life == true) {
						changeWonSize(i, dwon[i].s);
					}
				}
			}
			//분열원과 먹이 충돌
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
			//먹이 AI
			{
				for (int i = 0; i < feedc; i++)
				{
					if (feed[i].c >= 0 && feed[i].c <= 100)
						feed[i].c++;
					if (feed[i].c >= 0 && feed[i].c < 60)//출발
					{
						feed[i].x += 2 * feed[i].px;
						feed[i].y += 2 * feed[i].py;
					}
				}
			}
			break;
			case 2://바이러스 
			{
				//분열원 AI
				{
					for (int i = 0; i < dvirusc; i++)
					{
						dvirus[i].c++;
						if (dvirus[i].c > 0 && dvirus[i].c < 60)//나가기
						{
							angle = atan2(dvirus[i].y - virus[dvirus[i].owner].y, dvirus[i].x - virus[dvirus[i].owner].x);
							dvirus[i].x += (1 + dvirus[i].c / 60) * cos(angle);
							dvirus[i].y += (1 + dvirus[i].c / 60) * sin(angle);
							dvirus[i].life = false;
						}
						else if (dvirus[i].c >= 60 && dvirus[i].c < 200) {//대기대기
							dvirus[i].life = true;
						}
						else if (dvirus[i].c >= 200) {//합체
							angle = atan2(dvirus[i].y - virus[dvirus[i].owner].y, dvirus[i].x - virus[dvirus[i].owner].x);
							dvirus[i].x -= cos(angle);
							dvirus[i].y -= sin(angle);
							dvirus[i].life = true;
						}
					}

				}

				//먹이 탐색 AI, 추격 AI
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

					//분열원
					for (int j = 0; j < dvirusc; j++)
					{
						if (i == dvirus[j].owner)
						{
							dvirus[j].x += virus[i].speed * cos(angle);
							dvirus[j].y += virus[i].speed * sin(angle);
						}
					}
				}
				//먹이와 바이러스 충돌 - 먹이생성 뺌
				for (int i = 0; i < virusc; i++) {
					for (int j = 0; j < feedc; j++)
					{
						if (CheckCollision(virus[i].x, virus[i].y, virus[i].s, feed[j].x, feed[j].y, feed[j].s) == true) {
							changeVirusSize(-1, i, 2);
							delfeed(j);
						}
					}
				}
				//플레이어와 바이러스 충돌
				for (int i = 0; i < virusc; i++) {
					if (CheckCollision(virus[i].x, virus[i].y, virus[i].s, won.x, won.y, won.s) == true) {
						if (won.s >= virus[i].s) {//플레이어가 더 크면
							changeWonSize(-1, virus[i].s);//바이러스 사이즈의 절반만큼 성장
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
				//플레이어 분열원과 바이러스 충돌
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
				//dvirus - 플레이어
				{
					for (int i = 0; i < dvirusc; i++) {
						if (CheckCollision(dvirus[i].x, dvirus[i].y, dvirus[i].s, won.x, won.y, won.s) == true) {
							if (won.s >= dvirus[i].s) {//플레이어가 더 크면
								changeWonSize(-1, dvirus[i].s);//바이러스 사이즈의 절반만큼 성장
								deldvirus(i);
							}
							else {
								gameover = true;
							}
						}
					}
				}
				//dvirus - 먹이
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
				//dvirus - 바이러스
				{
					for (int j = 0; j < virusc; j++)
					{
						for (int i = 0; i < dvirusc; i++)
						{//충돌하면서 dvirus의 life가 true일 때(나오고 대기상태 이상일 때)
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
				//바이러스가 크면 분열
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
				spawnVirus++;//생성타이머, 바이러스 생성
				if (spawnVirus % 200 == 0) {
					virus[virusc].x = rand() % (WINDOWSIZE - 100) + 50;
					virus[virusc].y = rand() % (WINDOWSIZE - 100) + 50;
					virus[virusc].devided = false;
					virus[virusc].s = VIRUSSIZE;
					virus[virusc].speed = 3 - virus[virusc].s / 20;
					virusc++;
				}
			}
			//함정
			{
				spawnTrap++;
				swapTrapAI++;
				//함정 ai 체인지
				if (swapTrapAI % 150 == 0) {
					for (int i = 0; i < trapc; i++) {//ai 계속 랜덤으로 바꾸기
						trap[i].ai = rand() % 8;
					}
				}
				//생성 + 애니메이션
				{
					if (spawnTrap == 150) {//TODO : 애니메이션
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
					for (int i = 0; i < trapc; i++)//ai에 따라 움직임, 타이머로 ai 계속 랜덤 돌리기
					{
						if (trap[i].life == false) {
							i++;
							continue;
						}
						switch (trap[i].ai)
						{
						case 0://위
							if (trap[i].y > trap[i].s)
								trap[i].y--;
							break;
						case 1://우상향
							if (trap[i].y > trap[i].s)
								trap[i].y--;
							if (trap[i].x < WINDOWSIZE - trap[i].s)
								trap[i].x++;
							break;
						case 2://우
							if (trap[i].x < WINDOWSIZE - trap[i].s)
								trap[i].x++;
							break;
						case 3://우하향
							if (trap[i].y < WINDOWSIZE - trap[i].s)
								trap[i].y++;
							if (trap[i].x < WINDOWSIZE - trap[i].s)
								trap[i].x++;
							break;
						case 4://하
							if (trap[i].y < WINDOWSIZE - trap[i].s)
								trap[i].y++;
							break;
						case 5://좌하향
							if (trap[i].y < WINDOWSIZE - trap[i].s)
								trap[i].y++;
							if (trap[i].x > trap[i].s)
								trap[i].x--;
							break;
						case 6://좌
							if (trap[i].x > trap[i].s)
								trap[i].x--;
							break;
						case 7://좌상향
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
				//충돌
				{
					//바이러스와 함정
					for (int i = 0; i < virusc; i++) {
						for (int j = 0; j < trapc; j++)
						{
							if (trap[j].life == false) {//함정이 아직 생성 안됐으면 ++해서 검사 안함
								j++;
								continue;
							}
							if (CheckCollision(virus[i].x, virus[i].y, virus[i].s, trap[j].x, trap[j].y, trap[j].s) == true
								&& virus[i].s > trap[j].s) {//바이러스가 더 크면
								devidevirus(i, 3);
								deltrap(j);
							}
						}
					}
					//플레이어와 함정
					for (int i = 0; i < trapc; i++) {
						if (trap[i].life == false) {//함정이 아직 생성 안됐으면 ++해서 검사 안함
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
			case 3://먹이 생성및 삭제
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
		//기본 값
		hdc = BeginPaint(hwnd, &ps);
		mdc = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, bg.right, bg.bottom);
		SelectObject(mdc, (HBITMAP)hBitmap);
		//배경
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
		//캐릭터
		{
			//먹이
			{
				hbrush = CreateSolidBrush(RGB(0, 200, 200));
				oldbrush = (HBRUSH)SelectObject(mdc, hbrush);
				for (int i = 0; i < feedc; i++) {
					Ellipse(mdc, feed[i].x - feed[i].s, feed[i].y - feed[i].s, feed[i].x + feed[i].s, feed[i].y + feed[i].s);
				}
				SelectObject(mdc, oldbrush);
				DeleteObject(hbrush);
			}

			//바이러스
			{
				hbrush = CreateSolidBrush(RGB(255, 50, 50));
				oldbrush = (HBRUSH)SelectObject(mdc, hbrush);
				for (int i = 0; i < dvirusc; i++) {//분열원
					Ellipse(mdc, dvirus[i].x - dvirus[i].s, dvirus[i].y - dvirus[i].s, dvirus[i].x + dvirus[i].s, dvirus[i].y + dvirus[i].s);
				}
				for (int i = 0; i < virusc; i++) {
					Ellipse(mdc, virus[i].x - virus[i].s, virus[i].y - virus[i].s, virus[i].x + virus[i].s, virus[i].y + virus[i].s);
				}
				SelectObject(mdc, oldbrush);
				DeleteObject(hbrush);
			}
			//주인공원
			{
				hbrush = CreateSolidBrush(RGB(255, 255, 0));
				oldbrush = (HBRUSH)SelectObject(mdc, hbrush);
				for (int i = 0; i < dwonc; i++) {//분열원
					Ellipse(mdc, dwon[i].x - dwon[i].s, dwon[i].y - dwon[i].s, dwon[i].x + dwon[i].s, dwon[i].y + dwon[i].s);
				}
				Ellipse(mdc, won.x - won.s, won.y - won.s, won.x + won.s, won.y + won.s);
				SelectObject(mdc, oldbrush);
				DeleteObject(hbrush);
			}

			//트랩
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
		//텍스트
		{

			if (camera == 1) {//포커스 화면
				if (gameover == true) {


					TextOut(mdc, 350, 380, L"GameOver", lstrlen(L"GameOver"));
					_stprintf_s(getTime, L"시간 : %.2f초", timer);
					TextOut(mdc, 350, 400, getTime, lstrlen(getTime));
					wsprintf(getSize, L"세포 크기 : %d", won.s);
					TextOut(mdc, 350, 420, getSize, lstrlen(getSize));
					BitBlt(hdc, 0, 0, bg.right, bg.bottom, mdc, 0, 0, SRCCOPY);//전체화면
				}
				else {
					//시간
					if (inform) {
						_stprintf_s(getTime, L"시간 : %.2f초", timer);
						TextOut(mdc, won.x - 1.2 * won.s - 80, won.y - 1.2 * won.s - 80, getTime, lstrlen(getTime));
						wsprintf(getSize, L"세포 크기 : %d", won.s);
						TextOut(mdc, won.x - 1.2 * won.s - 80, won.y - 1.2 * won.s - 80 + 20, getSize, lstrlen(getSize));
					}
					StretchBlt(hdc, 0, 0, bg.right, bg.bottom, mdc, won.x - 1.2 * won.s - 80, won.y - 1.2 * won.s - 80, 2.4 * won.s + 160, 2.4 * won.s + 160, SRCCOPY);//포커스화면
				}
			}
			else if (camera == 2) {//전체 화면
				if (gameover == true) {
					TextOut(mdc, 350, 380, L"GameOver", lstrlen(L"GameOver"));
					_stprintf_s(getTime, L"시간 : %.2f초", timer);
					TextOut(mdc, 350, 400, getTime, lstrlen(getTime));
					wsprintf(getSize, L"세포 크기 : %d", won.s);
					TextOut(mdc, 350, 420, getSize, lstrlen(getSize));
				}
				else {
					//시간
					if (inform) {
						_stprintf_s(getTime, L"시간 : %.2f초", timer);
						TextOut(mdc, 10, 10, getTime, lstrlen(getTime));
						wsprintf(getSize, L"세포 크기 : %d", won.s);
						TextOut(mdc, 10, 40, getSize, lstrlen(getSize));
					}
				}
				BitBlt(hdc, 0, 0, bg.right, bg.bottom, mdc, 0, 0, SRCCOPY);//전체화면
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
			feedc = 0;//먹이 수
			virusc = 0;//바이러스 수
			trapc = 0;//함정 수
			dwonc = 0;//분열된 캐릭터 수
			dvirusc = 0;//분열된 적 개체 수
			 start = false;
			 stop = false;
			camera = 1;
			//주인공 초기 값
			{
				won.x = WINDOWSIZE / 2, won.y = WINDOWSIZE / 2;
				won.s = WONSIZE;
			}
			//먹이 초기 값 x,y 50~750
			for (int i = 0; i < 40; i++) {
				newfeed();
			}
			//바이러스 초기 값 0번에 x,y 50~750
			{
				virus[virusc].x = rand() % (WINDOWSIZE - 100) + 50;
				virus[virusc].y = rand() % (WINDOWSIZE - 100) + 50;
				virus[virusc].devided = false;
				virus[virusc].s = VIRUSSIZE;
				virus[virusc].speed = 3 -  virus[virusc].s / 20;
				virusc++;
			}
			//함정 초기 값
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
	{//사이즈가 20보다 작으면 분열 안함
		if (won.s < 20) {
			InvalidateRect(hwnd, NULL, FALSE);
			break;
		}
		//주인공의 사이즈 감소
		won.s = won.s / 2;

		mx = LOWORD(lParam);
		my = HIWORD(lParam);

		angle = atan2(my - won.y, mx - won.x);

		//주인공의 분리원 생성
		dwon[dwonc].x = won.x + won.s * cos(angle);
		dwon[dwonc].y = won.y + won.s * sin(angle);
		dwon[dwonc].s = won.s;
		dwon[dwonc++].c = 0;

	}
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	case WM_RBUTTONDOWN:
	{//사이즈가 20보다 작으면 먹이 발싸 안함
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

		//주인공의 분리원 생성
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
	return DefWindowProc(hwnd, uMsg, wParam, lParam); //--- 위의 세 메시지 외의 나머지 메시지는 OS로
}

float GetDistance(float x1, float y1, float x2, float y2) {
	float distance = sqrt(pow(fabs(y2 - y1), 2) + pow(fabs(x2 - x1), 2));
	return distance;
}
bool CheckCollision(float x1, float y1, float r1, float x2, float y2, float r2)
{
	// 두 원의 중심 좌표 간의 거리 계산
	float distX = x1 - x2;
	float distY = y1 - y2;
	float distance = sqrt(distX * distX + distY * distY);

	// 두 원의 반지름의 합 계산
	float Radius = r1 + r2;

	// 충돌 검사
	if (distance <= Radius) {
		// 충돌한 경우
		return true;
	}
	else {
		// 충돌하지 않은 경우
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
	if (s >= 0)//-1이면 분열원 삭제 진행 안함
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
void devidewon(int num)//분열 개수
{
	//주인공의 사이즈 감소
	won.s = won.s / (num + 1);
	moveSpeed = 3 - won.s / 20;
	//주인공의 분리원 생성
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
void devidevirus(int k, int num)// k :몇번 쨰 바이러스인지
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
void deldwon(int s)//-1이면 삭제 안함
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
void deldvirus(int s)//-1이면 삭제 안함
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