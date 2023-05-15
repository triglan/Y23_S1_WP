#include <windows.h> //--- 윈도우 헤더 파일
#include <tchar.h>
#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include"resource.h"


#include <windows.h> //--- 윈도우 헤더 파일
#include <tchar.h>
#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include"resource.h"
#include <atlimage.h>

#define RIGHT 0
#define LEFT 1
#define UP 2
#define DOWN 3

#define Size 50
#define BulletSize 100
//투명 비트맵 처리 
#pragma comment(lib, "msimg32.lib")

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

static HBITMAP hBitmap, hBitmap2, oldmap;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
    srand(time(NULL));
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
    hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 200, 200, 1280, 800, NULL, (HMENU)NULL, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    while (GetMessage(&Message, 0, 0, 0)) {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
    return Message.wParam;
}

typedef struct Player {
    RECT rc;
    int x, y, Direction;
}Player;

typedef struct Bullet {
    RECT rc;
    int Direction;
}Bullet;

typedef struct Monster {
    RECT rc;
    int x, y, Direction;
    BOOL Die;
    int DeadTime;
}Monster;

typedef struct Block {
    RECT rc;
    int x, y, DieCount;
}Block;

//CImage를 사용한 이미지 출력
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{//5개면 마우스 이동x
    PAINTSTRUCT ps;
    HDC hdc, mdc;
    HBRUSH hBrush, oldBrush;
    HPEN hPen, oldPen;

    static CImage Characterimg, Monsterimg, Blockimg, Backimg, Dying;
    static RECT rt;//
    static DWORD scopy = SRCCOPY;//반전색인지 아닌지

    static Player Player;
    static Bullet Bullet[5];
    static int BulletCount; //총알개수
    static Monster Monster[5][3];
    static Block Block[8];
    static int SelectBlock; //클릭시 선택블럭
    RECT ra; // 충돌검사할 때 필요한 임시 RECT

    static int PlayerAnimation; // 플레이어 애니메이션
    static int MonsterAnimation; // 몬스터 애니메이션
    static int MonsterDirection[5]; //시작 몬스터 진행방향
    static int PlayerImgY;//캐릭터 애니메이션 y좌표

    static BOOL LClick;
    static int mx, my; //마우스 좌표

    static int w, h;
    switch (uMsg) {
    case WM_CREATE:
    {
        SelectBlock = 100; // 빈곳 클릭시 0번째 블럭 선택 방지
        PlayerImgY = 30;
        Characterimg.LoadFromResource(g_hInst, IDB_BITMAP3); // 캐릭터
        Monsterimg.LoadFromResource(g_hInst, IDB_BITMAP1); //  몬스터
        Dying.LoadFromResource(g_hInst, IDB_BITMAP5); //  몬스터 죽음
        Blockimg.LoadFromResource(g_hInst, IDB_BITMAP2); // 블럭
        Backimg.LoadFromResource(g_hInst, IDB_BITMAP4); // 배경
        //imgSprite.Load(L"AllDog.bmp");
        GetClientRect(hwnd, &rt);

        SetTimer(hwnd, 1, 50, NULL);
        SetTimer(hwnd, 2, 70, NULL);
        SetTimer(hwnd, 3, 200, NULL);

        //플레이어 생성
        Player.x = 400;
        Player.y = 600;
        Player.Direction = rand() % 4;
        Player.rc.left = 400;
        Player.rc.top = 600;
        Player.rc.right = 400 + Size;
        Player.rc.bottom = 600 + Size;

        //몬스터 생성
        for (int i = 0; i < 5; i++) {
            int firstx = rand() % 500;
            int firsty = rand() % 500;
            MonsterDirection[i] = rand() % 4;
            if (MonsterDirection[i] == LEFT || MonsterDirection[i] == RIGHT) {
                for (int j = 0; j < 3; j++) {
                    Monster[i][j].x = firstx + j * Size;
                    Monster[i][j].y = firsty;
                    Monster[i][j].rc.left = Monster[i][j].x;
                    Monster[i][j].rc.top = Monster[i][j].y;
                    Monster[i][j].rc.right = Monster[i][j].x + Size;
                    Monster[i][j].rc.bottom = Monster[i][j].y + Size;
                    Monster[i][j].Direction = MonsterDirection[i];
                }
            }
            if (MonsterDirection[i] == UP || MonsterDirection[i] == DOWN) {
                for (int j = 0; j < 3; j++) {
                    Monster[i][j].x = firstx;
                    Monster[i][j].y = firsty + j * Size;
                    Monster[i][j].rc.left = Monster[i][j].x;
                    Monster[i][j].rc.top = Monster[i][j].y;
                    Monster[i][j].rc.right = Monster[i][j].x + Size;
                    Monster[i][j].rc.bottom = Monster[i][j].y + Size;
                    Monster[i][j].Direction = MonsterDirection[i];
                }
            }
        }
        //블럭생성
        for (int i = 0; i < 8; i++) {
            Block[i].x = rand() % 1000 + 100;
            Block[i].y = rand() % 600 + 100;
            Block[i].rc.left = Block[i].x;
            Block[i].rc.right = Block[i].x + 50;
            Block[i].rc.top = Block[i].y;
            Block[i].rc.bottom = Block[i].y + 50;
            for (int j = 0; j < i; j++) {
                if (IntersectRect(&ra, &Block[i].rc, &Block[j].rc)) {
                    i--;
                }
            }
            for (int j = 0; j < 5; j++) {
                for (int k = 0; k < 3; k++) {
                    if (IntersectRect(&ra, &Block[i].rc, &Monster[j][k].rc)) {
                        i--;
                    }
                }
            }
            if (IntersectRect(&ra, &Block[i].rc, &Player.rc)) i--;
        }

    }
    break;
    case WM_TIMER:
        switch (wParam)
        {
        case 1:
            MonsterAnimation++;
            MonsterAnimation = MonsterAnimation % 4;

            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 3; j++) {
                    if (Monster[i][j].Die == FALSE) {
                        //몬스터 이동
                        if (Monster[i][j].Direction == RIGHT) {
                            Monster[i][j].x += 5;
                        }
                        else if (Monster[i][j].Direction == LEFT) {
                            Monster[i][j].x -= 5;
                        }
                        else if (Monster[i][j].Direction == DOWN) {
                            Monster[i][j].y += 5;
                        }
                        else if (Monster[i][j].Direction == UP) {
                            Monster[i][j].y -= 5;
                        }
                        //벽에 부딪힘
                        if (Monster[i][j].x < 0) {
                            Monster[i][j].x += 5;
                            Monster[i][j].Direction = RIGHT;
                        }
                        if (Monster[i][j].y < 0) {
                            Monster[i][j].y += 5;
                            Monster[i][j].Direction = DOWN;
                        }
                        if (Monster[i][j].x > rt.right - Size) {
                            Monster[i][j].x -= 5;
                            Monster[i][j].Direction = LEFT;
                        }
                        if (Monster[i][j].y > rt.bottom - Size) {
                            Monster[i][j].y -= 5;
                            Monster[i][j].Direction = UP;
                        }
                        //장애물에 부딪힘
                        Monster[i][j].rc.left = Monster[i][j].x;
                        Monster[i][j].rc.top = Monster[i][j].y;
                        Monster[i][j].rc.right = Monster[i][j].x + Size;
                        Monster[i][j].rc.bottom = Monster[i][j].y + Size;
                        for (int k = 0; k < 8; k++) {
                            if (IntersectRect(&ra, &Block[k].rc, &Monster[i][j].rc) && Block[k].DieCount < 3) {
                                if (Monster[i][j].Direction == RIGHT) {
                                    Monster[i][j].x -= 5;
                                    Monster[i][j].Direction = LEFT;
                                }
                                else if (Monster[i][j].Direction == LEFT) {
                                    Monster[i][j].x += 5;
                                    Monster[i][j].Direction = RIGHT;
                                }
                                else if (Monster[i][j].Direction == UP) {
                                    Monster[i][j].y += 5;
                                    Monster[i][j].Direction = DOWN;
                                }
                                else if (Monster[i][j].Direction == DOWN) {
                                    Monster[i][j].y -= 5;
                                    Monster[i][j].Direction = UP;
                                }
                            }
                        }
                    }
                }
            }
            //플레이어 이동
            if (Player.Direction == RIGHT) {
                Player.x += 5;
            }
            else if (Player.Direction == LEFT) {
                Player.x -= 5;
            }
            else if (Player.Direction == DOWN) {
                Player.y += 5;
            }
            else if (Player.Direction == UP) {
                Player.y -= 5;
            }
            Player.rc.left = Player.x;
            Player.rc.top = Player.y;
            Player.rc.right = Player.x + Size;
            Player.rc.bottom = Player.y + Size;
            //장애물 충돌체크
            for (int k = 0; k < 8; k++) {
                if (IntersectRect(&ra, &Block[k].rc, &Player.rc) && Block[k].DieCount < 3) {
                    if (Player.Direction == RIGHT) {
                        Player.x -= 5;
                        Player.Direction = LEFT;
                    }
                    else if (Player.Direction == LEFT) {
                        Player.x += 5;
                        Player.Direction = RIGHT;
                    }
                    else if (Player.Direction == UP) {
                        Player.y += 5;
                        Player.Direction = DOWN;
                    }
                    else if (Player.Direction == DOWN) {
                        Player.y -= 5;
                        Player.Direction = UP;
                    }
                }
            }
            //벽 충돌
            if (Player.x < 0) {
                Player.x += 5;
                Player.Direction = RIGHT;
            }
            if (Player.y < 0) {
                Player.y += 5;
                Player.Direction = DOWN;
            }
            if (Player.x > rt.right - Size) {
                Player.x -= 5;
                Player.Direction = LEFT;
            }
            if (Player.y > rt.bottom - Size) {
                Player.y -= 5;
                Player.Direction = UP;
            }
            //총알 이동
            for (int i = 0; i < BulletCount; i++) {
                if (Bullet[i].Direction == LEFT) {
                    Bullet[i].rc.left -= 20;
                    Bullet[i].rc.right -= 20;
                }
                if (Bullet[i].Direction == UP) {
                    Bullet[i].rc.top -= 20;
                    Bullet[i].rc.bottom -= 20;
                }
                if (Bullet[i].Direction == RIGHT) {
                    Bullet[i].rc.left += 20;
                    Bullet[i].rc.right += 20;
                }
                if (Bullet[i].Direction == DOWN) {
                    Bullet[i].rc.top += 20;
                    Bullet[i].rc.bottom += 20;
                }
                //벽 충돌체크
                if (Bullet[i].rc.left < 0 || Bullet[i].rc.right > rt.right ||
                    Bullet[i].rc.top < 0 || Bullet[i].rc.bottom > rt.bottom) {
                    BulletCount--;
                    Bullet[i] = Bullet[BulletCount];
                }
                //장애물 충돌체크
                for (int j = 0; j < 8; j++) {
                    if (IntersectRect(&ra, &Bullet[i].rc, &Block[j].rc) && Block[j].DieCount < 3) {
                        Block[j].DieCount++;
                        BulletCount--;
                        Bullet[i] = Bullet[BulletCount];
                    }
                }
                //몬스터 충돌체크
                for (int j = 0; j < 5; j++) {
                    for (int k = 0; k < 3; k++) {
                        if (IntersectRect(&ra, &Bullet[i].rc, &Monster[j][k].rc) && Monster[j][k].Die == FALSE) {
                            Monster[j][k].Die = TRUE;
                            BulletCount--;
                            Bullet[i] = Bullet[BulletCount];
                        }
                    }
                }
            }

            break;
        case 2:
            PlayerAnimation++;
            PlayerAnimation = PlayerAnimation % 6;
            break;
        case 3:
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 3; j++) {
                    if (Monster[i][j].Die == TRUE && Monster[i][j].DeadTime < 5) {
                        Monster[i][j].DeadTime++;
                    }
                }
            }
        }
        InvalidateRect(hwnd, NULL, FALSE);
        break;
    case WM_KEYDOWN:
        if (wParam == VK_UP) Player.Direction = UP;
        if (wParam == VK_DOWN) Player.Direction = DOWN;
        if (wParam == VK_LEFT) Player.Direction = LEFT;
        if (wParam == VK_RIGHT) Player.Direction = RIGHT;
        if (wParam == VK_SPACE) {
            if (BulletCount < 5) {
                if (Player.Direction == LEFT) {
                    Bullet[BulletCount].Direction = LEFT;
                    Bullet[BulletCount].rc.left = Player.x - 15;
                    Bullet[BulletCount].rc.top = Player.y + 20;
                    Bullet[BulletCount].rc.right = Player.x - 5;
                    Bullet[BulletCount++].rc.bottom = Player.y + 30;
                }
                else if (Player.Direction == UP) {
                    Bullet[BulletCount].Direction = UP;
                    Bullet[BulletCount].rc.left = Player.x + 20;
                    Bullet[BulletCount].rc.top = Player.y - 15;
                    Bullet[BulletCount].rc.right = Player.x + 30;
                    Bullet[BulletCount++].rc.bottom = Player.y - 5;
                }
                else if (Player.Direction == RIGHT) {
                    Bullet[BulletCount].Direction = RIGHT;
                    Bullet[BulletCount].rc.left = Player.x + 5;
                    Bullet[BulletCount].rc.top = Player.y + 20;
                    Bullet[BulletCount].rc.right = Player.x + 15;
                    Bullet[BulletCount++].rc.bottom = Player.y + 30;
                }
                else if (Player.Direction == DOWN) {
                    Bullet[BulletCount].Direction = DOWN;
                    Bullet[BulletCount].rc.left = Player.x + 20;
                    Bullet[BulletCount].rc.top = Player.y + 5;
                    Bullet[BulletCount].rc.right = Player.x + 30;
                    Bullet[BulletCount++].rc.bottom = Player.y + 15;
                }
            }
        }
        break;
    case WM_CHAR:
        if (wParam == 'q') {
            DeleteObject(hBitmap);
            KillTimer(hwnd, 1);
            KillTimer(hwnd, 2);
            PostQuitMessage(0);
        }
        if (wParam == 's') {
            SelectBlock = 100;
            //Characterimg.LoadFromResource(g_hInst, IDB_BITMAP3); // 캐릭터
            //Monsterimg.LoadFromResource(g_hInst, IDB_BITMAP1); //  몬스터
            //Blockimg.LoadFromResource(g_hInst, IDB_BITMAP2); // 블럭
            //imgSprite.Load(L"AllDog.bmp");
            //GetClientRect(hwnd, &rt);

            SetTimer(hwnd, 1, 50, NULL);
            SetTimer(hwnd, 2, 70, NULL);
            SetTimer(hwnd, 3, 200, NULL);

            Player.x = 400;
            Player.y = 600;
            Player.Direction = rand() % 4;
            Player.rc.left = 400;
            Player.rc.top = 600;
            Player.rc.right = 400 + Size;
            Player.rc.bottom = 600 + Size;

            for (int i = 0; i < 5; i++) {
                int firstx = rand() % 500;
                int firsty = rand() % 500;
                MonsterDirection[i] = rand() % 4;
                if (MonsterDirection[i] == LEFT || MonsterDirection[i] == RIGHT) {
                    for (int j = 0; j < 3; j++) {
                        Monster[i][j].x = firstx + j * Size;
                        Monster[i][j].y = firsty;
                        Monster[i][j].rc.left = Monster[i][j].x;
                        Monster[i][j].rc.top = Monster[i][j].y;
                        Monster[i][j].rc.right = Monster[i][j].x + Size;
                        Monster[i][j].rc.bottom = Monster[i][j].y + Size;
                        Monster[i][j].Direction = MonsterDirection[i];
                    }
                }
                if (MonsterDirection[i] == UP || MonsterDirection[i] == DOWN) {
                    for (int j = 0; j < 3; j++) {
                        Monster[i][j].x = firstx;
                        Monster[i][j].y = firsty + j * Size;
                        Monster[i][j].rc.left = Monster[i][j].x;
                        Monster[i][j].rc.top = Monster[i][j].y;
                        Monster[i][j].rc.right = Monster[i][j].x + Size;
                        Monster[i][j].rc.bottom = Monster[i][j].y + Size;
                        Monster[i][j].Direction = MonsterDirection[i];
                        Monster[i][j].Die = FALSE;
                        Monster[i][j].DeadTime = 0;
                    }
                }
            }

            for (int i = 0; i < 8; i++) {
                Block[i].x = rand() % 1000 + 100;
                Block[i].y = rand() % 600 + 100;
                Block[i].rc.left = Block[i].x;
                Block[i].rc.right = Block[i].x + 50;
                Block[i].rc.top = Block[i].y;
                Block[i].rc.bottom = Block[i].y + 50;
                Block[i].DieCount = 0;
                for (int j = 0; j < i; j++) {
                    if (IntersectRect(&ra, &Block[i].rc, &Block[j].rc)) {
                        i--;
                    }
                }
                for (int j = 0; j < 5; j++) {
                    for (int k = 0; k < 3; k++) {
                        if (IntersectRect(&ra, &Block[i].rc, &Monster[j][k].rc)) {
                            i--;
                        }
                    }
                }
                if (IntersectRect(&ra, &Block[i].rc, &Player.rc)) i--;
            }

        }
        break;
    case WM_LBUTTONDOWN:
        LClick = TRUE;
        mx = LOWORD(lParam);
        my = HIWORD(lParam);
        for (int i = 0; i < 8; i++) {
            if (Block[i].rc.left <= mx && mx <= Block[i].rc.right &&
                Block[i].rc.top <= my && my <= Block[i].rc.bottom && Block[i].DieCount < 3) {
                SelectBlock = i;
            }
        }
        break;
    case WM_MOUSEMOVE:
        if (LClick == TRUE) {
            mx = LOWORD(lParam);
            my = HIWORD(lParam);
            Block[SelectBlock].x = mx - 25;
            Block[SelectBlock].y = my - 25;
        }
        break;
    case WM_LBUTTONUP:
        LClick = FALSE;
        Block[SelectBlock].rc.left = Block[SelectBlock].x;
        Block[SelectBlock].rc.top = Block[SelectBlock].y;
        Block[SelectBlock].rc.right = Block[SelectBlock].x + 50;
        Block[SelectBlock].rc.bottom = Block[SelectBlock].y + 50;
        SelectBlock = 100;
        break;

    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom);
        mdc = CreateCompatibleDC(hdc);

        SelectObject(mdc, hBitmap);
        //배경
        w = Backimg.GetWidth();
        h = Backimg.GetHeight();

        Backimg.Draw(mdc, 0, 0, rt.right, rt.bottom, 0, 0, w, h); //--- 메모리 DC에 배경 그리기
        
        //플레이어
        TransparentBlt(mdc, Player.x, Player.y, Size, Size, Characterimg.GetDC(), 20 * PlayerAnimation, 0, 20, 30, RGB(144, 187, 187));
        //총알
        for (int i = 0; i < BulletCount; i++) {
            Rectangle(mdc, Bullet[i].rc.left, Bullet[i].rc.top, Bullet[i].rc.right, Bullet[i].rc.bottom);
        }
        //몬스터
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 3; j++) {
                if (Monster[i][j].Die == FALSE)
                    TransparentBlt(mdc, Monster[i][j].x, Monster[i][j].y, Size, Size, Monsterimg.GetDC(), 19 * MonsterAnimation, 0, 19, 18, RGB(235, 197, 241));
                if (Monster[i][j].Die == TRUE && Monster[i][j].DeadTime < 5) {
                    TransparentBlt(mdc, Monster[i][j].x, Monster[i][j].y, Size, Size, Dying.GetDC(), 19 * MonsterAnimation, 0, 19, 18, RGB(235, 197, 241));
                }
            }
        }
        //블럭
        for (int i = 0; i < 8; i++) {
            if (Block[i].DieCount < 3)
                StretchBlt(mdc, Block[i].x, Block[i].y, 75, 50, Blockimg.GetDC(), 0, 0, 75, 50, SRCCOPY);
        }

        BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY); //--- 메모리 DC의 그림을 화면 DC에 복사하기

        DeleteObject(hBitmap);
        DeleteDC(mdc);
        InvalidateRect(hwnd, NULL, false);
        EndPaint(hwnd, &ps);
        break;
    case WM_DESTROY:
        DeleteObject(hBitmap);
        KillTimer(hwnd, 1);
        KillTimer(hwnd, 2);
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam); //--- 위의 세 메시지 외의 나머지 메시지는 O
}