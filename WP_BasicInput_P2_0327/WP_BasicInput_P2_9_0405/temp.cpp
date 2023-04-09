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

        // �⺻ ���� �׸���
        Rectangle(hdc, 200, 200, 300, 300);
        Ellipse(hdc, 200, 200, 300, 300);

        // qŰ�� ������ ��� �߾ӿ� �ٰ��� �׸���
        if (pressQ) {
            POINT pts[] = { {250, 220}, {220, 260}, {280, 260} };
            Polygon(hdc, pts, 3);
        }

        EndPaint(hwnd, &ps);
    }
    break;

    case WM_KEYDOWN:
        // qŰ�� ������ ��� pressQ ������ true�� �����ϰ� �ٽ� �׸��� ��û
        if (wParam == 'q') {
            pressQ = true;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;

    case WM_KEYUP:
        // qŰ�� ������ ������ ��� pressQ ������ false�� �����ϰ� �ٽ� �׸��� ��û
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