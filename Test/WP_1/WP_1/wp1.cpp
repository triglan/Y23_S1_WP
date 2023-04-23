  WM_CREATE �����찡 ������ �� �߻� WM_RBUTTONDOWN ���콺 ������ ��ư�� ������ �߻�
WM_NCACTIVATE �������� �� �۾������� Ȱ��ȭ �Ǵ� �� Ȱ��ȭ��
�߻�(������ Ÿ��Ʋ �� ���� ����) WM_RBUTTONUP ���콺 ������ ��ư�� ���� �߻�
WM_DESTROY �����찡 �ı��Ǳ� ������ �߻� WM_MOUSEMOVE ���콺�� �����̰� ������ �߻�
WM_PAINT �����찡 �ٽ� �׷����� �ϸ� �߻� WM_SETCURSOR ���콺�� �������� �缳���ؾ� �� �� �߻�
WM_LBUTTONDOWN ���콺 ���� ��ư�� ������ �߻� WM_TIMER Ÿ�̸� ���� �� �ֱ������� �߻�
WM_LBUTTONUP ���콺 ���� ��ư�� ���� �߻� WM_COMMAND �޴�, ��ư, �׼��������� ���� �� �߻�typedef struct tagMSG {
	HWND hwnd; //--- ������ �ڵ�
	UINT message; //--- �޽��� id
	WPARAM wParam; //--- �޽��� ���� ���� 1: 32 (�Ǵ� 64) ��Ʈ LONG_PTR
	LPARAM lParam; //--- �޽��� ���� ���� 2: 32 (�Ǵ� 64) ��Ʈ UINT_PTR
	DWORD time; //--- �̺�Ʈ �߻� �ð�
	POINT pt; //--- �̺�Ʈ �߻� �� Ŀ�� ��ġ
} MSG, * PMSG;

typedef struct _WNDCLASSEX {
	UINT cbSize; //--- �� ����ü�� ũ��
	UINT style; //--- ��� ��Ÿ��
	WNDPROC lpfnWndProc; //--- ���ν��� �Լ�
	int cbClsExtra; //--- Ŭ���� ���� �޸�--- ������
	int cbWndExtra; //--- ������ ���� �޸�--- ������
	HANDLE hInstance; //--- ������ �ν��Ͻ�
	HICON hIcon; //--- ������
	HCURSOR hCursor; //--- Ŀ��
	HBRUSH hbrBackground; //--- ����
	LPCTSTR lpszMenuName; //--- �޴��̸�
	LPCTSTR lpszClassName; //--- Ŭ���� �̸�
	HICON hIconSm; //--- ���� ������
} WNDCLASSEX;

HWND CreateWindow
lpClassName ������ Ŭ�������� ������ ������ Ŭ���� �̸�
lpWindowName �������� Ÿ��Ʋ �̸�
dwStyle �������� �پ��� ��Ÿ��
WS_OVERLAPPED : ����Ʈ ������
WS_CAPTION : Ÿ��Ʋ �ٸ� ���� ������
WS_HSCROLL / WS_VSCROLL : ���� / ���� ��ũ�� ��
WS_MAXIMIZEBOX / WS_MINIMIZEBOX : �ִ�ȭ / �ּ�ȭ ��ư
WS_SYSMENU : �ý��� �޴�
WS_THICKFRAME : ũ�� ������ ������ �β��� ��輱
WS_BORDER : �ܼ����� �� ��輱, ũ�� ���� �Ұ���
WS_POPUP : �˾� ������(WS_CHILD�� ���� �� �� ����)
WS_CHILD : ���ϵ� ������
WS_VISIBLE : �����츦 �����ڸ��� ȭ�鿡 ���
WS_OVERLAPPEDWINDOW : ���� �Ϲ����� ������ ��Ÿ��
WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME |
WS_MINIMIZEBOX | WS_MAXIMIZEBOX
WS_POPUPWINDOW : �Ϲ����� �˾� ������
WS_POPUP | WS_BORDER | WS_SYSMENU
x, y �������� ��ǥ��(���� ��� ����)
nWidth / nHeight �������� ����, ���� ũ��(�ȼ� ����)
hWndParent �θ� ������ �ڵ�, �θ� ���� ���� NULL
hMenu �������� ��ܿ� �ٴ� �޴��� �ڵ� : �޴��� ���� ��
�� NULL
hInstance WinMain���� ���� �ν��Ͻ� �ڵ�

//������ ����
#include <windows.h>
#include <tchar.h>

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"windows program 2";

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;

	switch (uMsg)
	{
	case WM_CREATE:
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

