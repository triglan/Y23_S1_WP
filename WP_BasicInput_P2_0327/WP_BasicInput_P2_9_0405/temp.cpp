#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    HWND hwnd;
    MSG msg;
    WNDCLASSW wc = { 0 };

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = L"Window";
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);

    RegisterClassW(&wc);
    hwnd = CreateWindowW(wc.lpszClassName, L"WinAPI Example",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100, 500, 500, NULL, NULL, hInstance, NULL);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam)
{
    static bool pressQ = false;

    switch (msg) {

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // 기본 도형 그리기
        Rectangle(hdc, 200, 200, 300, 300);
        Ellipse(hdc, 200, 200, 300, 300);

        // q키를 눌렀을 경우 중앙에 다각형 그리기
        if (pressQ) {
            POINT pts[] = { {250, 220}, {220, 260}, {280, 260} };
            Polygon(hdc, pts, 3);
        }

        EndPaint(hwnd, &ps);
    }
    break;

    case WM_KEYDOWN:
        // q키를 눌렀을 경우 pressQ 변수를 true로 설정하고 다시 그리기 요청
        if (wParam == 'q') {
            pressQ = true;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;

    case WM_KEYUP:
        // q키를 눌렀다 떼었을 경우 pressQ 변수를 false로 설정하고 다시 그리기 요청
        if (wParam == 'q') {
            pressQ = false;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}