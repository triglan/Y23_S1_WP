#include <windows.h> //--- 윈도우 헤더 파일
#include <tchar.h>
#include <stdbool.h>
#include<stdio.h>
#include<math.h>
#include <time.h>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming Lab";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
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
    hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    while (GetMessage(&Message, 0, 0, 0)) {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
    return Message.wParam;
}
typedef struct Circle {
    float x;
    float y;
    float r;
    int nd;//no die
}circle;
bool isCollision(circle c1, circle c2) {
    float len = sqrt((c2.x - c1.x) * (c2.x - c1.x) + (c2.y - c1.y) * (c2.y - c1.y));
    if (len <= (c2.r + c1.r))
        return true;
    else
        return false;
}
bool Cin(circle c1, circle c2) {//c1큰 c2작원
    float len = sqrt((c2.x - c1.x) * (c2.x - c1.x) + (c2.y - c1.y) * (c2.y - c1.y)) + c2.r;
    if (len <= c1.r)
        return true;
    else
        return false;
}
float length(int x1, int y1, int x2, int y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static int stop = 5;
    static int one = 0;
    static int camera = 0;
    static int gameover = 0;
    static int inforprtint = 0;
    PAINTSTRUCT ps;
    HDC hdc, mdc;
    HBRUSH hbr, oldbr;
    HPEN hp, oldp;
    HBITMAP hBitmap;
    RECT rt = { 0,0,800,600 };
    static int hspeed;
    static circle fcir[40];//먹이
    static circle hcir;//주인공 원
    static TCHAR hsize[50];
    static circle vcir[100];//바이러스
    static float vstap[100];
    static int vspeed = 50;
    static int vcount = 0;//바이러스개수
    static int vmode[100];

    static int vmove[3];
    static int dir;
    static float angle;
    static float angle1;
    static float mx = 0, my = 0;
    static circle trap[100];
    static int tcount[100];
    static int tspeed = 100;
    static int tnum = 0;
    static circle tmp;
    static int shortnum;
    //시간
    static int timerspeed = 1000;
    static int timercount = 0;//초단위
    static TCHAR timer[100];
    srand((unsigned)time(NULL));
    //--- 메시지 처리하기
    switch (uMsg) {
    case WM_CREATE:
    {
        //헤드
        hcir.r = 5;
        hcir.x = 150, hcir.y = 150;
        hcir.nd = 0;
        hspeed = 50;
        //먹이
        for (int i = 0; i < 40; i++) {
            fcir[i].x = rand() % 750;
            fcir[i].y = rand() % 550;
            fcir[i].r = 3;
            for (int j = 0; j < i; j++) {
                if (fcir[i].x == fcir[j].x && fcir[i].y == fcir[j].y) {
                    i--;
                }
            }
        }
        //바이러스
        vspeed = 250;
        vcir[0].x = rand() % 750, vcir[0].y = rand() % 550, vcir[0].r = 5;
        for (int i = 0; i < 100; i++) {
            vstap[i] = 5;
            vcir[i].r = 5;
            vmode[i] = 0;
        }
        //트랩
        trap[0].x = 400, trap[0].y = 300;
        trap[0].r = 20;
        tcount[0] = 0;
        for (int i = 0; i < 100; i++) {
            trap[i].r = 20;
        }

        //시간

        //

        SetTimer(hWnd, 4, tspeed, NULL);//트랩
        SetTimer(hWnd, 3, vspeed, NULL);//바이러스0
        SetTimer(hWnd, 2, hspeed, NULL);//주인공
        SetTimer(hWnd, 1, 6000, NULL);//먹이
        SetTimer(hWnd, 20, timerspeed, NULL);//
    }
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);

        {
            //더블버퍼링
            mdc = CreateCompatibleDC(hdc); //--- 메모리 DC 만들기
            hBitmap = CreateCompatibleBitmap(hdc, rt.right, rt.bottom); //--- 메모리 DC와 연결할 비트맵 만들기
            SelectObject(mdc, (HBITMAP)hBitmap);
            //흰색 배경
            hbr = CreateSolidBrush(RGB(255, 255, 255));
            oldbr = (HBRUSH)SelectObject(mdc, hbr);
            FillRect(mdc, &rt, hbr);
            SelectObject(mdc, oldbr);
            DeleteObject(hbr);
        }
        //--실재---
        //먹이
        for (int i = 0; i < 40; i++) {
            hbr = CreateSolidBrush(RGB(224, 230, 31));
            oldbr = (HBRUSH)SelectObject(mdc, hbr);
            Ellipse(mdc, fcir[i].x - fcir[i].r, fcir[i].y - fcir[i].r, fcir[i].x + fcir[i].r, fcir[i].y + fcir[i].r);
            SelectObject(mdc, oldbr);
            DeleteObject(hbr);
        }
        {
            //주인공원
            hbr = CreateSolidBrush(RGB(255, 0, 0));
            oldbr = (HBRUSH)SelectObject(mdc, hbr);
            Ellipse(mdc, hcir.x - hcir.r, hcir.y - hcir.r, hcir.x + hcir.r, hcir.y + hcir.r);
            SelectObject(mdc, oldbr);
            DeleteObject(hbr);
            //바이러스원
            for (int i = 0; i < vcount + 1; i++) {
                hbr = CreateSolidBrush(RGB(255, 0, 255));
                oldbr = (HBRUSH)SelectObject(mdc, hbr);
                Ellipse(mdc, vcir[i].x - vcir[i].r, vcir[i].y - vcir[i].r, vcir[i].x + vcir[i].r, vcir[i].y + vcir[i].r);
                SelectObject(mdc, oldbr);
                DeleteObject(hbr);
            }//트랩
            for (int i = 0; i < tnum + 1; i++) {
                hbr = CreateHatchBrush(HS_DIAGCROSS, RGB(0, 0, 0));
                oldbr = (HBRUSH)SelectObject(mdc, hbr);
                Ellipse(mdc, trap[i].x - trap[i].r, trap[i].y - trap[i].r, trap[i].x + trap[i].r, trap[i].y + trap[i].r);
                SelectObject(mdc, oldbr);
                DeleteObject(hbr);
            }
        }
       
        //시간
        if (inforprtint == 1) {
            wsprintf(timer, L"시간: %d초", timercount);
            TextOut(mdc, 0, 0, timer, lstrlen(timer));
            _stprintf_s(hsize, _countof(hsize), L"세포크기: %f", hcir.r);
            TextOut(mdc, 0, 20, hsize, lstrlen(hsize));
        }
        //TextOut(hdc, x, y, lpOut, lstrlen(lpOut));
        //-------------------
        if (camera == 0) {//전체
            if (gameover == 0) {
                BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, SRCCOPY);
            }
            else if (gameover == 1) {
                TextOut(mdc, 330, 200, L"GAME OVER!!", lstrlen(L"GAME OVER!!"));
                wsprintf(timer, L"시간: %d초", timercount);
                TextOut(mdc, 330, 220, timer, lstrlen(timer));
                _stprintf_s(hsize, _countof(hsize), L"세포크기: %f", hcir.r);
                TextOut(mdc, 330, 240, hsize, lstrlen(hsize));
                BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, NOTSRCCOPY);

            }
        }
        else if (camera == 1) {//포커스
            if (gameover == 0) {
                StretchBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, hcir.x - hcir.r - 50, hcir.y - hcir.r - 50, hcir.r + 120, hcir.r + 120, SRCCOPY);
            }
            else if (gameover == 1) {
                TextOut(mdc, 330, 200, L"GAME OVER!!", lstrlen(L"GAME OVER!!"));
                wsprintf(timer, L"시간: %d초", timercount);
                TextOut(mdc, 330, 220, timer, lstrlen(timer));
                _stprintf_s(hsize, _countof(hsize), L"세포크기: %f", hcir.r);
                TextOut(mdc, 330, 240, hsize, lstrlen(hsize));
                BitBlt(hdc, 0, 0, rt.right, rt.bottom, mdc, 0, 0, NOTSRCCOPY);
            }
        }
        DeleteDC(mdc); //--- 생성한 메모리 DC 삭제: 계속 사용할 경우 전역변수 또는 정적 변수로 선언해도 무방함.
        DeleteObject(hBitmap);
        EndPaint(hWnd, &ps);
        break;
    case WM_CHAR:
        if (wParam == '1') {
            camera = 1;
        }
        if (wParam == '2') {
            camera = 0;
        }
        if (wParam == 'n') {
            if (one == 0) {
                stop = 0;
                one = 1;
            }
        }
        if (wParam == 's') {
            if (stop == 1) {
                stop = 0;
            }
            else if (stop == 0) {
                stop = 1;
            }
        }
        if (wParam == 'q') {
            gameover = 1;
        }
        if (wParam == 'p') {
            if (inforprtint == 0) {
                inforprtint = 1;
            }
            else if (inforprtint == 1) {
                inforprtint = 0;
            }
        }
        if (wParam == 'q') {
            gameover = 1;
            inforprtint = 0;
        }
        if (wParam == 'r') {
            timerspeed = 1000;
            timercount = 0;
            stop = 5;
            one = 0;
            camera = 0;
            gameover = 0;
            inforprtint = 0;
            vspeed = 50;
            vcount = 0;
            tspeed = 100;
            tnum = 0;
            hcir.r = 5;
            hcir.x = 150, hcir.y = 150;
            hcir.nd = 0;
            hspeed = 50;

            //먹이
            for (int i = 0; i < 40; i++) {
                fcir[i].x = rand() % 750;
                fcir[i].y = rand() % 550;
                fcir[i].r = 3;
                for (int j = 0; j < i; j++) {
                    if (fcir[i].x == fcir[j].x && fcir[i].y == fcir[j].y) {
                        i--;
                    }
                }
            }
            //바이러스
            vspeed = 250;
            vcir[0].x = rand() % 750, vcir[0].y = rand() % 550, vcir[0].r = 5;
            for (int i = 0; i < 100; i++) {
                vstap[i] = 5;
                vcir[i].r = 5;
                vmode[i] = 0;
            }
            //트랩
            trap[0].x = 400, trap[0].y = 300;
            trap[0].r = 20;
            tcount[0] = 0;
            for (int i = 0; i < 100; i++) {
                trap[i].r = 20;
            }
        }
        InvalidateRect(hWnd, NULL, FALSE);
        break;
    case WM_TIMER:
        switch (wParam) {

        case 4://트랩
            if (stop == 0 && gameover == 0) {
                for (int i = 0; i < tnum + 1; i++) {
                    angle1 = atan2(fcir[tcount[i]].y - trap[i].y, fcir[tcount[i]].x - trap[i].x);
                    trap[i].x += 2 * cos(angle1);
                    trap[i].y += 2 * sin(angle1);
                    if (trap[i].r > hcir.r) {
                        if (Cin(trap[i], hcir)) {
                            //바이러스 충돌하지 않는다 
                            hcir.nd = 1;
                        }
                        else {
                            hcir.nd = 0;
                        }
                    }
                    else if (trap[i].r <= hcir.r) {//트랩<주인공 크기
                        if (isCollision(hcir, trap[i])) {

                        }
                    }
                    if (fcir[tcount[i]].r == 0 || isCollision(trap[i], fcir[tcount[i]])) {
                        tcount[i]++;
                    }
                    if (tcount[i] == 39) {
                        tcount[i] = 0;
                    }
                }
                break;
            }
        case 3://바이러스
            if (stop == 0 && gameover == 0) {
                for (int i = 0; i < vcount + 1; i++) {
                    tmp = fcir[0];
                    for (int j = 0; j < 40; j++) {
                        if (length(tmp.x, tmp.y, vcir[i].x, vcir[i].y) > length(vcir[i].x, vcir[i].y, fcir[j].x, fcir[j].y)
                            && fcir[j].r != 0) {
                            tmp = fcir[j];
                            shortnum = j;
                        }
                    }
                    if (vmode[i] == 0) {//자연스러움
                        angle = atan2(fcir[shortnum].y - vcir[i].y, fcir[shortnum].x - vcir[i].x);
                        vcir[i].x += vstap[i] * cos(angle);
                        vcir[i].y += vstap[i] * sin(angle);
                    }
                    else if (vmode[i] == 1) {//따라가기
                        angle = atan2(hcir.y - vcir[i].y, hcir.x - vcir[i].x);
                        vcir[i].x += vstap[i] * cos(angle);
                        vcir[i].y += vstap[i] * sin(angle);
                    }
                    else if (vmode[i] == 2) {//도망
                        angle = atan2(hcir.y - vcir[i].y, hcir.x - vcir[i].x);
                        vcir[i].x -= vstap[i] * cos(angle);
                        vcir[i].y -= vstap[i] * sin(angle);
                    }

                    if (length(vcir[i].x, vcir[i].y, hcir.x, hcir.y) - vcir[i].r - hcir.r <= 80 && vcir[i].r > hcir.r) {
                        vmode[i] = 1;
                    }
                    else if (length(vcir[i].x, vcir[i].y, hcir.x, hcir.y) - vcir[i].r - hcir.r <= 80 && vcir[i].r <= hcir.r) {
                        vmode[i] = 2;
                    }
                    else {
                        vmode[i] = 0;
                    }
                    if (isCollision(vcir[i], hcir) && hcir.nd == 0 && vcir[i].r > hcir.r) {////주인공과 바이러스 충돌
                        gameover = 1;
                        inforprtint = 0;
                    }
                    if (isCollision(vcir[i], fcir[shortnum])) {
                        fcir[shortnum].r = 0;
                        vcir[i].r += 0.5;
                        vstap[i] -= 0.02;
                        if (vstap[i] == 0) {
                            vstap[i] = 0.5;
                        }
                    }
                }
                break;
            }

        case 2://마우스 주인공
            if (stop == 0 && gameover == 0) {
                angle = atan2(my - hcir.y, mx - hcir.x);
                hcir.x += 3 * cos(angle);
                hcir.y += 3 * sin(angle);
                for (int i = 0; i < vcount + 1; i++) {//주인공과 바이러스 충돌
                    if (isCollision(vcir[i], hcir) && hcir.nd == 0 && vcir[i].r > hcir.r) {
                        gameover = 1;
                        inforprtint = 0;
                    }
                }
                for (int i = 0; i < tnum + 1; i++) {
                    if (trap[i].r > hcir.r) {//트랩>주인공 크기
                        if (Cin(trap[i], hcir)) {
                            //바이러스 충돌하지 않는다 
                            hcir.nd = 1;
                        }
                        else {
                            hcir.nd = 0;
                        }
                    }
                    else if (trap[i].r <= hcir.r) {//트랩<주인공 크기
                        if (isCollision(hcir, trap[i])) {

                        }
                    }
                }
                for (int i = 0; i < 40; i++) {
                    if (isCollision(hcir, fcir[i]) && fcir[i].r != 0) {
                        fcir[i].r = 0;
                        hcir.r += 0.5;
                        hspeed += 1;
                        SetTimer(hWnd, 2, hspeed, NULL);
                    }
                }
                break;
            }
        case 1://먹이 랜덤
            if (stop == 0 && gameover == 0) {
                for (int i = 0; i < 40; i++) {//3초마다 
                    if (fcir[i].r == 0) {
                        fcir[i].r = 3;
                    }
                }
                for (int i = 0; i < 7; i++) {
                    fcir[rand() % 40].r = 0;
                    fcir[rand() % 40].r = 3;
                    fcir[rand() % 40].x = rand() % 750;
                    fcir[rand() % 40].y = rand() % 550;
                }

                break;
            }
        case 20:
            if (stop == 0 && gameover == 0) {
                timercount += 1;
                if (timercount % 20 == 0) {
                    vcount++;
                    vcir[vcount].x = rand() % 750;
                    vcir[vcount].y = rand() % 550;
                }
                if (timercount % 60 == 0) {
                    tnum++;
                    trap[tnum].x = rand() % 750;
                    trap[tnum].y = rand() % 550;
                    tcount[tnum] = rand() % 40;
                }
                break;
            }
        }
        InvalidateRect(hWnd, NULL, FALSE);
        break;
    case WM_MOUSEMOVE:
        mx = LOWORD(lParam);
        my = HIWORD(lParam);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam); //--- 위의 세 메시지 외의 나머지 메시지 
}