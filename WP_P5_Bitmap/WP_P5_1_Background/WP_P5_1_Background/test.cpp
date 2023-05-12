#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "resource.h"

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
// 윈도우 창 이름
LPCTSTR lpszWindowName = L"windows program";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevlnstance, LPSTR lpszCmdParam, int nCmdShow) {
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
    // 아이콘 변경
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    // 커서 변경
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    // 배경색 변경
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClass.lpszMenuName = MAKEINTRESOURCE(102);
    WndClass.lpszClassName = lpszClass;
    // 스몰 아이콘 변경
    WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    RegisterClassEx(&WndClass);
    // 기본창 변경
    hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 800, NULL, (HMENU)NULL, hInstance, NULL);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    while (GetMessage(&Message, 0, 0, 0)) {
        TranslateMessage(&Message);
        DispatchMessage(&Message);
    }
    return Message.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc, memdc;
    PAINTSTRUCT ps;
    static HBITMAP hBitmap;
    static BOOL full = FALSE;
    static BOOL reversal = FALSE;
    static BOOL quter = FALSE;
    static int a = 400;
    static int b = 400;
    static int mouse_xPos;
    static int mouse_yPos;
    static int num = 0;
    static int move_x1 = 0;
    static int move_x2 = 0;
    static int move_x3 = 0;
    static int move_x4 = 0;
    HBRUSH hBrush, oldBrush;
    HPEN hPen, oldPen;
    switch (iMsg) {
    case WM_CREATE:
        hBitmap = (HBITMAP)LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP2));
        break;
    case WM_TIMER:
        switch (wParam)
        {
        case 1:
            move_x1 -= 10;
            if (move_x1 == 400 || move_x1 == -400) {
                move_x1 = 0;
            }


            move_x2 -= 10;
            if (move_x2 == 400 || move_x2 == -400) {
                move_x2 = 0;
            }


            move_x3 -= 10;
            if (move_x3 == 400 || move_x3 == -400) {
                move_x3 = 0;
            }

            move_x4 -= 10;
            if (move_x4 == 400 || move_x4 == -400) {
                move_x4 = 0;
            }
            break;
        }
        InvalidateRect(hWnd, NULL, FALSE);
        break;
    case WM_CHAR:
        if (wParam == 'a') {
            if (full == TRUE) {
                full = FALSE;
            }
            else {
                full = TRUE;
            }
        }
        if (wParam == 'r') {
            if (reversal == TRUE) {
                reversal = FALSE;
            }
            else {
                reversal = TRUE;
            }
        }
        if (wParam == 's') {
            // 화면을 하얗게 지우기
            full = FALSE;
            reversal = FALSE;
            quter = FALSE;
        }
        if (wParam == '+') {
            switch (num)
            {
            case 1:
                a += 10;
                b += 10;
                break;
            case 2:
                a += 10;
                b -= 10;
                break;
            case 3:
                a -= 10;
                b += 10;
                break;
            case 4:
                a -= 10;
                b -= 10;
                break;
            }
        }
        if (wParam == '-') {
            switch (num)
            {
            case 1:
                a -= 10;
                b -= 10;
                break;
            case 2:
                a -= 10;
                b += 10;
                break;
            case 3:
                a += 10;
                b -= 10;
                break;
            case 4:
                a += 10;
                b += 10;
                break;
            }
        }

        if (wParam == 'w') {
            quter = TRUE;
        }
        if (wParam == 'q') {
            PostQuitMessage(0);
        }
        if (wParam == 'p') {
            SetTimer(hWnd, 1, 500, NULL);
        }
        InvalidateRect(hWnd, NULL, FALSE);
        break;
    case WM_KEYDOWN:
        if (wParam == VK_LEFT) {
            if (num == 1) {
                move_x1 -= 10;
                if (move_x1 == 400 || move_x1 == -400) {
                    move_x1 = 0;
                }
            }
            else if (num == 2) {
                move_x2 -= 10;
                if (move_x2 == 400 || move_x2 == -400) {
                    move_x2 = 0;
                }
            }
            else if (num == 3) {
                move_x3 -= 10;
                if (move_x3 == 400 || move_x3 == -400) {
                    move_x3 = 0;
                }
            }
            else if (num == 4) {
                move_x4 -= 10;
                if (move_x4 == 400 || move_x4 == -400) {
                    move_x4 = 0;
                }
            }
        }
        else if (wParam == VK_RIGHT) {
            if (num == 1) {
                move_x1 += 10;
                if (move_x1 == 400 || move_x1 == -400) {
                    move_x1 = 0;
                }
            }
            else if (num == 2) {
                move_x2 += 10;
                if (move_x2 == 400 || move_x2 == -400) {
                    move_x2 = 0;
                }
            }
            else if (num == 3) {
                move_x3 += 10;
                if (move_x3 == 400 || move_x3 == -400) {
                    move_x3 = 0;
                }
            }
            else if (num == 4) {
                move_x4 += 10;
                if (move_x4 == 400 || move_x4 == -400) {
                    move_x4 = 0;
                }
            }
        }
        InvalidateRect(hWnd, NULL, FALSE);
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        memdc = CreateCompatibleDC(hdc);
        SelectObject(memdc, hBitmap);

        // 화면을 하얗게 지우기
        PatBlt(hdc, 0, 0, 800, 800, WHITENESS);
        if (reversal == FALSE) {
            if (full == FALSE) {
                StretchBlt(hdc, 0, 0, 225, 225, memdc, 0, 0, 225, 225, SRCCOPY);
            }
            else if (full == TRUE) {
                StretchBlt(hdc, 0, 0, 800, 800, memdc, 0, 0, 225, 225, SRCCOPY);
            }
        }
        else if (reversal == TRUE) {
            if (full == FALSE) {
                StretchBlt(hdc, 0, 0, 225, 225, memdc, 0, 0, 225, 225, NOTSRCCOPY);
            }
            else if (full == TRUE) {
                StretchBlt(hdc, 0, 0, 800, 800, memdc, 0, 0, 225, 225, NOTSRCCOPY);
            }
        }

        if (quter == TRUE) {
            PatBlt(hdc, 0, 0, 800, 800, WHITENESS);
            if (move_x1 > 0) {
                StretchBlt(hdc, move_x1 - 400, 0, a, b, memdc, 0, 0, 225, 225, SRCCOPY);
            }
            if (move_x2 > 0) {
                StretchBlt(hdc, a + move_x2 - 400, 0, 400 + (400 - a), b, memdc, 0, 0, 225, 225, SRCCOPY);
            }
            if (move_x3 > 0) {
                StretchBlt(hdc, move_x3 - 400, b, a, 400 + (400 - b), memdc, 0, 0, 225, 225, SRCCOPY);
            }
            if (move_x4 > 0) {
                StretchBlt(hdc, a + move_x4 - 400, b, 400 + (400 - a), 400 + (400 - b), memdc, 0, 0, 225, 225, SRCCOPY);
            }
            if (move_x1 < 0) {
                StretchBlt(hdc, move_x1 + 400, 0, a, b, memdc, 0, 0, 225, 225, SRCCOPY);
            }
            if (move_x2 < 0) {
                StretchBlt(hdc, a + move_x2 + 400, 0, 400 + (400 - a), b, memdc, 0, 0, 225, 225, SRCCOPY);
            }
            if (move_x3 < 0) {
                StretchBlt(hdc, move_x3 + 400, b, a, 400 + (400 - b), memdc, 0, 0, 225, 225, SRCCOPY);
            }
            if (move_x4 < 0) {
                StretchBlt(hdc, a + move_x4 + 400, b, 400 + (400 - a), 400 + (400 - b), memdc, 0, 0, 225, 225, SRCCOPY);
            }
            StretchBlt(hdc, move_x1, 0, a, b, memdc, 0, 0, 225, 225, SRCCOPY);
            StretchBlt(hdc, a + move_x2, 0, 400 + (400 - a), b, memdc, 0, 0, 225, 225, SRCCOPY);
            StretchBlt(hdc, move_x3, b, a, 400 + (400 - b), memdc, 0, 0, 225, 225, SRCCOPY);
            StretchBlt(hdc, a + move_x4, b, 400 + (400 - a), 400 + (400 - b), memdc, 0, 0, 225, 225, SRCCOPY);
        }

        if (num == 1) {
            hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0)); // GDI: 펜 만들기
            oldPen = (HPEN)SelectObject(hdc, hPen);
            MoveToEx(hdc, 0, 0, NULL); // (10, 30) -> (50, 60) 직선 그리기
            LineTo(hdc, 0, b);

            MoveToEx(hdc, 0, 0, NULL); // (10, 30) -> (50, 60) 직선 그리기
            LineTo(hdc, a, 0);

            MoveToEx(hdc, a, 0, NULL); // (10, 30) -> (50, 60) 직선 그리기
            LineTo(hdc, a, b);

            MoveToEx(hdc, 0, b, NULL); // (10, 30) -> (50, 60) 직선 그리기
            LineTo(hdc, a, b);

            SelectObject(hdc, oldPen); // 이전의 펜으로 돌아감
            DeleteObject(hPen);
        }
        if (num == 3) {
            hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0)); // GDI: 펜 만들기
            oldPen = (HPEN)SelectObject(hdc, hPen);
            MoveToEx(hdc, 0, b, NULL); // (10, 30) -> (50, 60) 직선 그리기
            LineTo(hdc, a, b);

            MoveToEx(hdc, 0, b, NULL); // (10, 30) -> (50, 60) 직선 그리기
            LineTo(hdc, 0, 800);

            MoveToEx(hdc, a, b, NULL); // (10, 30) -> (50, 60) 직선 그리기
            LineTo(hdc, a, 800);

            MoveToEx(hdc, 0, 800, NULL); // (10, 30) -> (50, 60) 직선 그리기
            LineTo(hdc, a, 800);

            SelectObject(hdc, oldPen); // 이전의 펜으로 돌아감
            DeleteObject(hPen);
        }
        if (num == 2) {
            hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0)); // GDI: 펜 만들기
            oldPen = (HPEN)SelectObject(hdc, hPen);
            MoveToEx(hdc, a, 0, NULL); // (10, 30) -> (50, 60) 직선 그리기
            LineTo(hdc, 1000, 0);

            MoveToEx(hdc, a, 0, NULL); // (10, 30) -> (50, 60) 직선 그리기
            LineTo(hdc, a, b);

            MoveToEx(hdc, 800, 0, NULL); // (10, 30) -> (50, 60) 직선 그리기
            LineTo(hdc, 800, b);

            MoveToEx(hdc, a, b, NULL); // (10, 30) -> (50, 60) 직선 그리기
            LineTo(hdc, 800, b);

            SelectObject(hdc, oldPen); // 이전의 펜으로 돌아감
            DeleteObject(hPen);
        }
        if (num == 4) {
            hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0)); // GDI: 펜 만들기
            oldPen = (HPEN)SelectObject(hdc, hPen);
            MoveToEx(hdc, a, b, NULL); // (10, 30) -> (50, 60) 직선 그리기
            LineTo(hdc, 800, b);

            MoveToEx(hdc, a, b, NULL); // (10, 30) -> (50, 60) 직선 그리기
            LineTo(hdc, a, 800);

            MoveToEx(hdc, 800, a, NULL); // (10, 30) -> (50, 60) 직선 그리기
            LineTo(hdc, 800, 800);

            MoveToEx(hdc, a, 800, NULL); // (10, 30) -> (50, 60) 직선 그리기
            LineTo(hdc, 800, 800);

            SelectObject(hdc, oldPen); // 이전의 펜으로 돌아감
            DeleteObject(hPen);
        }

        DeleteDC(memdc);
        EndPaint(hWnd, &ps);
        break;
    case WM_LBUTTONDOWN:
        hdc = GetDC(hWnd);
        mouse_xPos = LOWORD(lParam);
        mouse_yPos = HIWORD(lParam);

        if (mouse_xPos < a && mouse_yPos < b) {
            num = 1;
        }
        else if (mouse_xPos < a && mouse_yPos > b) {
            num = 3;
        }
        else if (mouse_xPos > a && mouse_yPos < b) {
            num = 2;
        }
        else if (mouse_xPos > a && mouse_yPos > b) {
            num = 4;
        }

        ReleaseDC(hWnd, hdc);
        InvalidateRect(hWnd, NULL, FALSE);
        break;
    case WM_DESTROY:
        DeleteObject(hBitmap);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, iMsg, wParam, lParam);
    }
    return 0;
}